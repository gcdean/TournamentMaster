#include "TimerMasterMainWindow.h"
#include "ui_TimerMasterMainWindow.h"

TimerMasterMainWindow::TimerMasterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimerMasterMainWindow)
{
    ui->setupUi(this);
}

TimerMasterMainWindow::~TimerMasterMainWindow()
{
    delete ui;
}
