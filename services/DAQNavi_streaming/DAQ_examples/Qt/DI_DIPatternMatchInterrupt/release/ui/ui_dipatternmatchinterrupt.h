/********************************************************************************
** Form generated from reading UI file 'dipatternmatchinterrupt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIPATTERNMATCHINTERRUPT_H
#define UI_DIPATTERNMATCHINTERRUPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DIPatternMatchInterruptClass
{
public:
    QFrame *background;
    QTableWidget *eventDataList;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnConfig;
    QLabel *gifViewer;

    void setupUi(QDialog *DIPatternMatchInterruptClass)
    {
        if (DIPatternMatchInterruptClass->objectName().isEmpty())
            DIPatternMatchInterruptClass->setObjectName(QString::fromUtf8("DIPatternMatchInterruptClass"));
        DIPatternMatchInterruptClass->resize(436, 283);
        DIPatternMatchInterruptClass->setMinimumSize(QSize(436, 283));
        DIPatternMatchInterruptClass->setMaximumSize(QSize(436, 283));
        background = new QFrame(DIPatternMatchInterruptClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(1, 0, 436, 283));
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/DIPatternMatchInterrupt/Resources/DiBackground.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        eventDataList = new QTableWidget(background);
        eventDataList->setObjectName(QString::fromUtf8("eventDataList"));
        eventDataList->setGeometry(QRect(16, 44, 311, 221));
        eventDataList->setMinimumSize(QSize(311, 221));
        eventDataList->setAutoScroll(true);
        eventDataList->setShowGrid(false);
        eventDataList->setRowCount(0);
        eventDataList->setColumnCount(0);
        eventDataList->verticalHeader()->setVisible(false);
        btnStart = new QPushButton(background);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(340, 80, 82, 23));
        btnStart->setMinimumSize(QSize(75, 23));
        btnStop = new QPushButton(background);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(340, 130, 82, 23));
        btnStop->setMinimumSize(QSize(75, 23));
        btnConfig = new QPushButton(background);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(340, 190, 82, 23));
        btnConfig->setMinimumSize(QSize(75, 23));
        gifViewer = new QLabel(background);
        gifViewer->setObjectName(QString::fromUtf8("gifViewer"));
        gifViewer->setGeometry(QRect(263, 10, 25, 25));
        gifViewer->setMinimumSize(QSize(25, 25));

        retranslateUi(DIPatternMatchInterruptClass);

        QMetaObject::connectSlotsByName(DIPatternMatchInterruptClass);
    } // setupUi

    void retranslateUi(QDialog *DIPatternMatchInterruptClass)
    {
        DIPatternMatchInterruptClass->setWindowTitle(QCoreApplication::translate("DIPatternMatchInterruptClass", "DI Pattern Match Interrupt", nullptr));
        btnStart->setText(QCoreApplication::translate("DIPatternMatchInterruptClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("DIPatternMatchInterruptClass", "Stop", nullptr));
        btnConfig->setText(QCoreApplication::translate("DIPatternMatchInterruptClass", "Configure", nullptr));
        gifViewer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DIPatternMatchInterruptClass: public Ui_DIPatternMatchInterruptClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIPATTERNMATCHINTERRUPT_H
