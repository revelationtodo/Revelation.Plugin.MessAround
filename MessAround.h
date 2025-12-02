#pragma once
#include <QWidget>
#include "ui_MessAround.h"

#ifdef Q_OS_WIN
#include "Windows.h"
#endif

class KeyboardEventProducer;
class KeyboardEventListener;
class MessAround : public QWidget
{
    Q_OBJECT
  public:
    MessAround(QWidget* parent = nullptr);
    ~MessAround();

  private:
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

  private:
    void Initialize();
    void InitWidget();
    void InitSignalSlots();

  public slots:
#ifdef Q_OS_WINDOWS
    void OnWindowPicked(HWND windowHandle);
#endif

  private:
    Ui::MessAroundClass ui;

    bool m_picking = false;

    KeyboardEventProducer* m_eventProducer = nullptr;
    KeyboardEventListener* m_eventListener = nullptr;
};
