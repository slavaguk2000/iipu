#include "batterywindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BatteryWindow w;
    w.show();

    return a.exec();
}
