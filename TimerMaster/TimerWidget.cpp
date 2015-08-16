#include "TimerWidget.h"
#include "ui_TimerWidget.h"

namespace
{
    const int timerInterval = 1;
}
TimerWidget::TimerWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);

    connect(&m_timer, &QTimer::timeout, this, &TimerWidget::updateTime);
}

TimerWidget::~TimerWidget()
{
    delete ui;
}

void TimerWidget::setTime(QTime time)
{
    m_maxTime = time;
    m_timeLeft = m_maxTime;
}

void TimerWidget::start()
{
    m_timer.start(timerInterval);
}

void TimerWidget::stop()
{
    m_timer.stop();
    emit stopped();
}

bool TimerWidget::isRunning()
{
    return m_timer.isActive();
}

void TimerWidget::reset()
{
    m_timeLeft = m_maxTime;
    setDisplay(m_timeLeft.toString("mm:ss.zzz"));
}

void TimerWidget::updateTime()
{
    m_timeLeft.setHMS(0, m_timeLeft.addMSecs(-timerInterval).minute(), m_timeLeft.addMSecs(-timerInterval).second(), m_timeLeft.addMSecs(-timerInterval).msec());
    setDisplay(m_timeLeft.toString("mm:ss.zzz"));
    if(m_timeLeft.hour() == 0 && m_timeLeft.minute() == 0 && m_timeLeft.second() == 0)
    {
        emit finished();
        stop();
    }
}


void TimerWidget::setDisplay(QString display)
{
    ui->lcdNumber->display(display);
}
