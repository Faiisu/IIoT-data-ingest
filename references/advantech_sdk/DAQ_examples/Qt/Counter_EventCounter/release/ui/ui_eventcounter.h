/********************************************************************************
** Form generated from reading UI file 'eventcounter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTCOUNTER_H
#define UI_EVENTCOUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EventCounterClass
{
public:
    QFrame *bkgrndImage;
    QGroupBox *groupBox;
    QListWidget *cntrValueList;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnConfig;
    QLineEdit *curValueEditor;

    void setupUi(QDialog *EventCounterClass)
    {
        if (EventCounterClass->objectName().isEmpty())
            EventCounterClass->setObjectName(QString::fromUtf8("EventCounterClass"));
        EventCounterClass->resize(352, 246);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EventCounterClass->sizePolicy().hasHeightForWidth());
        EventCounterClass->setSizePolicy(sizePolicy);
        EventCounterClass->setMinimumSize(QSize(352, 246));
        EventCounterClass->setMaximumSize(QSize(352, 246));
        bkgrndImage = new QFrame(EventCounterClass);
        bkgrndImage->setObjectName(QString::fromUtf8("bkgrndImage"));
        bkgrndImage->setGeometry(QRect(194, -7, 171, 58));
        bkgrndImage->setFrameShape(QFrame::StyledPanel);
        bkgrndImage->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(EventCounterClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(14, 43, 321, 191));
        groupBox->setAutoFillBackground(true);
        cntrValueList = new QListWidget(groupBox);
        cntrValueList->setObjectName(QString::fromUtf8("cntrValueList"));
        cntrValueList->setGeometry(QRect(9, 46, 171, 135));
        cntrValueList->setFlow(QListView::TopToBottom);
        cntrValueList->setProperty("isWrapping", QVariant(false));
        btnStart = new QPushButton(groupBox);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(204, 40, 91, 23));
        btnStop = new QPushButton(groupBox);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(204, 90, 91, 23));
        btnConfig = new QPushButton(groupBox);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(204, 140, 91, 23));
        curValueEditor = new QLineEdit(groupBox);
        curValueEditor->setObjectName(QString::fromUtf8("curValueEditor"));
        curValueEditor->setGeometry(QRect(9, 10, 171, 25));
        curValueEditor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        curValueEditor->setReadOnly(true);

        retranslateUi(EventCounterClass);

        QMetaObject::connectSlotsByName(EventCounterClass);
    } // setupUi

    void retranslateUi(QDialog *EventCounterClass)
    {
        EventCounterClass->setWindowTitle(QCoreApplication::translate("EventCounterClass", "Event Counter", nullptr));
        groupBox->setTitle(QString());
        btnStart->setText(QCoreApplication::translate("EventCounterClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("EventCounterClass", "Stop", nullptr));
        btnConfig->setText(QCoreApplication::translate("EventCounterClass", "Configure", nullptr));
        curValueEditor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EventCounterClass: public Ui_EventCounterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTCOUNTER_H
