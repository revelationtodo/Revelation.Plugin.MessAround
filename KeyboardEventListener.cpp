#include "KeyboardEventListener.h"

KeyboardEventListener::KeyboardEventListener(QObject* parent)
    : QObject(parent)
{
}

KeyboardEventListener::~KeyboardEventListener()
{
#ifdef Q_OS_WINDOWS
    for (auto& [winHandle, _] : m_winHandle2Info)
    {
        StopListening(winHandle);
    }
#endif
}

#ifdef Q_OS_WINDOWS
void KeyboardEventListener::StartListening(HWND handle, Qt::Key key)
{
    StopListening(handle);

    m_winHandle2Info.insert(std::make_pair(handle, WinInfo{key}));
    m_key2WinHandles.emplace(key, handle);

    // hide for once
    RECT rect;
    GetWindowRect(handle, &rect);
    SetWindowPos(handle, HWND_TOPMOST,
                 rect.left, rect.top,
                 rect.right - rect.left, rect.bottom - rect.top,
                 SWP_HIDEWINDOW);
}

void KeyboardEventListener::StopListening(HWND handle)
{
    auto infoFinder = m_winHandle2Info.find(handle);
    if (infoFinder != m_winHandle2Info.end())
    {
        auto range = m_key2WinHandles.equal_range(infoFinder->second.m_key);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second == handle)
            {
                m_key2WinHandles.erase(it);
                break;
            }
        }

        m_winHandle2Info.erase(infoFinder);
    }

    // show for once
    RECT rect;
    GetWindowRect(handle, &rect);
    SetWindowPos(handle, HWND_TOPMOST,
                 rect.left, rect.top,
                 rect.right - rect.left, rect.bottom - rect.top,
                 SWP_SHOWWINDOW);
}
#endif

void KeyboardEventListener::OnKeyDown(Qt::Key key)
{
#ifdef Q_OS_WINDOWS
    auto range = m_key2WinHandles.equal_range(key);
    for (auto it = range.first; it != range.second; ++it)
    {
        HWND handle = it->second;
        SetForegroundWindow(handle);
        PostMessage(handle, WM_KEYDOWN, VK_SPACE, 0);

        auto infoFinder = m_winHandle2Info.find(handle);
        if (infoFinder != m_winHandle2Info.end())
        {
            // WinInfo info = infoFinder->second;

            RECT rect;
            GetWindowRect(handle, &rect);
            SetWindowPos(handle, HWND_TOPMOST,
                         rect.left, rect.top,
                         rect.right - rect.left, rect.bottom - rect.top,
                         SWP_HIDEWINDOW);
        }
    }
#endif
}

void KeyboardEventListener::OnKeyUp(Qt::Key key)
{
#ifdef Q_OS_WINDOWS
    auto range = m_key2WinHandles.equal_range(key);
    for (auto it = range.first; it != range.second; ++it)
    {
        HWND handle = it->second;
        SetForegroundWindow(handle);
        PostMessage(handle, WM_KEYDOWN, VK_SPACE, 0);

        auto infoFinder = m_winHandle2Info.find(handle);
        if (infoFinder != m_winHandle2Info.end())
        {
            // WinInfo info = infoFinder->second;
            
            RECT rect;
            GetWindowRect(handle, &rect);
            SetWindowPos(handle, HWND_TOPMOST,
                         rect.left, rect.top,
                         rect.right - rect.left, rect.bottom - rect.top,
                         SWP_SHOWWINDOW);
        }
    }
#endif
}
