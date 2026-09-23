/********************************************************************************
** Form generated from reading UI file 'frequencymeasurement.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREQUENCYMEASUREMENT_H
#define UI_FREQUENCYMEASUREMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_FrequencyMeasurementClass
{
public:
    QFrame *bkgrndImage;
    QFrame *DataView;
    QLabel *yTLabel;
    QLabel *yMLabel;
    QLabel *yBLabel;
    QLabel *xLLabel;
    QLabel *xRLabel;
    QPushButton *btnStart;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnConfig;
    QPushButton *Enlarge;
    QPushButton *Shorten;
    QLabel *label;
    QSlider *timerTrackBar;
    QLabel *timerValueLabel;
    QLineEdit *lineEditFreqValue;

    void setupUi(QDialog *FrequencyMeasurementClass)
    {
        if (FrequencyMeasurementClass->objectName().isEmpty())
            FrequencyMeasurementClass->setObjectName(QString::fromUtf8("FrequencyMeasurementClass"));
        FrequencyMeasurementClass->resize(680, 514);
        FrequencyMeasurementClass->setMinimumSize(QSize(680, 514));
        FrequencyMeasurementClass->setMaximumSize(QSize(680, 514));
        FrequencyMeasurementClass->setSizeGripEnabled(false);
        FrequencyMeasurementClass->setModal(false);
        bkgrndImage = new QFrame(FrequencyMeasurementClass);
        bkgrndImage->setObjectName(QString::fromUtf8("bkgrndImage"));
        bkgrndImage->setGeometry(QRect(525, -2, 161, 51));
        bkgrndImage->setFrameShape(QFrame::StyledPanel);
        bkgrndImage->setFrameShadow(QFrame::Raised);
        DataView = new QFrame(FrequencyMeasurementClass);
        DataView->setObjectName(QString::fromUtf8("DataView"));
        DataView->setGeometry(QRect(83, 30, 511, 401));
        DataView->setAutoFillBackground(false);
        DataView->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        DataView->setFrameShape(QFrame::StyledPanel);
        DataView->setFrameShadow(QFrame::Raised);
        yTLabel = new QLabel(FrequencyMeasurementClass);
        yTLabel->setObjectName(QString::fromUtf8("yTLabel"));
        yTLabel->setGeometry(QRect(19, 30, 61, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(yTLabel->sizePolicy().hasHeightForWidth());
        yTLabel->setSizePolicy(sizePolicy);
        yTLabel->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        yMLabel = new QLabel(FrequencyMeasurementClass);
        yMLabel->setObjectName(QString::fromUtf8("yMLabel"));
        yMLabel->setGeometry(QRect(20, 216, 61, 20));
        sizePolicy.setHeightForWidth(yMLabel->sizePolicy().hasHeightForWidth());
        yMLabel->setSizePolicy(sizePolicy);
        yMLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        yBLabel = new QLabel(FrequencyMeasurementClass);
        yBLabel->setObjectName(QString::fromUtf8("yBLabel"));
        yBLabel->setGeometry(QRect(20, 411, 61, 20));
        sizePolicy.setHeightForWidth(yBLabel->sizePolicy().hasHeightForWidth());
        yBLabel->setSizePolicy(sizePolicy);
        yBLabel->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);
        xLLabel = new QLabel(FrequencyMeasurementClass);
        xLLabel->setObjectName(QString::fromUtf8("xLLabel"));
        xLLabel->setGeometry(QRect(83, 434, 81, 20));
        sizePolicy.setHeightForWidth(xLLabel->sizePolicy().hasHeightForWidth());
        xLLabel->setSizePolicy(sizePolicy);
        xLLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        xRLabel = new QLabel(FrequencyMeasurementClass);
        xRLabel->setObjectName(QString::fromUtf8("xRLabel"));
        xRLabel->setGeometry(QRect(513, 432, 81, 20));
        sizePolicy.setHeightForWidth(xRLabel->sizePolicy().hasHeightForWidth());
        xRLabel->setSizePolicy(sizePolicy);
        xRLabel->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        btnStart = new QPushButton(FrequencyMeasurementClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(610, 90, 61, 23));
        sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy);
        btnPause = new QPushButton(FrequencyMeasurementClass);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setGeometry(QRect(610, 170, 61, 23));
        sizePolicy.setHeightForWidth(btnPause->sizePolicy().hasHeightForWidth());
        btnPause->setSizePolicy(sizePolicy);
        btnStop = new QPushButton(FrequencyMeasurementClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(610, 220, 61, 23));
        sizePolicy.setHeightForWidth(btnStop->sizePolicy().hasHeightForWidth());
        btnStop->setSizePolicy(sizePolicy);
        btnConfig = new QPushButton(FrequencyMeasurementClass);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(604, 290, 71, 23));
        sizePolicy.setHeightForWidth(btnConfig->sizePolicy().hasHeightForWidth());
        btnConfig->setSizePolicy(sizePolicy);
        Enlarge = new QPushButton(FrequencyMeasurementClass);
        Enlarge->setObjectName(QString::fromUtf8("Enlarge"));
        Enlarge->setGeometry(QRect(35, 280, 31, 30));
        sizePolicy.setHeightForWidth(Enlarge->sizePolicy().hasHeightForWidth());
        Enlarge->setSizePolicy(sizePolicy);
        Enlarge->setStyleSheet(QString::fromUtf8("background:url(:/FrequencyMeasurement/Resources/Enlarge.png)"));
        Shorten = new QPushButton(FrequencyMeasurementClass);
        Shorten->setObjectName(QString::fromUtf8("Shorten"));
        Shorten->setGeometry(QRect(35, 330, 31, 30));
        sizePolicy.setHeightForWidth(Shorten->sizePolicy().hasHeightForWidth());
        Shorten->setSizePolicy(sizePolicy);
        Shorten->setStyleSheet(QString::fromUtf8("background:url(:/FrequencyMeasurement/Resources/Shorten.png)"));
        label = new QLabel(FrequencyMeasurementClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(145, 467, 101, 16));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        timerTrackBar = new QSlider(FrequencyMeasurementClass);
        timerTrackBar->setObjectName(QString::fromUtf8("timerTrackBar"));
        timerTrackBar->setGeometry(QRect(252, 465, 181, 21));
        sizePolicy.setHeightForWidth(timerTrackBar->sizePolicy().hasHeightForWidth());
        timerTrackBar->setSizePolicy(sizePolicy);
        timerTrackBar->setMinimum(10);
        timerTrackBar->setMaximum(1000);
        timerTrackBar->setValue(50);
        timerTrackBar->setOrientation(Qt::Horizontal);
        timerTrackBar->setInvertedAppearance(false);
        timerTrackBar->setInvertedControls(false);
        timerTrackBar->setTickPosition(QSlider::NoTicks);
        timerValueLabel = new QLabel(FrequencyMeasurementClass);
        timerValueLabel->setObjectName(QString::fromUtf8("timerValueLabel"));
        timerValueLabel->setGeometry(QRect(439, 467, 71, 16));
        sizePolicy.setHeightForWidth(timerValueLabel->sizePolicy().hasHeightForWidth());
        timerValueLabel->setSizePolicy(sizePolicy);
        timerValueLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lineEditFreqValue = new QLineEdit(FrequencyMeasurementClass);
        lineEditFreqValue->setObjectName(QString::fromUtf8("lineEditFreqValue"));
        lineEditFreqValue->setGeometry(QRect(610, 340, 61, 20));
        lineEditFreqValue->setReadOnly(true);

        retranslateUi(FrequencyMeasurementClass);

        QMetaObject::connectSlotsByName(FrequencyMeasurementClass);
    } // setupUi

    void retranslateUi(QDialog *FrequencyMeasurementClass)
    {
        FrequencyMeasurementClass->setWindowTitle(QCoreApplication::translate("FrequencyMeasurementClass", "Frequency Measurement", nullptr));
        yTLabel->setText(QCoreApplication::translate("FrequencyMeasurementClass", "100KHz", nullptr));
        yMLabel->setText(QCoreApplication::translate("FrequencyMeasurementClass", "50KHz", nullptr));
        yBLabel->setText(QCoreApplication::translate("FrequencyMeasurementClass", "0Hz", nullptr));
        xLLabel->setText(QCoreApplication::translate("FrequencyMeasurementClass", "0 Sec", nullptr));
        xRLabel->setText(QCoreApplication::translate("FrequencyMeasurementClass", "10 Sec", nullptr));
        btnStart->setText(QCoreApplication::translate("FrequencyMeasurementClass", "Start", nullptr));
        btnPause->setText(QCoreApplication::translate("FrequencyMeasurementClass", "Pause", nullptr));
        btnStop->setText(QCoreApplication::translate("FrequencyMeasurementClass", "Stop", nullptr));
        btnConfig->setText(QCoreApplication::translate("FrequencyMeasurementClass", "Configure", nullptr));
        Enlarge->setText(QString());
        Shorten->setText(QString());
        label->setText(QCoreApplication::translate("FrequencyMeasurementClass", "Sample Interval:", nullptr));
        timerValueLabel->setText(QCoreApplication::translate("FrequencyMeasurementClass", "50 ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrequencyMeasurementClass: public Ui_FrequencyMeasurementClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREQUENCYMEASUREMENT_H
