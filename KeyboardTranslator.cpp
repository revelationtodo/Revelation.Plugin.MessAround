#include "KeyboardTranslator.h"

#ifdef Q_OS_WINDOWS
#include <Windows.h>

// clang-format off
const std::unordered_map<Qt::Key, int> KeyboardTranslator::m_qtKey2WinKey = {
    // digits (top row)
    {Qt::Key_0, '0'}, {Qt::Key_1, '1'}, {Qt::Key_2, '2'}, {Qt::Key_3, '3'},
    {Qt::Key_4, '4'}, {Qt::Key_5, '5'}, {Qt::Key_6, '6'}, {Qt::Key_7, '7'},
    {Qt::Key_8, '8'}, {Qt::Key_9, '9'},

    // letters
    {Qt::Key_A, 'A'}, {Qt::Key_B, 'B'}, {Qt::Key_C, 'C'}, {Qt::Key_D, 'D'},
    {Qt::Key_E, 'E'}, {Qt::Key_F, 'F'}, {Qt::Key_G, 'G'}, {Qt::Key_H, 'H'},
    {Qt::Key_I, 'I'}, {Qt::Key_J, 'J'}, {Qt::Key_K, 'K'}, {Qt::Key_L, 'L'},
    {Qt::Key_M, 'M'}, {Qt::Key_N, 'N'}, {Qt::Key_O, 'O'}, {Qt::Key_P, 'P'},
    {Qt::Key_Q, 'Q'}, {Qt::Key_R, 'R'}, {Qt::Key_S, 'S'}, {Qt::Key_T, 'T'},
    {Qt::Key_U, 'U'}, {Qt::Key_V, 'V'}, {Qt::Key_W, 'W'}, {Qt::Key_X, 'X'},
    {Qt::Key_Y, 'Y'}, {Qt::Key_Z, 'Z'},

    // function keys
    {Qt::Key_F1, VK_F1}, {Qt::Key_F2, VK_F2}, {Qt::Key_F3, VK_F3}, {Qt::Key_F4, VK_F4},
    {Qt::Key_F5, VK_F5}, {Qt::Key_F6, VK_F6}, {Qt::Key_F7, VK_F7}, {Qt::Key_F8, VK_F8},
    {Qt::Key_F9, VK_F9}, {Qt::Key_F10, VK_F10}, {Qt::Key_F11, VK_F11}, {Qt::Key_F12, VK_F12},
    {Qt::Key_Print, VK_PRINT}, {Qt::Key_Pause, VK_PAUSE},

    // arrow keys
    {Qt::Key_Left, VK_LEFT}, {Qt::Key_Right, VK_RIGHT},
    {Qt::Key_Up, VK_UP}, {Qt::Key_Down, VK_DOWN},

    // control keys
    {Qt::Key_Return, VK_RETURN}, {Qt::Key_Enter, VK_RETURN}, {Qt::Key_Escape, VK_ESCAPE},
    {Qt::Key_Backspace, VK_BACK}, {Qt::Key_Tab, VK_TAB}, {Qt::Key_Space, VK_SPACE},

    // modifiers (not distinguishing left/right)
    {Qt::Key_Shift, VK_SHIFT}, {Qt::Key_Control, VK_CONTROL},
    {Qt::Key_Alt, VK_MENU}, {Qt::Key_Meta, VK_LWIN},

    // navigation / edit keys
    {Qt::Key_Insert, VK_INSERT}, {Qt::Key_Delete, VK_DELETE}, {Qt::Key_Home, VK_HOME},
    {Qt::Key_End, VK_END}, {Qt::Key_PageUp, VK_PRIOR}, {Qt::Key_PageDown, VK_NEXT},

    // signs / OEM keys
    {Qt::Key_Minus, VK_OEM_MINUS}, {Qt::Key_Equal, VK_OEM_PLUS},
    {Qt::Key_Comma, VK_OEM_COMMA}, {Qt::Key_Period, VK_OEM_PERIOD},
    {Qt::Key_Semicolon, VK_OEM_1}, {Qt::Key_Slash, VK_OEM_2}, {Qt::Key_BracketLeft, VK_OEM_4},
    {Qt::Key_Backslash, VK_OEM_5}, {Qt::Key_BracketRight, VK_OEM_6}, {Qt::Key_Apostrophe, VK_OEM_7},
    
    // lock keys
    {Qt::Key_CapsLock, VK_CAPITAL}, {Qt::Key_NumLock, VK_NUMLOCK}, {Qt::Key_ScrollLock, VK_SCROLL},
};
// clang-format on

// reverse lookup map
const std::unordered_map<int, Qt::Key> KeyboardTranslator::m_winKey2QtKey = [] {
    std::unordered_map<int, Qt::Key> map;
    for (auto& kv : KeyboardTranslator::m_qtKey2WinKey)
        map[kv.second] = kv.first;
    return map;
}();

#endif // Q_OS_WINDOWS

// translate Win32 -> Qt
bool KeyboardTranslator::Translate(int winKey, Qt::Key& qtKey)
{
#ifdef Q_OS_WINDOWS
    auto it = m_winKey2QtKey.find(winKey);
    if (it == m_winKey2QtKey.end())
    {
        return false;
    }

    qtKey = it->second;
    return true;
#else
    return false;
#endif
}

// translate Qt -> Win32
bool KeyboardTranslator::Translate(Qt::Key qtKey, int& winKey)
{
#ifdef Q_OS_WINDOWS
    auto it = m_qtKey2WinKey.find(qtKey);
    if (it == m_qtKey2WinKey.end())
    {
        return false;
    }

    winKey = it->second;
    return true;
#else
    return false;
#endif
}
