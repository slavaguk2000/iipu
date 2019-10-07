#include "batterywindow.h"
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "batteryinfo.h"
#include "hibernator.h"

const unsigned char maxPercent = 100;

QHBoxLayout* BatteryWindow::createTypeOfEnergyLayout()
{
    QHBoxLayout* typeOfEnergyLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Type of power supply: ", this);
    typeOfEnergyValue = new QLabel(this);
    typeOfEnergyLayout->addWidget(label);
    typeOfEnergyLayout->addWidget(typeOfEnergyValue);
    return typeOfEnergyLayout;
}

void BatteryWindow::setTypeOfEnergy(QString type)
{
    typeOfEnergyValue->setText(type);
}

QHBoxLayout* BatteryWindow::createLevelOfChargeLayout()
{
    QHBoxLayout* levelOfChargeLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Level of charge: ", this);
    levelOfCharge = new QProgressBar(this);
    levelOfCharge->setMaximum(maxPercent);
    levelOfChargeValue = new QLabel(this);
    levelOfChargeLayout->addWidget(label);
    levelOfChargeLayout->addWidget(levelOfChargeValue);
    levelOfChargeLayout->addWidget(levelOfCharge);
    return levelOfChargeLayout;
}

void BatteryWindow::setChargeValue(unsigned char value)
{
    if (value > maxPercent) return;
    QString level = "";
    if (value == 255) level = "Unknown";
    else levelOfCharge->setValue(value);
    levelOfChargeValue->setText(level);    
}

QHBoxLayout* BatteryWindow::createTypeOfEnergySaveLayout()
{
    QHBoxLayout* typeOfEnergySaveLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Power saving mode: ", this);
    typeOfEnergySaveValue = new QLabel(this);
    typeOfEnergySaveLayout->addWidget(label);
    typeOfEnergySaveLayout->addWidget(typeOfEnergySaveValue);
    return typeOfEnergySaveLayout;
}

void BatteryWindow::setTypeOfEnergySave(QString type)
{
    typeOfEnergySaveValue->setText(type);
}

QPushButton* BatteryWindow::createStartOfHibernationButton()
{
    QPushButton* startOfHibernationButton = new QPushButton("Hibernation", this);
    connect(startOfHibernationButton, &QPushButton::clicked, this, &BatteryWindow::hibernation);
    return startOfHibernationButton;
}

BatteryWindow::BatteryWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(createTypeOfEnergyLayout());
    mainLayout->addLayout(createLevelOfChargeLayout());
    mainLayout->addLayout(createTypeOfEnergySaveLayout());
    mainLayout->addWidget(createStartOfHibernationButton());
    setLayout(mainLayout);
    BatteryInfo* batteryInfo = new BatteryInfo(this);
    batteryInfo->start();
}

void BatteryWindow::hibernation()
{
    Hibernator* hibernator = new Hibernator();
    hibernator->start();
}

BatteryWindow::~BatteryWindow()
{

}
