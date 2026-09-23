/********************************************************************************
** Form generated from reading UI file 'synchronousonebufferedai.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCHRONOUSONEBUFFEREDAI_H
#define UI_SYNCHRONOUSONEBUFFEREDAI_H

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

class Ui_AI_SynchronousOneBufferedAiClass
{
public:
    QSlider *sldShift;
    QLabel *lblYCoordinateMin;
    QFrame *graphFrame;
    QLabel *lblXCoordinateStart;
    QLabel *lblShiftUnit;
    QLineEdit *edtShiftValue;
    QLabel *lblYCoordinateMid;
    QListWidget *listWidget;
    QPushButton *btnGetData;
    QLabel *lblColor;
    QLabel *lblYCoordinateMax;
    QLabel *lblShift;
    QLabel *lblXCoordinateEnd;
    QPushButton *btnConfigure;
    QSlider *sldDiv;
    QLabel *lblDivUnit;
    QLineEdit *edtDivValue;
    QLabel *lblDiv;

    void setupUi(QDialog *AI_SynchronousOneBufferedAiClass)
    {
        if (AI_SynchronousOneBufferedAiClass->objectName().isEmpty())
            AI_SynchronousOneBufferedAiClass->setObjectName(QString::fromUtf8("AI_SynchronousOneBufferedAiClass"));
        AI_SynchronousOneBufferedAiClass->resize(762, 515);
        AI_SynchronousOneBufferedAiClass->setMinimumSize(QSize(762, 515));
        AI_SynchronousOneBufferedAiClass->setMaximumSize(QSize(762, 515));
        sldShift = new QSlider(AI_SynchronousOneBufferedAiClass);
        sldShift->setObjectName(QString::fromUtf8("sldShift"));
        sldShift->setEnabled(false);
        sldShift->setGeometry(QRect(190, 458, 128, 21));
        sldShift->setMinimum(10);
        sldShift->setMaximum(1000);
        sldShift->setSingleStep(10);
        sldShift->setValue(200);
        sldShift->setOrientation(Qt::Horizontal);
        sldShift->setTickPosition(QSlider::NoTicks);
        lblYCoordinateMin = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblYCoordinateMin->setObjectName(QString::fromUtf8("lblYCoordinateMin"));
        lblYCoordinateMin->setGeometry(QRect(0, 345, 46, 16));
        lblYCoordinateMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        graphFrame = new QFrame(AI_SynchronousOneBufferedAiClass);
        graphFrame->setObjectName(QString::fromUtf8("graphFrame"));
        graphFrame->setGeometry(QRect(49, 39, 660, 324));
        graphFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        lblXCoordinateStart = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblXCoordinateStart->setObjectName(QString::fromUtf8("lblXCoordinateStart"));
        lblXCoordinateStart->setGeometry(QRect(50, 367, 71, 16));
        lblXCoordinateStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblShiftUnit = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblShiftUnit->setObjectName(QString::fromUtf8("lblShiftUnit"));
        lblShiftUnit->setGeometry(QRect(167, 460, 16, 16));
        lblShiftUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        edtShiftValue = new QLineEdit(AI_SynchronousOneBufferedAiClass);
        edtShiftValue->setObjectName(QString::fromUtf8("edtShiftValue"));
        edtShiftValue->setGeometry(QRect(111, 457, 51, 22));
        edtShiftValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtShiftValue->setReadOnly(true);
        lblYCoordinateMid = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblYCoordinateMid->setObjectName(QString::fromUtf8("lblYCoordinateMid"));
        lblYCoordinateMid->setGeometry(QRect(0, 191, 46, 16));
        lblYCoordinateMid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        listWidget = new QListWidget(AI_SynchronousOneBufferedAiClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(110, 406, 475, 38));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        btnGetData = new QPushButton(AI_SynchronousOneBufferedAiClass);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));
        btnGetData->setEnabled(false);
        btnGetData->setGeometry(QRect(600, 460, 111, 23));
        btnGetData->setAutoDefault(false);
        lblColor = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        lblColor->setGeometry(QRect(50, 406, 61, 38));
        lblColor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblYCoordinateMax = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblYCoordinateMax->setObjectName(QString::fromUtf8("lblYCoordinateMax"));
        lblYCoordinateMax->setGeometry(QRect(0, 40, 46, 20));
        lblYCoordinateMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblShift = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblShift->setObjectName(QString::fromUtf8("lblShift"));
        lblShift->setGeometry(QRect(56, 459, 51, 16));
        lblShift->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblXCoordinateEnd = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblXCoordinateEnd->setObjectName(QString::fromUtf8("lblXCoordinateEnd"));
        lblXCoordinateEnd->setGeometry(QRect(618, 366, 90, 16));
        lblXCoordinateEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnConfigure = new QPushButton(AI_SynchronousOneBufferedAiClass);
        btnConfigure->setObjectName(QString::fromUtf8("btnConfigure"));
        btnConfigure->setEnabled(true);
        btnConfigure->setGeometry(QRect(600, 421, 111, 23));
        btnConfigure->setAutoDefault(false);
        sldDiv = new QSlider(AI_SynchronousOneBufferedAiClass);
        sldDiv->setObjectName(QString::fromUtf8("sldDiv"));
        sldDiv->setEnabled(false);
        sldDiv->setGeometry(QRect(450, 458, 128, 21));
        sldDiv->setMinimum(10);
        sldDiv->setMaximum(1000);
        sldDiv->setSingleStep(10);
        sldDiv->setValue(200);
        sldDiv->setOrientation(Qt::Horizontal);
        sldDiv->setTickPosition(QSlider::NoTicks);
        lblDivUnit = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblDivUnit->setObjectName(QString::fromUtf8("lblDivUnit"));
        lblDivUnit->setGeometry(QRect(424, 458, 16, 16));
        lblDivUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        edtDivValue = new QLineEdit(AI_SynchronousOneBufferedAiClass);
        edtDivValue->setObjectName(QString::fromUtf8("edtDivValue"));
        edtDivValue->setGeometry(QRect(368, 454, 51, 22));
        edtDivValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edtDivValue->setReadOnly(true);
        lblDiv = new QLabel(AI_SynchronousOneBufferedAiClass);
        lblDiv->setObjectName(QString::fromUtf8("lblDiv"));
        lblDiv->setGeometry(QRect(334, 457, 31, 16));
        lblDiv->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QWidget::setTabOrder(btnConfigure, btnGetData);
        QWidget::setTabOrder(btnGetData, sldShift);
        QWidget::setTabOrder(sldShift, sldDiv);
        QWidget::setTabOrder(sldDiv, listWidget);
        QWidget::setTabOrder(listWidget, edtShiftValue);
        QWidget::setTabOrder(edtShiftValue, edtDivValue);

        retranslateUi(AI_SynchronousOneBufferedAiClass);

        QMetaObject::connectSlotsByName(AI_SynchronousOneBufferedAiClass);
    } // setupUi

    void retranslateUi(QDialog *AI_SynchronousOneBufferedAiClass)
    {
        AI_SynchronousOneBufferedAiClass->setWindowTitle(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "AI_SynchronousOneBufferedAi", nullptr));
        lblYCoordinateMin->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "-10.0V", nullptr));
        lblXCoordinateStart->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "0Sec", nullptr));
        lblShiftUnit->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "ms", nullptr));
        edtShiftValue->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "200", nullptr));
        lblYCoordinateMid->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "0", nullptr));
        btnGetData->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "Get Data", nullptr));
        lblColor->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "Color of\n"
"channels:", nullptr));
        lblYCoordinateMax->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "10.0V", nullptr));
        lblShift->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "Shift:", nullptr));
        lblXCoordinateEnd->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "10Sec", nullptr));
        btnConfigure->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "Configure", nullptr));
        lblDivUnit->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "ms", nullptr));
        edtDivValue->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "200", nullptr));
        lblDiv->setText(QCoreApplication::translate("AI_SynchronousOneBufferedAiClass", "Div:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AI_SynchronousOneBufferedAiClass: public Ui_AI_SynchronousOneBufferedAiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCHRONOUSONEBUFFEREDAI_H
