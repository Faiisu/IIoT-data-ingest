/********************************************************************************
** Form generated from reading UI file 'pulseoutputwithtimerinterrupt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PULSEOUTPUTWITHTIMERINTERRUPT_H
#define UI_PULSEOUTPUTWITHTIMERINTERRUPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PulseOutputwithTimerInterruptClass
{
public:
    QFrame *bkgrndImage;
    QLabel *label;
    QLineEdit *userFreqEditor;
    QLabel *label_2;
    QGroupBox *groupBox;
    QLabel *ExecutionStatus;
    QLabel *label_3;
    QLineEdit *devFreqEditor;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *evtCountEditor;
    QPushButton *btnConfig;
    QPushButton *btnStart;
    QPushButton *btnStop;

    void setupUi(QDialog *PulseOutputwithTimerInterruptClass)
    {
        if (PulseOutputwithTimerInterruptClass->objectName().isEmpty())
            PulseOutputwithTimerInterruptClass->setObjectName(QString::fromUtf8("PulseOutputwithTimerInterruptClass"));
        PulseOutputwithTimerInterruptClass->resize(363, 299);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PulseOutputwithTimerInterruptClass->sizePolicy().hasHeightForWidth());
        PulseOutputwithTimerInterruptClass->setSizePolicy(sizePolicy);
        PulseOutputwithTimerInterruptClass->setMinimumSize(QSize(363, 299));
        PulseOutputwithTimerInterruptClass->setMaximumSize(QSize(363, 299));
        bkgrndImage = new QFrame(PulseOutputwithTimerInterruptClass);
        bkgrndImage->setObjectName(QString::fromUtf8("bkgrndImage"));
        bkgrndImage->setGeometry(QRect(237, 0, 151, 51));
        bkgrndImage->setFrameShape(QFrame::StyledPanel);
        bkgrndImage->setFrameShadow(QFrame::Raised);
        label = new QLabel(PulseOutputwithTimerInterruptClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(25, 14, 121, 16));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        userFreqEditor = new QLineEdit(PulseOutputwithTimerInterruptClass);
        userFreqEditor->setObjectName(QString::fromUtf8("userFreqEditor"));
        userFreqEditor->setGeometry(QRect(24, 36, 171, 28));
        sizePolicy.setHeightForWidth(userFreqEditor->sizePolicy().hasHeightForWidth());
        userFreqEditor->setSizePolicy(sizePolicy);
        label_2 = new QLabel(PulseOutputwithTimerInterruptClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 42, 16, 16));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        groupBox = new QGroupBox(PulseOutputwithTimerInterruptClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 70, 321, 181));
        groupBox->setAutoFillBackground(true);
        ExecutionStatus = new QLabel(groupBox);
        ExecutionStatus->setObjectName(QString::fromUtf8("ExecutionStatus"));
        ExecutionStatus->setGeometry(QRect(15, 20, 261, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(13, 54, 211, 16));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(171, 0));
        devFreqEditor = new QLineEdit(groupBox);
        devFreqEditor->setObjectName(QString::fromUtf8("devFreqEditor"));
        devFreqEditor->setGeometry(QRect(13, 75, 171, 28));
        sizePolicy.setHeightForWidth(devFreqEditor->sizePolicy().hasHeightForWidth());
        devFreqEditor->setSizePolicy(sizePolicy);
        devFreqEditor->setReadOnly(true);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(189, 80, 16, 16));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(12, 118, 221, 16));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(181, 0));
        evtCountEditor = new QLineEdit(groupBox);
        evtCountEditor->setObjectName(QString::fromUtf8("evtCountEditor"));
        evtCountEditor->setGeometry(QRect(12, 140, 171, 28));
        sizePolicy.setHeightForWidth(evtCountEditor->sizePolicy().hasHeightForWidth());
        evtCountEditor->setSizePolicy(sizePolicy);
        evtCountEditor->setReadOnly(true);
        btnConfig = new QPushButton(PulseOutputwithTimerInterruptClass);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(20, 260, 75, 23));
        btnStart = new QPushButton(PulseOutputwithTimerInterruptClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(154, 260, 71, 23));
        btnStop = new QPushButton(PulseOutputwithTimerInterruptClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(250, 260, 71, 23));

        retranslateUi(PulseOutputwithTimerInterruptClass);

        QMetaObject::connectSlotsByName(PulseOutputwithTimerInterruptClass);
    } // setupUi

    void retranslateUi(QDialog *PulseOutputwithTimerInterruptClass)
    {
        PulseOutputwithTimerInterruptClass->setWindowTitle(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Pulse Output with Timer Interrupt", nullptr));
        label->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Desired frequency:", nullptr));
        label_2->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Hz", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Execution status", nullptr));
        ExecutionStatus->setText(QString());
        label_3->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Device generated pulse frequency:", nullptr));
        label_4->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Hz", nullptr));
        label_5->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Device generated timer event count:", nullptr));
        btnConfig->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Configure", nullptr));
        btnStart->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("PulseOutputwithTimerInterruptClass", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PulseOutputwithTimerInterruptClass: public Ui_PulseOutputwithTimerInterruptClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PULSEOUTPUTWITHTIMERINTERRUPT_H
