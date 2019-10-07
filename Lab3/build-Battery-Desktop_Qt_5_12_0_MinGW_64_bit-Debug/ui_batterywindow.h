/********************************************************************************
** Form generated from reading UI file 'batterywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTERYWINDOW_H
#define UI_BATTERYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BatteryWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QProgressBar *BatteryLevel_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BatteryWindow)
    {
        if (BatteryWindow->objectName().isEmpty())
            BatteryWindow->setObjectName(QString::fromUtf8("BatteryWindow"));
        BatteryWindow->resize(400, 300);
        BatteryWindow->setMinimumSize(QSize(400, 300));
        BatteryWindow->setMaximumSize(QSize(400, 300));
        centralWidget = new QWidget(BatteryWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(400, 247));
        centralWidget->setMaximumSize(QSize(400, 247));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(5, -1, 391, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        BatteryLevel_2 = new QProgressBar(verticalLayoutWidget);
        BatteryLevel_2->setObjectName(QString::fromUtf8("BatteryLevel_2"));
        BatteryLevel_2->setValue(24);

        horizontalLayout_2->addWidget(BatteryLevel_2);


        verticalLayout->addLayout(horizontalLayout_2);

        BatteryWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BatteryWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        BatteryWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BatteryWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BatteryWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BatteryWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BatteryWindow->setStatusBar(statusBar);

        retranslateUi(BatteryWindow);

        QMetaObject::connectSlotsByName(BatteryWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BatteryWindow)
    {
        BatteryWindow->setWindowTitle(QApplication::translate("BatteryWindow", "BatteryWindow", nullptr));
        label_2->setText(QApplication::translate("BatteryWindow", "Battery Level:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BatteryWindow: public Ui_BatteryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTERYWINDOW_H
