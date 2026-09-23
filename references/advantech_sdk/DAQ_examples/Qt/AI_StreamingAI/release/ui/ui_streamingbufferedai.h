/********************************************************************************
** Form generated from reading UI file 'streamingbufferedai.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMINGBUFFEREDAI_H
#define UI_STREAMINGBUFFEREDAI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_AI_StreamingBufferedAiClass
{
public:
    QLabel *lblDiv;
    QLabel *lblXCoordinateEnd;
    QLabel *lblXCoordinateStart;
    QPushButton *btnConfigure;
    QLabel *lblColor;
    QListWidget *listWidget;
    QLabel *lblYCoordinateMin;
    QFrame *graphFrame;
    QPushButton *btnStart;
    QLabel *lblYCoordinateMid;
    QSlider *sldDiv;
    QLabel *lblYCoordinateMax;
    QPushButton *btnPause;
    QPushButton *btnStop;

    void setupUi(QDialog *AI_StreamingBufferedAiClass)
    {
        if (AI_StreamingBufferedAiClass->objectName().isEmpty())
            AI_StreamingBufferedAiClass->setObjectName(QString::fromUtf8("AI_StreamingBufferedAiClass"));
        AI_StreamingBufferedAiClass->resize(762, 515);
        AI_StreamingBufferedAiClass->setMinimumSize(QSize(762, 515));
        AI_StreamingBufferedAiClass->setMaximumSize(QSize(762, 515));
        lblDiv = new QLabel(AI_StreamingBufferedAiClass);
        lblDiv->setObjectName(QString::fromUtf8("lblDiv"));
        lblDiv->setGeometry(QRect(550, 417, 31, 16));
        lblDiv->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblXCoordinateEnd = new QLabel(AI_StreamingBufferedAiClass);
        lblXCoordinateEnd->setObjectName(QString::fromUtf8("lblXCoordinateEnd"));
        lblXCoordinateEnd->setGeometry(QRect(618, 381, 90, 16));
        lblXCoordinateEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblXCoordinateStart = new QLabel(AI_StreamingBufferedAiClass);
        lblXCoordinateStart->setObjectName(QString::fromUtf8("lblXCoordinateStart"));
        lblXCoordinateStart->setGeometry(QRect(50, 382, 71, 16));
        lblXCoordinateStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        btnConfigure = new QPushButton(AI_StreamingBufferedAiClass);
        btnConfigure->setObjectName(QString::fromUtf8("btnConfigure"));
        btnConfigure->setEnabled(true);
        btnConfigure->setGeometry(QRect(270, 473, 111, 23));
        btnConfigure->setAutoDefault(false);
        lblColor = new QLabel(AI_StreamingBufferedAiClass);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        lblColor->setGeometry(QRect(42, 404, 61, 41));
        lblColor->setMinimumSize(QSize(41, 41));
        listWidget = new QListWidget(AI_StreamingBufferedAiClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(100, 400, 440, 45));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        lblYCoordinateMin = new QLabel(AI_StreamingBufferedAiClass);
        lblYCoordinateMin->setObjectName(QString::fromUtf8("lblYCoordinateMin"));
        lblYCoordinateMin->setGeometry(QRect(0, 360, 46, 16));
        lblYCoordinateMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        graphFrame = new QFrame(AI_StreamingBufferedAiClass);
        graphFrame->setObjectName(QString::fromUtf8("graphFrame"));
        graphFrame->setGeometry(QRect(49, 39, 660, 340));
        graphFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        btnStart = new QPushButton(AI_StreamingBufferedAiClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setEnabled(true);
        btnStart->setGeometry(QRect(430, 473, 81, 23));
        btnStart->setAutoDefault(true);
        lblYCoordinateMid = new QLabel(AI_StreamingBufferedAiClass);
        lblYCoordinateMid->setObjectName(QString::fromUtf8("lblYCoordinateMid"));
        lblYCoordinateMid->setGeometry(QRect(0, 200, 46, 16));
        lblYCoordinateMid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sldDiv = new QSlider(AI_StreamingBufferedAiClass);
        sldDiv->setObjectName(QString::fromUtf8("sldDiv"));
        sldDiv->setEnabled(false);
        sldDiv->setGeometry(QRect(586, 414, 121, 21));
        sldDiv->setMinimum(10);
        sldDiv->setMaximum(1000);
        sldDiv->setSingleStep(10);
        sldDiv->setValue(200);
        sldDiv->setOrientation(Qt::Horizontal);
        sldDiv->setTickPosition(QSlider::NoTicks);
        lblYCoordinateMax = new QLabel(AI_StreamingBufferedAiClass);
        lblYCoordinateMax->setObjectName(QString::fromUtf8("lblYCoordinateMax"));
        lblYCoordinateMax->setGeometry(QRect(0, 40, 46, 20));
        lblYCoordinateMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnPause = new QPushButton(AI_StreamingBufferedAiClass);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setEnabled(false);
        btnPause->setGeometry(QRect(530, 473, 81, 23));
        btnPause->setAutoDefault(false);
        btnStop = new QPushButton(AI_StreamingBufferedAiClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setEnabled(false);
        btnStop->setGeometry(QRect(630, 473, 81, 23));
        btnStop->setAutoDefault(false);
        QWidget::setTabOrder(btnConfigure, btnStart);
        QWidget::setTabOrder(btnStart, btnPause);
        QWidget::setTabOrder(btnPause, btnStop);
        QWidget::setTabOrder(btnStop, sldDiv);
        QWidget::setTabOrder(sldDiv, listWidget);

        retranslateUi(AI_StreamingBufferedAiClass);

        QMetaObject::connectSlotsByName(AI_StreamingBufferedAiClass);
    } // setupUi

    void retranslateUi(QDialog *AI_StreamingBufferedAiClass)
    {
        AI_StreamingBufferedAiClass->setWindowTitle(QCoreApplication::translate("AI_StreamingBufferedAiClass", "AI_StreamingAI", nullptr));
        lblDiv->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "Div:", nullptr));
        lblXCoordinateEnd->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "10Sec", nullptr));
        lblXCoordinateStart->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "0Sec", nullptr));
        btnConfigure->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "Configure", nullptr));
        lblColor->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "Color of\n"
"channel:", nullptr));
        lblYCoordinateMin->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "-10.0V", nullptr));
        btnStart->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "Start", nullptr));
        lblYCoordinateMid->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "0", nullptr));
        lblYCoordinateMax->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "10.0V", nullptr));
        btnPause->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "Pause", nullptr));
        btnStop->setText(QCoreApplication::translate("AI_StreamingBufferedAiClass", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AI_StreamingBufferedAiClass: public Ui_AI_StreamingBufferedAiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMINGBUFFEREDAI_H
