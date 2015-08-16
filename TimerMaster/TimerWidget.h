#pragma once

#include <QFrame>
#include <QTime>
#include <QTimer>

namespace Ui {
class TimerWidget;
}

class TimerWidget : public QFrame
{
    Q_OBJECT

public:
    explicit TimerWidget(QWidget *parent = 0);
    ~TimerWidget();

    void setTime(QTime time);

    void start();
    void stop();
    bool isRunning();
    void reset();

signals:
    void finished();
    void stopped();

private slots:
    void updateTime();

private:
    void setDisplay(QString display);


    Ui::TimerWidget *ui;

    QTime m_maxTime;
    QTime m_timeLeft;
    QTimer m_timer;
};

