/********************************************************************************
** Form generated from reading UI file 'asynonebufferedai_tdtp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASYNONEBUFFEREDAI_TDTP_H
#define UI_ASYNONEBUFFEREDAI_TDTP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_AsynOneBufferedAI_TDtpClass
{
public:
    QListWidget *listWidget;
    QLabel *lblYCoordinateMin;
    QPushButton *btnConfigure;
    QLabel *lblDiv;
    QPushButton *btnGetData;
    QSlider *sldDiv;
    QLabel *lblShiftUnit;
    QLabel *lblXCoordinateStart;
    QFrame *graphFrame;
    QLabel *lblYCoordinateMax;
    QLabel *lblXCoordinateEnd;
    QLabel *lblYCoordinateMid;
    QLabel *lblShift;
    QLabel *lblColor;
    QLineEdit *edtDivValue;
    QLineEdit *edtShiftValue;
    QSlider *sldShift;
    QLabel *lblDivUnit;
    QFrame *triggerPointFlag;
    QLabel *label_triggerPoint;

    void setupUi(QDialog *AsynOneBufferedAI_TDtpClass)
    {
        if (AsynOneBufferedAI_TDtpClass->objectName().isEmpty())
            AsynOneBufferedAI_TDtpClass->setObjectName(QString::fromUtf8("AsynOneBufferedAI_TDtpClass"));
        AsynOneBufferedAI_TDtpClass->resize(762, 518);
        AsynOneBufferedAI_TDtpClass->setMinimumSize(QSize(762, 518));
        AsynOneBufferedAI_TDtpClass->setMaximumSize(QSize(762, 518));
        listWidget = new QListWidget(AsynOneBufferedAI_TDtpClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(113, 423, 475, 38));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        lblYCoordinateMin = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblYCoordinateMin->setObjectName(QString::fromUtf8("lblYCoordinateMin"));
        lblYCoordinateMin->setGeometry(QRect(3, 347, 46, 16));
        lblYCoordinateMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnConfigure = new QPushButton(AsynOneBufferedAI_TDtpClass);
        btnConfigure->setObjectName(QString::fromUtf8("btnConfigure"));
        btnConfigure->setEnabled(true);
        btnConfigure->setGeometry(QRect(603, 440, 111, 23));
        btnConfigure->setAutoDefault(false);
        lblDiv = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblDiv->setObjectName(QString::fromUtf8("lblDiv"));
        lblDiv->setGeometry(QRect(349, 476, 31, 16));
        lblDiv->setMinimumSize(QSize(31, 16));
        lblDiv->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        btnGetData = new QPushButton(AsynOneBufferedAI_TDtpClass);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));
        btnGetData->setEnabled(true);
        btnGetData->setGeometry(QRect(603, 479, 111, 23));
        btnGetData->setAutoDefault(false);
        sldDiv = new QSlider(AsynOneBufferedAI_TDtpClass);
        sldDiv->setObjectName(QString::fromUtf8("sldDiv"));
        sldDiv->setEnabled(true);
        sldDiv->setGeometry(QRect(456, 473, 128, 21));
        sldDiv->setMinimum(10);
        sldDiv->setMaximum(1000);
        sldDiv->setSingleStep(10);
        sldDiv->setValue(200);
        sldDiv->setOrientation(Qt::Horizontal);
        sldDiv->setTickPosition(QSlider::NoTicks);
        lblShiftUnit = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblShiftUnit->setObjectName(QString::fromUtf8("lblShiftUnit"));
        lblShiftUnit->setGeometry(QRect(170, 477, 16, 16));
        lblShiftUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblXCoordinateStart = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblXCoordinateStart->setObjectName(QString::fromUtf8("lblXCoordinateStart"));
        lblXCoordinateStart->setGeometry(QRect(51, 392, 71, 16));
        lblXCoordinateStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        graphFrame = new QFrame(AsynOneBufferedAI_TDtpClass);
        graphFrame->setObjectName(QString::fromUtf8("graphFrame"));
        graphFrame->setGeometry(QRect(52, 41, 660, 324));
        graphFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        lblYCoordinateMax = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblYCoordinateMax->setObjectName(QString::fromUtf8("lblYCoordinateMax"));
        lblYCoordinateMax->setGeometry(QRect(3, 42, 46, 20));
        lblYCoordinateMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblXCoordinateEnd = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblXCoordinateEnd->setObjectName(QString::fromUtf8("lblXCoordinateEnd"));
        lblXCoordinateEnd->setGeometry(QRect(621, 392, 90, 16));
        lblXCoordinateEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblYCoordinateMid = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblYCoordinateMid->setObjectName(QString::fromUtf8("lblYCoordinateMid"));
        lblYCoordinateMid->setGeometry(QRect(3, 193, 46, 16));
        lblYCoordinateMid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblShift = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblShift->setObjectName(QString::fromUtf8("lblShift"));
        lblShift->setGeometry(QRect(60, 476, 51, 16));
        lblShift->setMinimumSize(QSize(41, 16));
        lblShift->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblColor = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        lblColor->setGeometry(QRect(53, 423, 61, 38));
        lblColor->setMinimumSize(QSize(61, 38));
        lblColor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        edtDivValue = new QLineEdit(AsynOneBufferedAI_TDtpClass);
        edtDivValue->setObjectName(QString::fromUtf8("edtDivValue"));
        edtDivValue->setGeometry(QRect(379, 473, 51, 22));
        edtDivValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtDivValue->setReadOnly(true);
        edtShiftValue = new QLineEdit(AsynOneBufferedAI_TDtpClass);
        edtShiftValue->setObjectName(QString::fromUtf8("edtShiftValue"));
        edtShiftValue->setGeometry(QRect(114, 473, 51, 22));
        edtShiftValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtShiftValue->setReadOnly(true);
        sldShift = new QSlider(AsynOneBufferedAI_TDtpClass);
        sldShift->setObjectName(QString::fromUtf8("sldShift"));
        sldShift->setEnabled(true);
        sldShift->setGeometry(QRect(193, 474, 128, 21));
        sldShift->setMinimum(10);
        sldShift->setMaximum(1000);
        sldShift->setSingleStep(10);
        sldShift->setValue(200);
        sldShift->setOrientation(Qt::Horizontal);
        sldShift->setTickPosition(QSlider::NoTicks);
        lblDivUnit = new QLabel(AsynOneBufferedAI_TDtpClass);
        lblDivUnit->setObjectName(QString::fromUtf8("lblDivUnit"));
        lblDivUnit->setGeometry(QRect(435, 476, 16, 16));
        lblDivUnit->setMinimumSize(QSize(16, 16));
        lblDivUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        triggerPointFlag = new QFrame(AsynOneBufferedAI_TDtpClass);
        triggerPointFlag->setObjectName(QString::fromUtf8("triggerPointFlag"));
        triggerPointFlag->setGeometry(QRect(46, 367, 16, 21));
        triggerPointFlag->setMinimumSize(QSize(16, 21));
        triggerPointFlag->setMaximumSize(QSize(16, 21));
        triggerPointFlag->setStyleSheet(QString::fromUtf8("background:url(:/AsynOneBufferedAI_TDtp/Resources/trigger.png)"));
        triggerPointFlag->setFrameShape(QFrame::StyledPanel);
        triggerPointFlag->setFrameShadow(QFrame::Raised);
        label_triggerPoint = new QLabel(AsynOneBufferedAI_TDtpClass);
        label_triggerPoint->setObjectName(QString::fromUtf8("label_triggerPoint"));
        label_triggerPoint->setGeometry(QRect(64, 373, 121, 16));
        label_triggerPoint->setMinimumSize(QSize(121, 16));
        label_triggerPoint->setMaximumSize(QSize(121, 16));

        retranslateUi(AsynOneBufferedAI_TDtpClass);

        QMetaObject::connectSlotsByName(AsynOneBufferedAI_TDtpClass);
    } // setupUi

    void retranslateUi(QDialog *AsynOneBufferedAI_TDtpClass)
    {
        AsynOneBufferedAI_TDtpClass->setWindowTitle(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "Asynchronous One Buffered AI with Trigger Delay to Stop", nullptr));
        lblYCoordinateMin->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "-10.0V", nullptr));
        btnConfigure->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "Configure", nullptr));
        lblDiv->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "Div:", nullptr));
        btnGetData->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "Get Data", nullptr));
        lblShiftUnit->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "ms", nullptr));
        lblXCoordinateStart->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "0Sec", nullptr));
        lblYCoordinateMax->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "10.0V", nullptr));
        lblXCoordinateEnd->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "10Sec", nullptr));
        lblYCoordinateMid->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "0", nullptr));
        lblShift->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "Shift:", nullptr));
        lblColor->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "Color of\n"
"channels:", nullptr));
        edtDivValue->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "200", nullptr));
        edtShiftValue->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "200", nullptr));
        lblDivUnit->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "ms", nullptr));
        label_triggerPoint->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtpClass", "0 ms Triggered.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AsynOneBufferedAI_TDtpClass: public Ui_AsynOneBufferedAI_TDtpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASYNONEBUFFEREDAI_TDTP_H
