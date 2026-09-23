/********************************************************************************
** Form generated from reading UI file 'streamingai_tdtr.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMINGAI_TDTR_H
#define UI_STREAMINGAI_TDTR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_StreamingAI_TDtrClass
{
public:
    QPushButton *btnStop;
    QPushButton *btnPause;
    QListWidget *listWidget;
    QPushButton *btnStart;
    QLabel *lblColor;
    QSlider *sldDiv;
    QLabel *lblYCoordinateMax;
    QFrame *graphFrame;
    QLabel *lblXCoordinateStart;
    QPushButton *btnConfigure;
    QLabel *lblYCoordinateMin;
    QLabel *lblYCoordinateMid;
    QLabel *lblXCoordinateEnd;
    QLabel *lblDiv;

    void setupUi(QDialog *StreamingAI_TDtrClass)
    {
        if (StreamingAI_TDtrClass->objectName().isEmpty())
            StreamingAI_TDtrClass->setObjectName(QString::fromUtf8("StreamingAI_TDtrClass"));
        StreamingAI_TDtrClass->resize(762, 515);
        StreamingAI_TDtrClass->setMinimumSize(QSize(762, 515));
        StreamingAI_TDtrClass->setMaximumSize(QSize(762, 515));
        btnStop = new QPushButton(StreamingAI_TDtrClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setEnabled(true);
        btnStop->setGeometry(QRect(633, 470, 81, 23));
        btnStop->setAutoDefault(false);
        btnPause = new QPushButton(StreamingAI_TDtrClass);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setEnabled(true);
        btnPause->setGeometry(QRect(533, 470, 81, 23));
        btnPause->setAutoDefault(false);
        listWidget = new QListWidget(StreamingAI_TDtrClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(103, 397, 440, 45));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        btnStart = new QPushButton(StreamingAI_TDtrClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setEnabled(true);
        btnStart->setGeometry(QRect(433, 470, 81, 23));
        btnStart->setAutoDefault(true);
        lblColor = new QLabel(StreamingAI_TDtrClass);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        lblColor->setGeometry(QRect(37, 401, 61, 41));
        lblColor->setLayoutDirection(Qt::LeftToRight);
        sldDiv = new QSlider(StreamingAI_TDtrClass);
        sldDiv->setObjectName(QString::fromUtf8("sldDiv"));
        sldDiv->setEnabled(true);
        sldDiv->setGeometry(QRect(589, 411, 121, 21));
        sldDiv->setMinimum(10);
        sldDiv->setMaximum(1000);
        sldDiv->setSingleStep(10);
        sldDiv->setValue(200);
        sldDiv->setOrientation(Qt::Horizontal);
        sldDiv->setTickPosition(QSlider::NoTicks);
        lblYCoordinateMax = new QLabel(StreamingAI_TDtrClass);
        lblYCoordinateMax->setObjectName(QString::fromUtf8("lblYCoordinateMax"));
        lblYCoordinateMax->setGeometry(QRect(3, 37, 46, 20));
        lblYCoordinateMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        graphFrame = new QFrame(StreamingAI_TDtrClass);
        graphFrame->setObjectName(QString::fromUtf8("graphFrame"));
        graphFrame->setGeometry(QRect(52, 36, 660, 340));
        graphFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        lblXCoordinateStart = new QLabel(StreamingAI_TDtrClass);
        lblXCoordinateStart->setObjectName(QString::fromUtf8("lblXCoordinateStart"));
        lblXCoordinateStart->setGeometry(QRect(53, 379, 71, 16));
        lblXCoordinateStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        btnConfigure = new QPushButton(StreamingAI_TDtrClass);
        btnConfigure->setObjectName(QString::fromUtf8("btnConfigure"));
        btnConfigure->setEnabled(true);
        btnConfigure->setGeometry(QRect(274, 470, 91, 23));
        btnConfigure->setAutoDefault(false);
        lblYCoordinateMin = new QLabel(StreamingAI_TDtrClass);
        lblYCoordinateMin->setObjectName(QString::fromUtf8("lblYCoordinateMin"));
        lblYCoordinateMin->setGeometry(QRect(3, 357, 46, 16));
        lblYCoordinateMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblYCoordinateMid = new QLabel(StreamingAI_TDtrClass);
        lblYCoordinateMid->setObjectName(QString::fromUtf8("lblYCoordinateMid"));
        lblYCoordinateMid->setGeometry(QRect(3, 197, 46, 16));
        lblYCoordinateMid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblXCoordinateEnd = new QLabel(StreamingAI_TDtrClass);
        lblXCoordinateEnd->setObjectName(QString::fromUtf8("lblXCoordinateEnd"));
        lblXCoordinateEnd->setGeometry(QRect(621, 378, 90, 16));
        lblXCoordinateEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblDiv = new QLabel(StreamingAI_TDtrClass);
        lblDiv->setObjectName(QString::fromUtf8("lblDiv"));
        lblDiv->setGeometry(QRect(553, 414, 31, 16));
        lblDiv->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(StreamingAI_TDtrClass);

        QMetaObject::connectSlotsByName(StreamingAI_TDtrClass);
    } // setupUi

    void retranslateUi(QDialog *StreamingAI_TDtrClass)
    {
        StreamingAI_TDtrClass->setWindowTitle(QCoreApplication::translate("StreamingAI_TDtrClass", "Streaming AI with Trigger Delay to Start", nullptr));
        btnStop->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "Stop", nullptr));
        btnPause->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "Pause", nullptr));
        btnStart->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "Start", nullptr));
        lblColor->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "Color of\n"
"channel:", nullptr));
        lblYCoordinateMax->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "10.0V", nullptr));
        lblXCoordinateStart->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "0Sec", nullptr));
        btnConfigure->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "Configure", nullptr));
        lblYCoordinateMin->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "-10.0V", nullptr));
        lblYCoordinateMid->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "0", nullptr));
        lblXCoordinateEnd->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "10Sec", nullptr));
        lblDiv->setText(QCoreApplication::translate("StreamingAI_TDtrClass", "Div:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StreamingAI_TDtrClass: public Ui_StreamingAI_TDtrClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMINGAI_TDTR_H
