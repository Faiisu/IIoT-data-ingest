/********************************************************************************
** Form generated from reading UI file 'asynchronousonebufferedai.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASYNCHRONOUSONEBUFFEREDAI_H
#define UI_ASYNCHRONOUSONEBUFFEREDAI_H

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

class Ui_AI_AsynchronousOneBufferedAiClass
{
public:
    QLabel *lblShift;
    QLabel *lblYCoordinateMin;
    QLabel *lblColor;
    QLabel *lblXCoordinateEnd;
    QSlider *sldShift;
    QPushButton *btnConfigure;
    QLabel *lblYCoordinateMid;
    QLabel *lblXCoordinateStart;
    QFrame *graphFrame;
    QPushButton *btnGetData;
    QLabel *lblShiftUnit;
    QLineEdit *edtShiftValue;
    QLabel *lblDivUnit;
    QListWidget *listWidget;
    QLabel *lblYCoordinateMax;
    QSlider *sldDiv;
    QLabel *lblDiv;
    QLineEdit *edtDivValue;

    void setupUi(QDialog *AI_AsynchronousOneBufferedAiClass)
    {
        if (AI_AsynchronousOneBufferedAiClass->objectName().isEmpty())
            AI_AsynchronousOneBufferedAiClass->setObjectName(QString::fromUtf8("AI_AsynchronousOneBufferedAiClass"));
        AI_AsynchronousOneBufferedAiClass->resize(762, 515);
        AI_AsynchronousOneBufferedAiClass->setMinimumSize(QSize(762, 515));
        AI_AsynchronousOneBufferedAiClass->setMaximumSize(QSize(762, 515));
        lblShift = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblShift->setObjectName(QString::fromUtf8("lblShift"));
        lblShift->setGeometry(QRect(57, 451, 51, 20));
        lblShift->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblYCoordinateMin = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblYCoordinateMin->setObjectName(QString::fromUtf8("lblYCoordinateMin"));
        lblYCoordinateMin->setGeometry(QRect(0, 345, 46, 16));
        lblYCoordinateMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblColor = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        lblColor->setGeometry(QRect(50, 398, 61, 38));
        lblColor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblXCoordinateEnd = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblXCoordinateEnd->setObjectName(QString::fromUtf8("lblXCoordinateEnd"));
        lblXCoordinateEnd->setGeometry(QRect(618, 366, 90, 16));
        lblXCoordinateEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sldShift = new QSlider(AI_AsynchronousOneBufferedAiClass);
        sldShift->setObjectName(QString::fromUtf8("sldShift"));
        sldShift->setEnabled(false);
        sldShift->setGeometry(QRect(190, 449, 128, 21));
        sldShift->setMinimum(10);
        sldShift->setMaximum(1000);
        sldShift->setSingleStep(10);
        sldShift->setValue(200);
        sldShift->setOrientation(Qt::Horizontal);
        sldShift->setTickPosition(QSlider::NoTicks);
        btnConfigure = new QPushButton(AI_AsynchronousOneBufferedAiClass);
        btnConfigure->setObjectName(QString::fromUtf8("btnConfigure"));
        btnConfigure->setEnabled(true);
        btnConfigure->setGeometry(QRect(600, 415, 111, 23));
        btnConfigure->setAutoDefault(false);
        lblYCoordinateMid = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblYCoordinateMid->setObjectName(QString::fromUtf8("lblYCoordinateMid"));
        lblYCoordinateMid->setGeometry(QRect(0, 191, 46, 16));
        lblYCoordinateMid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblXCoordinateStart = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblXCoordinateStart->setObjectName(QString::fromUtf8("lblXCoordinateStart"));
        lblXCoordinateStart->setGeometry(QRect(50, 367, 71, 16));
        lblXCoordinateStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        graphFrame = new QFrame(AI_AsynchronousOneBufferedAiClass);
        graphFrame->setObjectName(QString::fromUtf8("graphFrame"));
        graphFrame->setGeometry(QRect(49, 39, 660, 324));
        graphFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        btnGetData = new QPushButton(AI_AsynchronousOneBufferedAiClass);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));
        btnGetData->setEnabled(false);
        btnGetData->setGeometry(QRect(600, 454, 111, 23));
        btnGetData->setAutoDefault(false);
        lblShiftUnit = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblShiftUnit->setObjectName(QString::fromUtf8("lblShiftUnit"));
        lblShiftUnit->setGeometry(QRect(167, 452, 16, 16));
        lblShiftUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        edtShiftValue = new QLineEdit(AI_AsynchronousOneBufferedAiClass);
        edtShiftValue->setObjectName(QString::fromUtf8("edtShiftValue"));
        edtShiftValue->setGeometry(QRect(111, 448, 51, 22));
        edtShiftValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtShiftValue->setReadOnly(true);
        lblDivUnit = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblDivUnit->setObjectName(QString::fromUtf8("lblDivUnit"));
        lblDivUnit->setGeometry(QRect(432, 451, 16, 16));
        lblDivUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidget = new QListWidget(AI_AsynchronousOneBufferedAiClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(110, 398, 475, 38));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        lblYCoordinateMax = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblYCoordinateMax->setObjectName(QString::fromUtf8("lblYCoordinateMax"));
        lblYCoordinateMax->setGeometry(QRect(0, 40, 46, 20));
        lblYCoordinateMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sldDiv = new QSlider(AI_AsynchronousOneBufferedAiClass);
        sldDiv->setObjectName(QString::fromUtf8("sldDiv"));
        sldDiv->setEnabled(false);
        sldDiv->setGeometry(QRect(453, 448, 128, 21));
        sldDiv->setMinimum(10);
        sldDiv->setMaximum(1000);
        sldDiv->setSingleStep(10);
        sldDiv->setValue(200);
        sldDiv->setOrientation(Qt::Horizontal);
        sldDiv->setTickPosition(QSlider::NoTicks);
        lblDiv = new QLabel(AI_AsynchronousOneBufferedAiClass);
        lblDiv->setObjectName(QString::fromUtf8("lblDiv"));
        lblDiv->setGeometry(QRect(346, 451, 31, 16));
        lblDiv->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        edtDivValue = new QLineEdit(AI_AsynchronousOneBufferedAiClass);
        edtDivValue->setObjectName(QString::fromUtf8("edtDivValue"));
        edtDivValue->setGeometry(QRect(376, 448, 51, 22));
        edtDivValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtDivValue->setReadOnly(true);
        QWidget::setTabOrder(btnConfigure, btnGetData);
        QWidget::setTabOrder(btnGetData, sldShift);
        QWidget::setTabOrder(sldShift, sldDiv);
        QWidget::setTabOrder(sldDiv, listWidget);
        QWidget::setTabOrder(listWidget, edtShiftValue);
        QWidget::setTabOrder(edtShiftValue, edtDivValue);

        retranslateUi(AI_AsynchronousOneBufferedAiClass);

        QMetaObject::connectSlotsByName(AI_AsynchronousOneBufferedAiClass);
    } // setupUi

    void retranslateUi(QDialog *AI_AsynchronousOneBufferedAiClass)
    {
        AI_AsynchronousOneBufferedAiClass->setWindowTitle(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "AI_AsynchronousOneBufferedAi", nullptr));
        lblShift->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "Shift:", nullptr));
        lblYCoordinateMin->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "-10.0V", nullptr));
        lblColor->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "Color of\n"
"channels:", nullptr));
        lblXCoordinateEnd->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "10Sec", nullptr));
        btnConfigure->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "Configure", nullptr));
        lblYCoordinateMid->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "0", nullptr));
        lblXCoordinateStart->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "0Sec", nullptr));
        btnGetData->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "Get Data", nullptr));
        lblShiftUnit->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "ms", nullptr));
        edtShiftValue->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "200", nullptr));
        lblDivUnit->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "ms", nullptr));
        lblYCoordinateMax->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "10.0V", nullptr));
        lblDiv->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "Div:", nullptr));
        edtDivValue->setText(QCoreApplication::translate("AI_AsynchronousOneBufferedAiClass", "200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AI_AsynchronousOneBufferedAiClass: public Ui_AI_AsynchronousOneBufferedAiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASYNCHRONOUSONEBUFFEREDAI_H
