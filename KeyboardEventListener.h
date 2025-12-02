#pragma once
#include <QObject>
#include <QRect>
#ifdef Q_OS_WINDOWS
#include "Windows.h"
#endif

class KeyboardEventListener : public QObject
{
    Q_OBJECT
  public:
    KeyboardEventListener(QObject* parent = nullptr);
    ~KeyboardEventListener();

#ifdef Q_OS_WINDOWS
    void StartListening(HWND winHandle, Qt::Key key);
    void StopListening(HWND winHandle);
#endif

  public slots:
    void OnKeyDown(Qt::Key key);
    void OnKeyUp(Qt::Key key);

  private:
#ifdef Q_OS_WINDOWS
    struct WinInfo
    {
        Qt::Key m_key;
        QRect   m_rect   = QRect(0, 0, 0, 0);
        bool    m_paused = true;
    };

    std::unordered_map<HWND, WinInfo> m_winHandle2Info;
    std::multimap<Qt::Key, HWND>      m_key2WinHandles;
#endif
};
