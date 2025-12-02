#pragma once
#include <QObject>
#ifdef Q_OS_WINDOWS
#include "Windows.h"
#endif

class KeyboardEventProducer : public QObject
{
    Q_OBJECT
  public:
    KeyboardEventProducer(QObject* parent = nullptr);
    virtual ~KeyboardEventProducer();
    static KeyboardEventProducer* Instance();
    static void Destroy();

  signals:
    void KeyDown(Qt::Key key);
    void KeyUp(Qt::Key key);

  private:
#ifdef Q_OS_WINDOWS
    HHOOK m_hook = 0;
#endif
};
