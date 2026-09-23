/********************************************************************************
** Form generated from reading UI file 'continuecompare.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTINUECOMPARE_H
#define UI_CONTINUECOMPARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_ContinueCompareClass
{
public:
    QFrame *background;
    QGroupBox *groupBox;
    QGroupBox *groupBox_4;
    QLabel *label;
    QLineEdit *txtTab1Data0;
    QLineEdit *txtTab1Data1;
    QLabel *label_2;
    QLineEdit *txtTab1Data2;
    QLabel *label_3;
    QGroupBox *groupBox_5;
    QLabel *label_4;
    QLineEdit *txtTab2Data0;
    QLineEdit *txtTab2Data1;
    QLabel *label_5;
    QLineEdit *txtTab2Data2;
    QLabel *label_6;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_6;
    QLabel *label_7;
    QLineEdit *txtInt1FirstValue;
    QLineEdit *txtInt1Increment;
    QLabel *label_8;
    QLineEdit *txtInt1Count;
    QLabel *label_9;
    QGroupBox *groupBox_7;
    QLabel *label_10;
    QLineEdit *txtInt2FirstValue;
    QLineEdit *txtInt2Increment;
    QLabel *label_11;
    QLineEdit *txtInt2Count;
    QLabel *label_12;
    QGroupBox *groupBox_3;
    QLineEdit *txtCounterValue;
    QPushButton *btnConfig;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QRadioButton *radTable;
    QRadioButton *radInterval;
    QLabel *label_13;
    QLineEdit *txtPMCount;
    QLabel *label_14;
    QLineEdit *txtEndCount;

    void setupUi(QDialog *ContinueCompareClass)
    {
        if (ContinueCompareClass->objectName().isEmpty())
            ContinueCompareClass->setObjectName(QString::fromUtf8("ContinueCompareClass"));
        ContinueCompareClass->resize(532, 315);
        ContinueCompareClass->setMinimumSize(QSize(532, 315));
        ContinueCompareClass->setMaximumSize(QSize(532, 315));
        background = new QFrame(ContinueCompareClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(0, 0, 532, 321));
        background->setMaximumSize(QSize(532, 321));
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/ContinueCompare/Resources/Background.bmp)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(background);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 49, 171, 215));
        groupBox->setMinimumSize(QSize(171, 215));
        groupBox->setMaximumSize(QSize(171, 215));
        groupBox->setAutoFillBackground(true);
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 10, 152, 92));
        groupBox_4->setMinimumSize(QSize(152, 92));
        groupBox_4->setMaximumSize(QSize(152, 92));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 17, 81, 16));
        label->setMinimumSize(QSize(81, 16));
        label->setMaximumSize(QSize(81, 16));
        txtTab1Data0 = new QLineEdit(groupBox_4);
        txtTab1Data0->setObjectName(QString::fromUtf8("txtTab1Data0"));
        txtTab1Data0->setGeometry(QRect(85, 16, 61, 20));
        txtTab1Data0->setMinimumSize(QSize(61, 20));
        txtTab1Data0->setMaximumSize(QSize(61, 20));
        txtTab1Data1 = new QLineEdit(groupBox_4);
        txtTab1Data1->setObjectName(QString::fromUtf8("txtTab1Data1"));
        txtTab1Data1->setGeometry(QRect(85, 42, 61, 20));
        txtTab1Data1->setMinimumSize(QSize(61, 20));
        txtTab1Data1->setMaximumSize(QSize(61, 20));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(6, 43, 81, 16));
        label_2->setMinimumSize(QSize(81, 16));
        label_2->setMaximumSize(QSize(81, 16));
        txtTab1Data2 = new QLineEdit(groupBox_4);
        txtTab1Data2->setObjectName(QString::fromUtf8("txtTab1Data2"));
        txtTab1Data2->setGeometry(QRect(85, 66, 61, 20));
        txtTab1Data2->setMinimumSize(QSize(61, 20));
        txtTab1Data2->setMaximumSize(QSize(61, 20));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(6, 67, 81, 16));
        label_3->setMinimumSize(QSize(81, 16));
        label_3->setMaximumSize(QSize(81, 16));
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 110, 152, 92));
        groupBox_5->setMinimumSize(QSize(152, 92));
        groupBox_5->setMaximumSize(QSize(152, 92));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(6, 17, 81, 16));
        label_4->setMinimumSize(QSize(81, 16));
        label_4->setMaximumSize(QSize(81, 16));
        txtTab2Data0 = new QLineEdit(groupBox_5);
        txtTab2Data0->setObjectName(QString::fromUtf8("txtTab2Data0"));
        txtTab2Data0->setGeometry(QRect(85, 16, 61, 20));
        txtTab2Data0->setMinimumSize(QSize(61, 20));
        txtTab2Data0->setMaximumSize(QSize(61, 20));
        txtTab2Data1 = new QLineEdit(groupBox_5);
        txtTab2Data1->setObjectName(QString::fromUtf8("txtTab2Data1"));
        txtTab2Data1->setGeometry(QRect(85, 42, 61, 20));
        txtTab2Data1->setMinimumSize(QSize(61, 20));
        txtTab2Data1->setMaximumSize(QSize(61, 20));
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(6, 43, 81, 16));
        label_5->setMinimumSize(QSize(81, 16));
        label_5->setMaximumSize(QSize(81, 16));
        txtTab2Data2 = new QLineEdit(groupBox_5);
        txtTab2Data2->setObjectName(QString::fromUtf8("txtTab2Data2"));
        txtTab2Data2->setGeometry(QRect(85, 66, 61, 20));
        txtTab2Data2->setMinimumSize(QSize(61, 20));
        txtTab2Data2->setMaximumSize(QSize(61, 20));
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(6, 67, 81, 16));
        label_6->setMinimumSize(QSize(81, 16));
        label_6->setMaximumSize(QSize(81, 16));
        groupBox_2 = new QGroupBox(background);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(197, 49, 161, 215));
        groupBox_2->setMinimumSize(QSize(161, 215));
        groupBox_2->setMaximumSize(QSize(161, 215));
        groupBox_2->setAutoFillBackground(true);
        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 11, 141, 92));
        groupBox_6->setMinimumSize(QSize(141, 92));
        groupBox_6->setMaximumSize(QSize(141, 92));
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(6, 17, 63, 16));
        label_7->setMinimumSize(QSize(63, 16));
        label_7->setMaximumSize(QSize(63, 16));
        txtInt1FirstValue = new QLineEdit(groupBox_6);
        txtInt1FirstValue->setObjectName(QString::fromUtf8("txtInt1FirstValue"));
        txtInt1FirstValue->setGeometry(QRect(74, 16, 61, 20));
        txtInt1FirstValue->setMinimumSize(QSize(61, 20));
        txtInt1FirstValue->setMaximumSize(QSize(61, 20));
        txtInt1Increment = new QLineEdit(groupBox_6);
        txtInt1Increment->setObjectName(QString::fromUtf8("txtInt1Increment"));
        txtInt1Increment->setGeometry(QRect(74, 42, 61, 20));
        txtInt1Increment->setMinimumSize(QSize(61, 20));
        txtInt1Increment->setMaximumSize(QSize(61, 20));
        label_8 = new QLabel(groupBox_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(6, 43, 61, 16));
        label_8->setMinimumSize(QSize(61, 16));
        label_8->setMaximumSize(QSize(61, 16));
        txtInt1Count = new QLineEdit(groupBox_6);
        txtInt1Count->setObjectName(QString::fromUtf8("txtInt1Count"));
        txtInt1Count->setGeometry(QRect(74, 66, 61, 20));
        txtInt1Count->setMinimumSize(QSize(61, 20));
        txtInt1Count->setMaximumSize(QSize(61, 20));
        label_9 = new QLabel(groupBox_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(6, 67, 41, 16));
        label_9->setMinimumSize(QSize(41, 16));
        label_9->setMaximumSize(QSize(41, 16));
        groupBox_7 = new QGroupBox(groupBox_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(9, 111, 141, 92));
        groupBox_7->setMinimumSize(QSize(141, 92));
        groupBox_7->setMaximumSize(QSize(141, 92));
        label_10 = new QLabel(groupBox_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(6, 17, 63, 16));
        label_10->setMinimumSize(QSize(63, 16));
        label_10->setMaximumSize(QSize(63, 16));
        txtInt2FirstValue = new QLineEdit(groupBox_7);
        txtInt2FirstValue->setObjectName(QString::fromUtf8("txtInt2FirstValue"));
        txtInt2FirstValue->setGeometry(QRect(74, 16, 61, 20));
        txtInt2FirstValue->setMinimumSize(QSize(61, 20));
        txtInt2FirstValue->setMaximumSize(QSize(61, 20));
        txtInt2Increment = new QLineEdit(groupBox_7);
        txtInt2Increment->setObjectName(QString::fromUtf8("txtInt2Increment"));
        txtInt2Increment->setGeometry(QRect(74, 42, 61, 20));
        txtInt2Increment->setMinimumSize(QSize(61, 20));
        txtInt2Increment->setMaximumSize(QSize(61, 20));
        label_11 = new QLabel(groupBox_7);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(6, 43, 61, 16));
        label_11->setMinimumSize(QSize(61, 16));
        label_11->setMaximumSize(QSize(61, 16));
        txtInt2Count = new QLineEdit(groupBox_7);
        txtInt2Count->setObjectName(QString::fromUtf8("txtInt2Count"));
        txtInt2Count->setGeometry(QRect(74, 66, 61, 20));
        txtInt2Count->setMinimumSize(QSize(61, 20));
        txtInt2Count->setMaximumSize(QSize(61, 20));
        label_12 = new QLabel(groupBox_7);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(6, 67, 41, 16));
        label_12->setMinimumSize(QSize(41, 16));
        label_12->setMaximumSize(QSize(41, 16));
        groupBox_3 = new QGroupBox(background);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(380, 50, 131, 215));
        groupBox_3->setMinimumSize(QSize(131, 215));
        groupBox_3->setMaximumSize(QSize(131, 215));
        groupBox_3->setAutoFillBackground(true);
        txtCounterValue = new QLineEdit(groupBox_3);
        txtCounterValue->setObjectName(QString::fromUtf8("txtCounterValue"));
        txtCounterValue->setGeometry(QRect(13, 10, 110, 25));
        txtCounterValue->setMinimumSize(QSize(110, 25));
        txtCounterValue->setMaximumSize(QSize(110, 25));
        txtCounterValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnConfig = new QPushButton(groupBox_3);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(34, 165, 75, 23));
        btnConfig->setMinimumSize(QSize(75, 23));
        btnConfig->setMaximumSize(QSize(75, 23));
        btnStart = new QPushButton(groupBox_3);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(34, 50, 75, 23));
        btnStart->setMinimumSize(QSize(75, 23));
        btnStart->setMaximumSize(QSize(75, 23));
        btnStop = new QPushButton(groupBox_3);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(34, 100, 75, 23));
        btnStop->setMinimumSize(QSize(75, 23));
        btnStop->setMaximumSize(QSize(75, 23));
        radTable = new QRadioButton(background);
        radTable->setObjectName(QString::fromUtf8("radTable"));
        radTable->setGeometry(QRect(20, 42, 101, 16));
        radTable->setMinimumSize(QSize(101, 16));
        radTable->setMaximumSize(QSize(101, 16));
        radTable->setAutoFillBackground(true);
        radTable->setChecked(true);
        radInterval = new QRadioButton(background);
        radInterval->setObjectName(QString::fromUtf8("radInterval"));
        radInterval->setGeometry(QRect(207, 42, 121, 16));
        radInterval->setMinimumSize(QSize(121, 16));
        radInterval->setMaximumSize(QSize(121, 16));
        radInterval->setAutoFillBackground(true);
        label_13 = new QLabel(background);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 280, 202, 16));
        label_13->setMinimumSize(QSize(202, 16));
        label_13->setMaximumSize(QSize(202, 16));
        txtPMCount = new QLineEdit(background);
        txtPMCount->setObjectName(QString::fromUtf8("txtPMCount"));
        txtPMCount->setEnabled(true);
        txtPMCount->setGeometry(QRect(198, 277, 70, 25));
        txtPMCount->setMinimumSize(QSize(70, 25));
        txtPMCount->setMaximumSize(QSize(81, 25));
        txtPMCount->setReadOnly(true);
        label_14 = new QLabel(background);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(278, 281, 141, 16));
        label_14->setMinimumSize(QSize(141, 16));
        label_14->setMaximumSize(QSize(141, 16));
        txtEndCount = new QLineEdit(background);
        txtEndCount->setObjectName(QString::fromUtf8("txtEndCount"));
        txtEndCount->setEnabled(true);
        txtEndCount->setGeometry(QRect(425, 278, 81, 25));
        txtEndCount->setMinimumSize(QSize(81, 25));
        txtEndCount->setMaximumSize(QSize(81, 25));
        txtEndCount->setReadOnly(true);

        retranslateUi(ContinueCompareClass);

        QMetaObject::connectSlotsByName(ContinueCompareClass);
    } // setupUi

    void retranslateUi(QDialog *ContinueCompareClass)
    {
        ContinueCompareClass->setWindowTitle(QCoreApplication::translate("ContinueCompareClass", "Counter_ContinueCompare", nullptr));
        groupBox->setTitle(QString());
        groupBox_4->setTitle(QCoreApplication::translate("ContinueCompareClass", "Table 1", nullptr));
        label->setText(QCoreApplication::translate("ContinueCompareClass", "CompareData0:", nullptr));
        label_2->setText(QCoreApplication::translate("ContinueCompareClass", "CompareData1:", nullptr));
        label_3->setText(QCoreApplication::translate("ContinueCompareClass", "CompareData2:", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("ContinueCompareClass", "Table 2", nullptr));
        label_4->setText(QCoreApplication::translate("ContinueCompareClass", "CompareData0:", nullptr));
        label_5->setText(QCoreApplication::translate("ContinueCompareClass", "CompareData1:", nullptr));
        label_6->setText(QCoreApplication::translate("ContinueCompareClass", "CompareData2:", nullptr));
        groupBox_2->setTitle(QString());
        groupBox_6->setTitle(QCoreApplication::translate("ContinueCompareClass", "Interval 1", nullptr));
        label_7->setText(QCoreApplication::translate("ContinueCompareClass", "FirstValue:", nullptr));
        label_8->setText(QCoreApplication::translate("ContinueCompareClass", "Increment:", nullptr));
        label_9->setText(QCoreApplication::translate("ContinueCompareClass", "Count:", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("ContinueCompareClass", "Interval 2", nullptr));
        label_10->setText(QCoreApplication::translate("ContinueCompareClass", "FirstValue:", nullptr));
        label_11->setText(QCoreApplication::translate("ContinueCompareClass", "Increment:", nullptr));
        label_12->setText(QCoreApplication::translate("ContinueCompareClass", "Count:", nullptr));
        groupBox_3->setTitle(QString());
        btnConfig->setText(QCoreApplication::translate("ContinueCompareClass", "Configure...", nullptr));
        btnStart->setText(QCoreApplication::translate("ContinueCompareClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("ContinueCompareClass", "Stop", nullptr));
        radTable->setText(QCoreApplication::translate("ContinueCompareClass", "Compare table", nullptr));
        radInterval->setText(QCoreApplication::translate("ContinueCompareClass", "Compare interval", nullptr));
        label_13->setText(QCoreApplication::translate("ContinueCompareClass", "Pattern match event capture count:", nullptr));
        label_14->setText(QCoreApplication::translate("ContinueCompareClass", "Compare table end count:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContinueCompareClass: public Ui_ContinueCompareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTINUECOMPARE_H
