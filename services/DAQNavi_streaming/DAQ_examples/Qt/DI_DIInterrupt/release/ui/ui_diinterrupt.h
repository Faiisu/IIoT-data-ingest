/********************************************************************************
** Form generated from reading UI file 'diinterrupt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIINTERRUPT_H
#define UI_DIINTERRUPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DIInterruptClass
{
public:
    QPushButton *btnConfig;
    QFrame *background;
    QTableWidget *eventDataList;
    QLabel *gifViewer;
    QPushButton *btnStop;
    QPushButton *btnStart;

    void setupUi(QDialog *DIInterruptClass)
    {
        if (DIInterruptClass->objectName().isEmpty())
            DIInterruptClass->setObjectName(QString::fromUtf8("DIInterruptClass"));
        DIInterruptClass->resize(436, 277);
        DIInterruptClass->setMinimumSize(QSize(436, 277));
        DIInterruptClass->setMaximumSize(QSize(436, 277));
        btnConfig = new QPushButton(DIInterruptClass);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(346, 230, 81, 23));
        btnConfig->setMinimumSize(QSize(75, 23));
        background = new QFrame(DIInterruptClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(311, -2, 121, 51));
        background->setMinimumSize(QSize(0, 0));
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/DIInterrupt/Resources/Background.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        eventDataList = new QTableWidget(DIInterruptClass);
        eventDataList->setObjectName(QString::fromUtf8("eventDataList"));
        eventDataList->setGeometry(QRect(16, 38, 321, 221));
        eventDataList->setMinimumSize(QSize(321, 221));
        eventDataList->setAutoScroll(true);
        eventDataList->setShowGrid(false);
        eventDataList->setRowCount(0);
        eventDataList->setColumnCount(0);
        eventDataList->verticalHeader()->setVisible(false);
        gifViewer = new QLabel(DIInterruptClass);
        gifViewer->setObjectName(QString::fromUtf8("gifViewer"));
        gifViewer->setGeometry(QRect(241, 5, 25, 25));
        gifViewer->setMinimumSize(QSize(25, 25));
        btnStop = new QPushButton(DIInterruptClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(346, 165, 81, 23));
        btnStop->setMinimumSize(QSize(75, 23));
        btnStart = new QPushButton(DIInterruptClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(346, 117, 81, 23));
        btnStart->setMinimumSize(QSize(75, 23));

        retranslateUi(DIInterruptClass);

        QMetaObject::connectSlotsByName(DIInterruptClass);
    } // setupUi

    void retranslateUi(QDialog *DIInterruptClass)
    {
        DIInterruptClass->setWindowTitle(QCoreApplication::translate("DIInterruptClass", "DI Interrupt", nullptr));
        btnConfig->setText(QCoreApplication::translate("DIInterruptClass", "Configure", nullptr));
        gifViewer->setText(QString());
        btnStop->setText(QCoreApplication::translate("DIInterruptClass", "Stop", nullptr));
        btnStart->setText(QCoreApplication::translate("DIInterruptClass", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DIInterruptClass: public Ui_DIInterruptClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIINTERRUPT_H
