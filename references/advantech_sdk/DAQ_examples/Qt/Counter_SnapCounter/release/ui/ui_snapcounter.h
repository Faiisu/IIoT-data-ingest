/********************************************************************************
** Form generated from reading UI file 'snapcounter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAPCOUNTER_H
#define UI_SNAPCOUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SnapCounterClass
{
public:
    QFrame *background;
    QGroupBox *groupBox2;
    QLineEdit *txtCounterValue;
    QListWidget *CounterValueList;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnConfig;
    QGroupBox *groupBox1;
    QLabel *label;
    QListWidget *listSnapSource;
    QLabel *label_2;
    QLineEdit *txtTimeInterval;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *txtSnapCount;

    void setupUi(QDialog *SnapCounterClass)
    {
        if (SnapCounterClass->objectName().isEmpty())
            SnapCounterClass->setObjectName(QString::fromUtf8("SnapCounterClass"));
        SnapCounterClass->resize(534, 305);
        SnapCounterClass->setMinimumSize(QSize(534, 305));
        SnapCounterClass->setMaximumSize(QSize(534, 305));
        background = new QFrame(SnapCounterClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(7, 0, 541, 311));
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/SnapCounter/Resources/Background.bmp)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        groupBox2 = new QGroupBox(background);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(199, 48, 311, 241));
        groupBox2->setMinimumSize(QSize(311, 241));
        groupBox2->setMaximumSize(QSize(311, 241));
        groupBox2->setAutoFillBackground(true);
        txtCounterValue = new QLineEdit(groupBox2);
        txtCounterValue->setObjectName(QString::fromUtf8("txtCounterValue"));
        txtCounterValue->setGeometry(QRect(15, 10, 171, 25));
        txtCounterValue->setMinimumSize(QSize(171, 25));
        txtCounterValue->setMaximumSize(QSize(171, 25));
        txtCounterValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        CounterValueList = new QListWidget(groupBox2);
        CounterValueList->setObjectName(QString::fromUtf8("CounterValueList"));
        CounterValueList->setGeometry(QRect(15, 46, 171, 181));
        CounterValueList->setMinimumSize(QSize(171, 181));
        CounterValueList->setMaximumSize(QSize(171, 181));
        CounterValueList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        CounterValueList->setMovement(QListView::Static);
        btnStart = new QPushButton(groupBox2);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(210, 20, 75, 23));
        btnStart->setMinimumSize(QSize(75, 23));
        btnStart->setMaximumSize(QSize(75, 23));
        btnStop = new QPushButton(groupBox2);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(210, 66, 75, 23));
        btnStop->setMinimumSize(QSize(75, 23));
        btnStop->setMaximumSize(QSize(75, 23));
        btnConfig = new QPushButton(groupBox2);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(210, 184, 75, 23));
        btnConfig->setMinimumSize(QSize(75, 23));
        btnConfig->setMaximumSize(QSize(75, 23));
        groupBox1 = new QGroupBox(background);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(11, 48, 171, 201));
        groupBox1->setMinimumSize(QSize(171, 201));
        label = new QLabel(groupBox1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(15, 6, 71, 21));
        label->setMinimumSize(QSize(71, 21));
        listSnapSource = new QListWidget(groupBox1);
        listSnapSource->setObjectName(QString::fromUtf8("listSnapSource"));
        listSnapSource->setGeometry(QRect(15, 30, 141, 111));
        listSnapSource->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listSnapSource->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listSnapSource->setSelectionMode(QAbstractItemView::MultiSelection);
        listSnapSource->setModelColumn(0);
        label_2 = new QLabel(groupBox1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(14, 152, 71, 16));
        label_2->setMinimumSize(QSize(71, 16));
        txtTimeInterval = new QLineEdit(groupBox1);
        txtTimeInterval->setObjectName(QString::fromUtf8("txtTimeInterval"));
        txtTimeInterval->setEnabled(false);
        txtTimeInterval->setGeometry(QRect(82, 148, 73, 25));
        txtTimeInterval->setMinimumSize(QSize(73, 25));
        txtTimeInterval->setReadOnly(false);
        label_3 = new QLabel(groupBox1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(24, 179, 121, 16));
        label_3->setMinimumSize(QSize(121, 16));
        label_4 = new QLabel(background);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(25, 259, 61, 21));
        label_4->setMinimumSize(QSize(61, 21));
        txtSnapCount = new QLineEdit(background);
        txtSnapCount->setObjectName(QString::fromUtf8("txtSnapCount"));
        txtSnapCount->setEnabled(true);
        txtSnapCount->setGeometry(QRect(93, 259, 73, 25));
        txtSnapCount->setMinimumSize(QSize(73, 25));
        txtSnapCount->setReadOnly(true);

        retranslateUi(SnapCounterClass);

        QMetaObject::connectSlotsByName(SnapCounterClass);
    } // setupUi

    void retranslateUi(QDialog *SnapCounterClass)
    {
        SnapCounterClass->setWindowTitle(QCoreApplication::translate("SnapCounterClass", "Counter_SnapCounter", nullptr));
        groupBox2->setTitle(QString());
        btnStart->setText(QCoreApplication::translate("SnapCounterClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("SnapCounterClass", "Stop", nullptr));
        btnConfig->setText(QCoreApplication::translate("SnapCounterClass", "Configure...", nullptr));
        groupBox1->setTitle(QString());
        label->setText(QCoreApplication::translate("SnapCounterClass", "Snap source:", nullptr));
        label_2->setText(QCoreApplication::translate("SnapCounterClass", "Time interval:", nullptr));
        label_3->setText(QCoreApplication::translate("SnapCounterClass", "(From 0.02Hz to 50kHz)", nullptr));
        label_4->setText(QCoreApplication::translate("SnapCounterClass", "Snap count:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SnapCounterClass: public Ui_SnapCounterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAPCOUNTER_H
