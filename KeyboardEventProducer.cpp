#include "KeyboardEventProducer.h"
#include "KeyboardTranslator.h"
#include <thread>
#include <set>

static KeyboardEventProducer* s_instance;

#ifdef Q_OS_WINDOWS
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    if (code >= 0 && nullptr != s_instance)
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        Qt::Key          translatedKey;
        if (KeyboardTranslator::Translate(p->vkCode, translatedKey))
        {
            if (wParam == WM_KEYDOWN)
            {
                emit s_instance->KeyDown(translatedKey);
            }
            else if (wParam == WM_KEYUP)
            {
                emit s_instance->KeyUp(translatedKey);
            }
        }
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}
#endif

KeyboardEventProducer::KeyboardEventProducer(QObject* parent /*= nullptr*/)
    : QObject(parent)
{
#ifdef Q_OS_WINDOWS
    std::thread hookThread([&]() {
        MSG msg;
        PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);

        m_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    });
    hookThread.detach();
#endif
}

KeyboardEventProducer::~KeyboardEventProducer()
{
#ifdef Q_OS_WINDOWS
    UnhookWindowsHookEx(m_hook);
#endif
}

KeyboardEventProducer* KeyboardEventProducer::Instance()
{
    if (nullptr == s_instance)
    {
        s_instance = new KeyboardEventProducer();
    }
    return s_instance;
}

void KeyboardEventProducer::Destroy()
{
    if (s_instance != nullptr)
    {
        delete s_instance;
    }
}
