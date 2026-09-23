/********************************************************************************
** Form generated from reading UI file 'staticdi.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATICDI_H
#define UI_STATICDI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StaticDIClass
{
public:
    QFrame *background;
    QPushButton *btnConfig;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QDialog *StaticDIClass)
    {
        if (StaticDIClass->objectName().isEmpty())
            StaticDIClass->setObjectName(QString::fromUtf8("StaticDIClass"));
        StaticDIClass->resize(470, 432);
        StaticDIClass->setMinimumSize(QSize(470, 432));
        StaticDIClass->setMaximumSize(QSize(470, 432));
        background = new QFrame(StaticDIClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(286, -4, 191, 91));
        background->setMinimumSize(QSize(191, 91));
        background->setAutoFillBackground(false);
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/StaticDI/Resources/Background.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        btnConfig = new QPushButton(StaticDIClass);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(303, 398, 91, 23));
        btnConfig->setMinimumSize(QSize(75, 23));
        label = new QLabel(StaticDIClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(27, 52, 361, 16));
        label->setMinimumSize(QSize(361, 16));
        label->setMaximumSize(QSize(361, 16));
        scrollArea = new QScrollArea(StaticDIClass);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(26, 71, 369, 317));
        scrollArea->setMinimumSize(QSize(369, 317));
        scrollArea->setMaximumSize(QSize(369, 317));
        scrollArea->setSizeIncrement(QSize(369, 317));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 341, 0));
        scrollAreaWidgetContents->setMinimumSize(QSize(341, 0));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(StaticDIClass);

        QMetaObject::connectSlotsByName(StaticDIClass);
    } // setupUi

    void retranslateUi(QDialog *StaticDIClass)
    {
        StaticDIClass->setWindowTitle(QCoreApplication::translate("StaticDIClass", "Static DI", nullptr));
        btnConfig->setText(QCoreApplication::translate("StaticDIClass", "Configure", nullptr));
        label->setText(QCoreApplication::translate("StaticDIClass", "Port No.    Bit7                          4            3                             0          Hex", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StaticDIClass: public Ui_StaticDIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATICDI_H
