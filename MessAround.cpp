#include "MessAround.h"
#include "KeyboardEventProducer.h"
#include "KeyboardEventListener.h"

MessAround::MessAround(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    Initialize();
}

MessAround::~MessAround()
{
    delete m_eventListener;
    KeyboardEventProducer::Destroy();
}

void MessAround::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_picking)
    {
        QWidget::mouseMoveEvent(event);
        return;
    }

    setCursor(Qt::CrossCursor);
    QWidget::mouseMoveEvent(event);
}

void MessAround::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_picking && event->button() == Qt::LeftButton)
    {
#ifdef Q_OS_WIN
        POINT pt;
        GetCursorPos(&pt);

        HWND windowHandle = WindowFromPoint(pt);
        windowHandle      = GetAncestor(windowHandle, GA_ROOT);
        emit OnWindowPicked(windowHandle);
#endif
    }

    m_picking = false;
    setCursor(Qt::ArrowCursor);
    QWidget::mouseReleaseEvent(event);
}

void MessAround::Initialize()
{
    m_eventProducer = KeyboardEventProducer::Instance();
    m_eventListener = new KeyboardEventListener;

    InitWidget();
    InitSignalSlots();
}

void MessAround::InitWidget()
{
    ui.btnPickWindow->setToolTip(tr("Drag to pick, release to add"));
    ui.btnPickWindow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Add));
}

void MessAround::InitSignalSlots()
{
    connect(ui.btnPickWindow, &QPushButton::pressed, [this]() {
        setMouseTracking(true);
        m_picking = true;
    });

    connect(m_eventProducer, &KeyboardEventProducer::KeyDown, m_eventListener, &KeyboardEventListener::OnKeyDown);
    connect(m_eventProducer, &KeyboardEventProducer::KeyUp, m_eventListener, &KeyboardEventListener::OnKeyUp);
}

#ifdef Q_OS_WINDOWS
void MessAround::OnWindowPicked(HWND windowHandle)
{
    // wchar_t title[512];
    // GetWindowTextW(windowHandle, title, 512);
    //
    // // ui.editTitle->setText(QString::fromStdWString(std::wstring(title)));
    //
    // LONG exStyle     = GetWindowLong(m_windowHandle, GWL_EXSTYLE);
    // bool alwaysOnTop = (exStyle & WS_EX_TOPMOST) != 0;
    //
    // BYTE     alpha;
    // DWORD    flags = 0;
    // COLORREF key   = 0;
    //
    // BOOL ok = GetLayeredWindowAttributes(m_windowHandle, &key, &alpha, &flags);

    m_eventListener->StartListening(windowHandle, Qt::Key_Pause);

    wchar_t title[512];
    GetWindowTextW(windowHandle, title, 512);

    wchar_t hwndStr[32];
    swprintf(hwndStr, 32, L"%p", windowHandle);

    const wchar_t sep = L'\x1F';

    std::wstring text = hwndStr;
    text.push_back(sep);
    text.append(title);
    ui.listWindows->addItem(QString::fromStdWString(text));
}
#endif
