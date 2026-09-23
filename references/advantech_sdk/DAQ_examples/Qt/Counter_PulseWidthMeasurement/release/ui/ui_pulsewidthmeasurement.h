/********************************************************************************
** Form generated from reading UI file 'pulsewidthmeasurement.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PULSEWIDTHMEASUREMENT_H
#define UI_PULSEWIDTHMEASUREMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PulseWidthMeasurementClass
{
public:
    QFrame *bkgrndImage;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *hiPeriodEditor;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *loPeriodEditor;
    QLabel *label_4;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnConfig;
    QListWidget *cntrValueList;

    void setupUi(QDialog *PulseWidthMeasurementClass)
    {
        if (PulseWidthMeasurementClass->objectName().isEmpty())
            PulseWidthMeasurementClass->setObjectName(QString::fromUtf8("PulseWidthMeasurementClass"));
        PulseWidthMeasurementClass->resize(358, 279);
        PulseWidthMeasurementClass->setMinimumSize(QSize(358, 279));
        PulseWidthMeasurementClass->setMaximumSize(QSize(358, 279));
        bkgrndImage = new QFrame(PulseWidthMeasurementClass);
        bkgrndImage->setObjectName(QString::fromUtf8("bkgrndImage"));
        bkgrndImage->setGeometry(QRect(200, -4, 162, 59));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bkgrndImage->sizePolicy().hasHeightForWidth());
        bkgrndImage->setSizePolicy(sizePolicy);
        bkgrndImage->setFrameShape(QFrame::StyledPanel);
        bkgrndImage->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(PulseWidthMeasurementClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(17, 47, 321, 221));
        groupBox->setAutoFillBackground(true);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 14, 71, 21));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        hiPeriodEditor = new QLineEdit(groupBox);
        hiPeriodEditor->setObjectName(QString::fromUtf8("hiPeriodEditor"));
        hiPeriodEditor->setGeometry(QRect(80, 10, 101, 29));
        sizePolicy.setHeightForWidth(hiPeriodEditor->sizePolicy().hasHeightForWidth());
        hiPeriodEditor->setSizePolicy(sizePolicy);
        hiPeriodEditor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        hiPeriodEditor->setReadOnly(true);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(188, 17, 16, 16));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(9, 55, 71, 21));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        loPeriodEditor = new QLineEdit(groupBox);
        loPeriodEditor->setObjectName(QString::fromUtf8("loPeriodEditor"));
        loPeriodEditor->setGeometry(QRect(80, 51, 101, 29));
        sizePolicy.setHeightForWidth(loPeriodEditor->sizePolicy().hasHeightForWidth());
        loPeriodEditor->setSizePolicy(sizePolicy);
        loPeriodEditor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        loPeriodEditor->setReadOnly(true);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(187, 58, 16, 16));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        btnStart = new QPushButton(groupBox);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(230, 30, 75, 25));
        btnStop = new QPushButton(groupBox);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(230, 80, 75, 25));
        btnConfig = new QPushButton(groupBox);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(230, 150, 75, 25));
        cntrValueList = new QListWidget(groupBox);
        cntrValueList->setObjectName(QString::fromUtf8("cntrValueList"));
        cntrValueList->setGeometry(QRect(9, 90, 191, 121));
        sizePolicy.setHeightForWidth(cntrValueList->sizePolicy().hasHeightForWidth());
        cntrValueList->setSizePolicy(sizePolicy);

        retranslateUi(PulseWidthMeasurementClass);

        QMetaObject::connectSlotsByName(PulseWidthMeasurementClass);
    } // setupUi

    void retranslateUi(QDialog *PulseWidthMeasurementClass)
    {
        PulseWidthMeasurementClass->setWindowTitle(QCoreApplication::translate("PulseWidthMeasurementClass", "Pulse Width Measurement", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("PulseWidthMeasurementClass", "High Period:", nullptr));
        label_2->setText(QCoreApplication::translate("PulseWidthMeasurementClass", "S", nullptr));
        label_3->setText(QCoreApplication::translate("PulseWidthMeasurementClass", "Low  Period:", nullptr));
        label_4->setText(QCoreApplication::translate("PulseWidthMeasurementClass", "S", nullptr));
        btnStart->setText(QCoreApplication::translate("PulseWidthMeasurementClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("PulseWidthMeasurementClass", "Stop", nullptr));
        btnConfig->setText(QCoreApplication::translate("PulseWidthMeasurementClass", "Configure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PulseWidthMeasurementClass: public Ui_PulseWidthMeasurementClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PULSEWIDTHMEASUREMENT_H
