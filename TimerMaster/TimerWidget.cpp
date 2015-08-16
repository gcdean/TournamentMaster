#include "TimerWidget.h"
#include "ui_TimerWidget.h"

TimerWidget::TimerWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);
}

TimerWidget::~TimerWidget()
{
    delete ui;
}
