#include "batteryinfo.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <WinIoCtl.h>
#include <ntddscsi.h>
#include <conio.h>
#include <QMessageBox>

using namespace std;

void BatteryInfo::run()
{
    while(true)
    {
        getInfo();
    }
}

void BatteryInfo::setACLineStatus(unsigned char st)
{
    QString typeOfEnergy;
    switch (st) {
    case 0:
    typeOfEnergy = "Buttery";
    break;
    case 1:
    typeOfEnergy = "ACLine";
    break;
    default:
    typeOfEnergy = "Unknown";
    break;
    }
    emit sendTypeOfEnergy(typeOfEnergy);
}

void BatteryInfo::setBatteryLifePercent(unsigned char per)
{
    if(per > 100 && per < 255) return;
    emit sendChargeValue(per);
}

void BatteryInfo::setPowerSaveFlag(bool flag)
{
    QString powerSaveMode = "Battery saver ";
    if(flag) powerSaveMode += "on";
    else powerSaveMode += "off";
    emit sendTypeOfEnergySave(powerSaveMode);
}

void BatteryInfo::getInfo()
{
    SYSTEM_POWER_STATUS batteryState;
    if ( !GetSystemPowerStatus(&batteryState)) {
        //QMessageBox errorMessage(QString::number(GetLastError()));
        return;
    }
    setACLineStatus(batteryState.ACLineStatus);
    setBatteryLifePercent(batteryState.BatteryLifePercent);
    setPowerSaveFlag(batteryState.SystemStatusFlag == 1?true:false);
}

BatteryInfo::BatteryInfo(BatteryWindow* parent)
{
    connect(this, &BatteryInfo::sendChargeValue, parent, &BatteryWindow::setChargeValue);
    connect(this, &BatteryInfo::sendTypeOfEnergy, parent, &BatteryWindow::setTypeOfEnergy);
    connect(this, &BatteryInfo::sendTypeOfEnergySave, parent, &BatteryWindow::setTypeOfEnergySave);
}

Hibernator::Hibernator()
{

}

void Hibernator::run()
{
    system("shutdown /h");
}
