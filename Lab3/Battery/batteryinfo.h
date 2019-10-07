#ifndef BATTERYINFO_H
#define BATTERYINFO_H
#include <QThread>
#include <QObject>
#include "batterywindow.h"
class BatteryWindow;
class BatteryInfo : public QThread
{
    Q_OBJECT
    void setACLineStatus(unsigned char st);
    void setBatteryLifePercent(unsigned char per);
    void setPowerSaveFlag(bool);
public:
    BatteryInfo(BatteryWindow* parent);
    void getInfo();
    void run();
signals:
    void sendTypeOfEnergy(QString type);
    void sendChargeValue(unsigned char value);
    void sendTypeOfEnergySave(QString type);
};

class Hibernator : public QThread
{
public:
    Hibernator();
    void run();
};

#endif // BATTERYINFO_H
