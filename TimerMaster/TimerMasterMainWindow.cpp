#include "TimerMasterMainWindow.h"
#include "ui_TimerMasterMainWindow.h"

#include <QKeyEvent>
#include <QTime>

TimerMasterMainWindow::TimerMasterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimerMasterMainWindow)
{
    ui->setupUi(this);
    ui->timerWidget->setTime(QTime(0,1, 10));
    //ui->timerWidget->start();
}

TimerMasterMainWindow::~TimerMasterMainWindow()
{
    delete ui;
}


void TimerMasterMainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        if(ui->timerWidget->isRunning())
        {
            ui->timerWidget->stop();
        }
        else
        {
            ui->timerWidget->start();
        }
    }
    else if(event->key() == Qt::Key_Escape)
    {
        ui->timerWidget->stop();
        ui->timerWidget->reset();
    }
}
