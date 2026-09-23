/********************************************************************************
** Form generated from reading UI file 'updowncounter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDOWNCOUNTER_H
#define UI_UPDOWNCOUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_UpDownCounterClass
{
public:
    QFrame *background;
    QGroupBox *groupBox2;
    QLineEdit *txtCounterValue;
    QListWidget *CounterValueList;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnConfig;
    QPushButton *btnValReset;
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *cmbResetValue;
    QLineEdit *txtResetValue;
    QGroupBox *groupBox_2;
    QRadioButton *radDisable;
    QRadioButton *raInfinite;
    QRadioButton *radFinite;
    QLabel *label_2;
    QLineEdit *txtResetTimes;

    void setupUi(QDialog *UpDownCounterClass)
    {
        if (UpDownCounterClass->objectName().isEmpty())
            UpDownCounterClass->setObjectName(QString::fromUtf8("UpDownCounterClass"));
        UpDownCounterClass->resize(530, 311);
        UpDownCounterClass->setMinimumSize(QSize(530, 311));
        UpDownCounterClass->setMaximumSize(QSize(530, 311));
        background = new QFrame(UpDownCounterClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(1, 0, 531, 311));
        background->setMinimumSize(QSize(531, 311));
        background->setMaximumSize(QSize(531, 311));
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/UpDownCounter/Resources/Background.bmp)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        groupBox2 = new QGroupBox(background);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(214, 49, 295, 241));
        groupBox2->setMinimumSize(QSize(295, 241));
        groupBox2->setMaximumSize(QSize(295, 241));
        groupBox2->setAutoFillBackground(true);
        txtCounterValue = new QLineEdit(groupBox2);
        txtCounterValue->setObjectName(QString::fromUtf8("txtCounterValue"));
        txtCounterValue->setGeometry(QRect(24, 10, 155, 25));
        txtCounterValue->setMinimumSize(QSize(155, 25));
        txtCounterValue->setMaximumSize(QSize(155, 25));
        txtCounterValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        CounterValueList = new QListWidget(groupBox2);
        CounterValueList->setObjectName(QString::fromUtf8("CounterValueList"));
        CounterValueList->setGeometry(QRect(24, 46, 155, 181));
        CounterValueList->setMinimumSize(QSize(155, 181));
        CounterValueList->setMaximumSize(QSize(155, 181));
        CounterValueList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        btnStart = new QPushButton(groupBox2);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(203, 20, 75, 23));
        btnStart->setMinimumSize(QSize(75, 23));
        btnStart->setMaximumSize(QSize(75, 23));
        btnStop = new QPushButton(groupBox2);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(203, 66, 75, 23));
        btnStop->setMinimumSize(QSize(75, 23));
        btnStop->setMaximumSize(QSize(75, 23));
        btnConfig = new QPushButton(groupBox2);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(203, 184, 75, 23));
        btnConfig->setMinimumSize(QSize(75, 23));
        btnConfig->setMaximumSize(QSize(75, 23));
        btnValReset = new QPushButton(groupBox2);
        btnValReset->setObjectName(QString::fromUtf8("btnValReset"));
        btnValReset->setGeometry(QRect(203, 110, 75, 23));
        btnValReset->setMinimumSize(QSize(75, 23));
        btnValReset->setMaximumSize(QSize(75, 23));
        groupBox = new QGroupBox(background);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(11, 44, 191, 81));
        groupBox->setMinimumSize(QSize(191, 81));
        groupBox->setMaximumSize(QSize(191, 81));
        groupBox->setAutoFillBackground(true);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 71, 16));
        label->setMinimumSize(QSize(71, 16));
        label->setMaximumSize(QSize(71, 16));
        cmbResetValue = new QComboBox(groupBox);
        cmbResetValue->setObjectName(QString::fromUtf8("cmbResetValue"));
        cmbResetValue->setGeometry(QRect(90, 20, 91, 22));
        cmbResetValue->setMinimumSize(QSize(91, 22));
        cmbResetValue->setMaximumSize(QSize(91, 22));
        txtResetValue = new QLineEdit(groupBox);
        txtResetValue->setObjectName(QString::fromUtf8("txtResetValue"));
        txtResetValue->setEnabled(false);
        txtResetValue->setGeometry(QRect(90, 50, 91, 22));
        txtResetValue->setMinimumSize(QSize(91, 22));
        txtResetValue->setMaximumSize(QSize(91, 22));
        groupBox_2 = new QGroupBox(background);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 131, 191, 150));
        groupBox_2->setMinimumSize(QSize(191, 150));
        groupBox_2->setMaximumSize(QSize(191, 150));
        radDisable = new QRadioButton(groupBox_2);
        radDisable->setObjectName(QString::fromUtf8("radDisable"));
        radDisable->setEnabled(true);
        radDisable->setGeometry(QRect(15, 21, 89, 16));
        radDisable->setMinimumSize(QSize(89, 16));
        radDisable->setMaximumSize(QSize(89, 16));
        radDisable->setCheckable(true);
        radDisable->setChecked(false);
        raInfinite = new QRadioButton(groupBox_2);
        raInfinite->setObjectName(QString::fromUtf8("raInfinite"));
        raInfinite->setEnabled(true);
        raInfinite->setGeometry(QRect(15, 51, 89, 16));
        raInfinite->setMinimumSize(QSize(89, 16));
        raInfinite->setMaximumSize(QSize(89, 16));
        radFinite = new QRadioButton(groupBox_2);
        radFinite->setObjectName(QString::fromUtf8("radFinite"));
        radFinite->setEnabled(true);
        radFinite->setGeometry(QRect(15, 81, 89, 16));
        radFinite->setMinimumSize(QSize(89, 16));
        radFinite->setMaximumSize(QSize(89, 16));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(15, 113, 71, 16));
        label_2->setMinimumSize(QSize(71, 16));
        label_2->setMaximumSize(QSize(71, 16));
        txtResetTimes = new QLineEdit(groupBox_2);
        txtResetTimes->setObjectName(QString::fromUtf8("txtResetTimes"));
        txtResetTimes->setEnabled(false);
        txtResetTimes->setGeometry(QRect(90, 111, 91, 24));
        txtResetTimes->setMinimumSize(QSize(91, 24));
        txtResetTimes->setMaximumSize(QSize(91, 24));

        retranslateUi(UpDownCounterClass);

        QMetaObject::connectSlotsByName(UpDownCounterClass);
    } // setupUi

    void retranslateUi(QDialog *UpDownCounterClass)
    {
        UpDownCounterClass->setWindowTitle(QCoreApplication::translate("UpDownCounterClass", "Counter_UpDownCounter", nullptr));
        groupBox2->setTitle(QString());
        btnStart->setText(QCoreApplication::translate("UpDownCounterClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("UpDownCounterClass", "Stop", nullptr));
        btnConfig->setText(QCoreApplication::translate("UpDownCounterClass", "Configure...", nullptr));
        btnValReset->setText(QCoreApplication::translate("UpDownCounterClass", "ValueReset", nullptr));
        groupBox->setTitle(QCoreApplication::translate("UpDownCounterClass", "Reset Value", nullptr));
        label->setText(QCoreApplication::translate("UpDownCounterClass", "Reset Value:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("UpDownCounterClass", "Index Reset", nullptr));
        radDisable->setText(QCoreApplication::translate("UpDownCounterClass", "Disable", nullptr));
        raInfinite->setText(QCoreApplication::translate("UpDownCounterClass", "Infinite", nullptr));
        radFinite->setText(QCoreApplication::translate("UpDownCounterClass", "Finite", nullptr));
        label_2->setText(QCoreApplication::translate("UpDownCounterClass", "Reset Times:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UpDownCounterClass: public Ui_UpDownCounterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDOWNCOUNTER_H
