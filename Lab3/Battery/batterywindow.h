#ifndef BATTERYWINDOW_H
#define BATTERYWINDOW_H

#include <QWidget>

namespace Ui {
class BatteryWindow;
}

class QHBoxLayout;
class QLabel;
class QProgressBar;
class QPushButton;

class BatteryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BatteryWindow(QWidget *parent = nullptr);
    ~BatteryWindow();

private:
    QHBoxLayout* createTypeOfEnergyLayout();
    QHBoxLayout* createLevelOfChargeLayout();
    QHBoxLayout* createTypeOfEnergySaveLayout();
    QPushButton* createStartOfHibernationButton();

    QLabel* typeOfEnergyValue;
    QLabel* levelOfChargeValue;
    QProgressBar* levelOfCharge;
    QLabel* typeOfEnergySaveValue;
    QPushButton* *hibernationButton;
private slots:
    void hibernation();
public slots:
    void setTypeOfEnergy(QString type);
    void setChargeValue(unsigned char value);
    void setTypeOfEnergySave(QString type);
};

#endif // BATTERYWINDOW_H
