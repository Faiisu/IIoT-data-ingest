/********************************************************************************
** Form generated from reading UI file 'asynonebufferedai_tdtr.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASYNONEBUFFEREDAI_TDTR_H
#define UI_ASYNONEBUFFEREDAI_TDTR_H

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

class Ui_AsynOneBufferedAI_TDtrClass
{
public:
    QPushButton *btnGetData;
    QLabel *lblXCoordinateEnd;
    QLabel *lblShift;
    QLabel *lblYCoordinateMid;
    QLineEdit *edtDivValue;
    QListWidget *listWidget;
    QLabel *lblYCoordinateMax;
    QLabel *lblDiv;
    QLabel *lblColor;
    QLabel *lblYCoordinateMin;
    QSlider *sldShift;
    QLineEdit *edtShiftValue;
    QLabel *lblDivUnit;
    QPushButton *btnConfigure;
    QFrame *graphFrame;
    QLabel *lblXCoordinateStart;
    QLabel *lblShiftUnit;
    QSlider *sldDiv;

    void setupUi(QDialog *AsynOneBufferedAI_TDtrClass)
    {
        if (AsynOneBufferedAI_TDtrClass->objectName().isEmpty())
            AsynOneBufferedAI_TDtrClass->setObjectName(QString::fromUtf8("AsynOneBufferedAI_TDtrClass"));
        AsynOneBufferedAI_TDtrClass->resize(762, 515);
        AsynOneBufferedAI_TDtrClass->setMinimumSize(QSize(762, 515));
        AsynOneBufferedAI_TDtrClass->setMaximumSize(QSize(762, 515));
        btnGetData = new QPushButton(AsynOneBufferedAI_TDtrClass);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));
        btnGetData->setEnabled(true);
        btnGetData->setGeometry(QRect(605, 456, 111, 23));
        btnGetData->setAutoDefault(false);
        lblXCoordinateEnd = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblXCoordinateEnd->setObjectName(QString::fromUtf8("lblXCoordinateEnd"));
        lblXCoordinateEnd->setGeometry(QRect(623, 368, 90, 16));
        lblXCoordinateEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblShift = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblShift->setObjectName(QString::fromUtf8("lblShift"));
        lblShift->setGeometry(QRect(62, 453, 51, 16));
        lblShift->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblYCoordinateMid = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblYCoordinateMid->setObjectName(QString::fromUtf8("lblYCoordinateMid"));
        lblYCoordinateMid->setGeometry(QRect(5, 193, 46, 16));
        lblYCoordinateMid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtDivValue = new QLineEdit(AsynOneBufferedAI_TDtrClass);
        edtDivValue->setObjectName(QString::fromUtf8("edtDivValue"));
        edtDivValue->setGeometry(QRect(381, 450, 51, 22));
        edtDivValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtDivValue->setReadOnly(true);
        listWidget = new QListWidget(AsynOneBufferedAI_TDtrClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(115, 400, 475, 38));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        lblYCoordinateMax = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblYCoordinateMax->setObjectName(QString::fromUtf8("lblYCoordinateMax"));
        lblYCoordinateMax->setGeometry(QRect(5, 42, 46, 20));
        lblYCoordinateMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblDiv = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblDiv->setObjectName(QString::fromUtf8("lblDiv"));
        lblDiv->setGeometry(QRect(351, 453, 31, 16));
        lblDiv->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblColor = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        lblColor->setGeometry(QRect(55, 400, 61, 38));
        lblColor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblYCoordinateMin = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblYCoordinateMin->setObjectName(QString::fromUtf8("lblYCoordinateMin"));
        lblYCoordinateMin->setGeometry(QRect(5, 347, 46, 16));
        lblYCoordinateMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sldShift = new QSlider(AsynOneBufferedAI_TDtrClass);
        sldShift->setObjectName(QString::fromUtf8("sldShift"));
        sldShift->setEnabled(true);
        sldShift->setGeometry(QRect(195, 451, 128, 21));
        sldShift->setMinimum(10);
        sldShift->setMaximum(1000);
        sldShift->setSingleStep(10);
        sldShift->setValue(200);
        sldShift->setOrientation(Qt::Horizontal);
        sldShift->setTickPosition(QSlider::NoTicks);
        edtShiftValue = new QLineEdit(AsynOneBufferedAI_TDtrClass);
        edtShiftValue->setObjectName(QString::fromUtf8("edtShiftValue"));
        edtShiftValue->setGeometry(QRect(116, 450, 51, 22));
        edtShiftValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtShiftValue->setReadOnly(true);
        lblDivUnit = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblDivUnit->setObjectName(QString::fromUtf8("lblDivUnit"));
        lblDivUnit->setGeometry(QRect(437, 453, 16, 16));
        lblDivUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        btnConfigure = new QPushButton(AsynOneBufferedAI_TDtrClass);
        btnConfigure->setObjectName(QString::fromUtf8("btnConfigure"));
        btnConfigure->setEnabled(true);
        btnConfigure->setGeometry(QRect(605, 417, 111, 23));
        btnConfigure->setAutoDefault(false);
        graphFrame = new QFrame(AsynOneBufferedAI_TDtrClass);
        graphFrame->setObjectName(QString::fromUtf8("graphFrame"));
        graphFrame->setGeometry(QRect(54, 41, 660, 324));
        graphFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        lblXCoordinateStart = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblXCoordinateStart->setObjectName(QString::fromUtf8("lblXCoordinateStart"));
        lblXCoordinateStart->setGeometry(QRect(55, 369, 71, 16));
        lblXCoordinateStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblShiftUnit = new QLabel(AsynOneBufferedAI_TDtrClass);
        lblShiftUnit->setObjectName(QString::fromUtf8("lblShiftUnit"));
        lblShiftUnit->setGeometry(QRect(172, 454, 16, 16));
        lblShiftUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sldDiv = new QSlider(AsynOneBufferedAI_TDtrClass);
        sldDiv->setObjectName(QString::fromUtf8("sldDiv"));
        sldDiv->setEnabled(true);
        sldDiv->setGeometry(QRect(458, 450, 128, 21));
        sldDiv->setMinimum(10);
        sldDiv->setMaximum(1000);
        sldDiv->setSingleStep(10);
        sldDiv->setValue(200);
        sldDiv->setOrientation(Qt::Horizontal);
        sldDiv->setTickPosition(QSlider::NoTicks);

        retranslateUi(AsynOneBufferedAI_TDtrClass);

        QMetaObject::connectSlotsByName(AsynOneBufferedAI_TDtrClass);
    } // setupUi

    void retranslateUi(QDialog *AsynOneBufferedAI_TDtrClass)
    {
        AsynOneBufferedAI_TDtrClass->setWindowTitle(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "Asynchronous One Buffered AI with Trigger Delay to Start", nullptr));
        btnGetData->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "Get Data", nullptr));
        lblXCoordinateEnd->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "10Sec", nullptr));
        lblShift->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "Shift:", nullptr));
        lblYCoordinateMid->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "0", nullptr));
        edtDivValue->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "200", nullptr));
        lblYCoordinateMax->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "10.0V", nullptr));
        lblDiv->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "Div:", nullptr));
        lblColor->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "Color of\n"
"channels:", nullptr));
        lblYCoordinateMin->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "-10.0V", nullptr));
        edtShiftValue->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "200", nullptr));
        lblDivUnit->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "ms", nullptr));
        btnConfigure->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "Configure", nullptr));
        lblXCoordinateStart->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "0Sec", nullptr));
        lblShiftUnit->setText(QCoreApplication::translate("AsynOneBufferedAI_TDtrClass", "ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AsynOneBufferedAI_TDtrClass: public Ui_AsynOneBufferedAI_TDtrClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASYNONEBUFFEREDAI_TDTR_H
