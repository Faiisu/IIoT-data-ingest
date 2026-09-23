/********************************************************************************
** Form generated from reading UI file 'pwmoutput.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PWMOUTPUT_H
#define UI_PWMOUTPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PWMOutputClass
{
public:
    QFrame *bkgrndImage;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *hiPeriodEditor;
    QLineEdit *loPeriodEditor;
    QLabel *label_4;
    QLabel *label_5;
    QGroupBox *groupBox;
    QLabel *ExecutionStatus;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *actualLoPeriod;
    QLabel *label_9;
    QLineEdit *actualHiPeriod;
    QLabel *label_10;
    QPushButton *btnConfig;
    QPushButton *btnStart;
    QPushButton *btnStop;

    void setupUi(QDialog *PWMOutputClass)
    {
        if (PWMOutputClass->objectName().isEmpty())
            PWMOutputClass->setObjectName(QString::fromUtf8("PWMOutputClass"));
        PWMOutputClass->resize(367, 298);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PWMOutputClass->sizePolicy().hasHeightForWidth());
        PWMOutputClass->setSizePolicy(sizePolicy);
        PWMOutputClass->setMinimumSize(QSize(367, 298));
        PWMOutputClass->setMaximumSize(QSize(367, 298));
        bkgrndImage = new QFrame(PWMOutputClass);
        bkgrndImage->setObjectName(QString::fromUtf8("bkgrndImage"));
        bkgrndImage->setGeometry(QRect(211, 0, 161, 51));
        sizePolicy.setHeightForWidth(bkgrndImage->sizePolicy().hasHeightForWidth());
        bkgrndImage->setSizePolicy(sizePolicy);
        bkgrndImage->setFrameShape(QFrame::StyledPanel);
        bkgrndImage->setFrameShadow(QFrame::Raised);
        label = new QLabel(PWMOutputClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(15, 14, 91, 16));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label_2 = new QLabel(PWMOutputClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 37, 71, 20));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_3 = new QLabel(PWMOutputClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 73, 71, 20));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        hiPeriodEditor = new QLineEdit(PWMOutputClass);
        hiPeriodEditor->setObjectName(QString::fromUtf8("hiPeriodEditor"));
        hiPeriodEditor->setGeometry(QRect(90, 31, 91, 28));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hiPeriodEditor->sizePolicy().hasHeightForWidth());
        hiPeriodEditor->setSizePolicy(sizePolicy1);
        loPeriodEditor = new QLineEdit(PWMOutputClass);
        loPeriodEditor->setObjectName(QString::fromUtf8("loPeriodEditor"));
        loPeriodEditor->setGeometry(QRect(90, 69, 91, 28));
        sizePolicy1.setHeightForWidth(loPeriodEditor->sizePolicy().hasHeightForWidth());
        loPeriodEditor->setSizePolicy(sizePolicy1);
        label_4 = new QLabel(PWMOutputClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(186, 38, 16, 16));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_5 = new QLabel(PWMOutputClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(186, 75, 16, 16));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        groupBox = new QGroupBox(PWMOutputClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(16, 102, 291, 151));
        groupBox->setAutoFillBackground(true);
        ExecutionStatus = new QLabel(groupBox);
        ExecutionStatus->setObjectName(QString::fromUtf8("ExecutionStatus"));
        ExecutionStatus->setGeometry(QRect(13, 20, 241, 21));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 53, 181, 21));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(169, 121, 16, 16));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(3, 119, 71, 20));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        actualLoPeriod = new QLineEdit(groupBox);
        actualLoPeriod->setObjectName(QString::fromUtf8("actualLoPeriod"));
        actualLoPeriod->setGeometry(QRect(73, 115, 91, 28));
        sizePolicy1.setHeightForWidth(actualLoPeriod->sizePolicy().hasHeightForWidth());
        actualLoPeriod->setSizePolicy(sizePolicy1);
        actualLoPeriod->setReadOnly(true);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(169, 84, 16, 16));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        actualHiPeriod = new QLineEdit(groupBox);
        actualHiPeriod->setObjectName(QString::fromUtf8("actualHiPeriod"));
        actualHiPeriod->setGeometry(QRect(73, 77, 91, 28));
        sizePolicy1.setHeightForWidth(actualHiPeriod->sizePolicy().hasHeightForWidth());
        actualHiPeriod->setSizePolicy(sizePolicy1);
        actualHiPeriod->setReadOnly(true);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(3, 83, 71, 20));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        btnConfig = new QPushButton(PWMOutputClass);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(20, 260, 75, 23));
        btnStart = new QPushButton(PWMOutputClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(144, 261, 71, 23));
        btnStop = new QPushButton(PWMOutputClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(234, 261, 71, 23));

        retranslateUi(PWMOutputClass);

        QMetaObject::connectSlotsByName(PWMOutputClass);
    } // setupUi

    void retranslateUi(QDialog *PWMOutputClass)
    {
        PWMOutputClass->setWindowTitle(QCoreApplication::translate("PWMOutputClass", "PWM Output", nullptr));
        label->setText(QCoreApplication::translate("PWMOutputClass", "Desired period:", nullptr));
        label_2->setText(QCoreApplication::translate("PWMOutputClass", "High Period:", nullptr));
        label_3->setText(QCoreApplication::translate("PWMOutputClass", "Low  Period:", nullptr));
        label_4->setText(QCoreApplication::translate("PWMOutputClass", "S", nullptr));
        label_5->setText(QCoreApplication::translate("PWMOutputClass", "S", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PWMOutputClass", "Execution status", nullptr));
        ExecutionStatus->setText(QString());
        label_6->setText(QCoreApplication::translate("PWMOutputClass", "Device generated pulse period:", nullptr));
        label_7->setText(QCoreApplication::translate("PWMOutputClass", "S", nullptr));
        label_8->setText(QCoreApplication::translate("PWMOutputClass", "Low  Period:", nullptr));
        label_9->setText(QCoreApplication::translate("PWMOutputClass", "S", nullptr));
        label_10->setText(QCoreApplication::translate("PWMOutputClass", "High Period:", nullptr));
        btnConfig->setText(QCoreApplication::translate("PWMOutputClass", "Configure", nullptr));
        btnStart->setText(QCoreApplication::translate("PWMOutputClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("PWMOutputClass", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PWMOutputClass: public Ui_PWMOutputClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PWMOUTPUT_H
