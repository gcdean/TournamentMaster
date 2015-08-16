#include "TimerMasterMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimerMasterMainWindow w;
    w.show();

    return a.exec();
}
