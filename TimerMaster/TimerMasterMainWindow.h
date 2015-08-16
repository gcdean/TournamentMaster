#ifndef TIMERMASTERMAINWINDOW_H
#define TIMERMASTERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class TimerMasterMainWindow;
}

class TimerMasterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimerMasterMainWindow(QWidget *parent = 0);
    ~TimerMasterMainWindow();


private:
    Ui::TimerMasterMainWindow *ui;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // TIMERMASTERMAINWINDOW_H
