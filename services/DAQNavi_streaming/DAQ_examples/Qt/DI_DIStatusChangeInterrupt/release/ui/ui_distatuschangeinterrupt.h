/********************************************************************************
** Form generated from reading UI file 'distatuschangeinterrupt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTATUSCHANGEINTERRUPT_H
#define UI_DISTATUSCHANGEINTERRUPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DIStatusChangeInterruptClass
{
public:
    QFrame *background;
    QTableWidget *eventDataList;
    QLabel *gifViewer;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnConfig;

    void setupUi(QDialog *DIStatusChangeInterruptClass)
    {
        if (DIStatusChangeInterruptClass->objectName().isEmpty())
            DIStatusChangeInterruptClass->setObjectName(QString::fromUtf8("DIStatusChangeInterruptClass"));
        DIStatusChangeInterruptClass->resize(436, 277);
        DIStatusChangeInterruptClass->setMinimumSize(QSize(436, 277));
        DIStatusChangeInterruptClass->setMaximumSize(QSize(436, 277));
        background = new QFrame(DIStatusChangeInterruptClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(297, -12, 155, 120));
        background->setMinimumSize(QSize(155, 120));
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/DIStatusChangeInterrupt/Resources/DIBackground.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        eventDataList = new QTableWidget(DIStatusChangeInterruptClass);
        eventDataList->setObjectName(QString::fromUtf8("eventDataList"));
        eventDataList->setGeometry(QRect(14, 40, 321, 221));
        eventDataList->setMinimumSize(QSize(321, 221));
        eventDataList->setAutoScroll(true);
        eventDataList->setShowGrid(false);
        eventDataList->setRowCount(0);
        eventDataList->setColumnCount(0);
        eventDataList->verticalHeader()->setVisible(false);
        gifViewer = new QLabel(DIStatusChangeInterruptClass);
        gifViewer->setObjectName(QString::fromUtf8("gifViewer"));
        gifViewer->setGeometry(QRect(239, 7, 25, 25));
        gifViewer->setMinimumSize(QSize(25, 25));
        btnStart = new QPushButton(DIStatusChangeInterruptClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(348, 119, 75, 23));
        btnStart->setMinimumSize(QSize(75, 23));
        btnStop = new QPushButton(DIStatusChangeInterruptClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(348, 167, 75, 23));
        btnStop->setMinimumSize(QSize(75, 23));
        btnConfig = new QPushButton(DIStatusChangeInterruptClass);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(348, 227, 75, 23));
        btnConfig->setMinimumSize(QSize(75, 23));

        retranslateUi(DIStatusChangeInterruptClass);

        QMetaObject::connectSlotsByName(DIStatusChangeInterruptClass);
    } // setupUi

    void retranslateUi(QDialog *DIStatusChangeInterruptClass)
    {
        DIStatusChangeInterruptClass->setWindowTitle(QCoreApplication::translate("DIStatusChangeInterruptClass", "DI Status Change Interrupt", nullptr));
        gifViewer->setText(QString());
        btnStart->setText(QCoreApplication::translate("DIStatusChangeInterruptClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("DIStatusChangeInterruptClass", "Stop", nullptr));
        btnConfig->setText(QCoreApplication::translate("DIStatusChangeInterruptClass", "Configure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DIStatusChangeInterruptClass: public Ui_DIStatusChangeInterruptClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTATUSCHANGEINTERRUPT_H
