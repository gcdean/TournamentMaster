#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QFrame>

namespace Ui {
class TimerWidget;
}

class TimerWidget : public QFrame
{
    Q_OBJECT

public:
    explicit TimerWidget(QWidget *parent = 0);
    ~TimerWidget();

private:
    Ui::TimerWidget *ui;
};

#endif // TIMERWIDGET_H
