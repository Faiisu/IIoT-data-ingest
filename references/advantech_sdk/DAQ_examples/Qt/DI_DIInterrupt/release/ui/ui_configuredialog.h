/********************************************************************************
** Form generated from reading UI file 'configuredialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREDIALOG_H
#define UI_CONFIGUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigureDialog
{
public:
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QFrame *frame;
    QPushButton *btnBrowse;
    QLabel *lblDevice_2;
    QLabel *lblEnChanel;
    QLabel *lblDevice;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLineEdit *txtProfilePath;
    QComboBox *cmbDevice;
    QLabel *label;
    QLabel *lblHostname;
    QComboBox *cmbHostName;
    QPushButton *btnLogin;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->setEnabled(true);
        ConfigureDialog->resize(350, 420);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigureDialog->sizePolicy().hasHeightForWidth());
        ConfigureDialog->setSizePolicy(sizePolicy);
        ConfigureDialog->setMinimumSize(QSize(350, 420));
        ConfigureDialog->setSizeGripEnabled(false);
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(161, 386, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(252, 386, 75, 23));
        btnCancel->setAutoDefault(false);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 50, 331, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(250, 50, 51, 23));
        lblDevice_2 = new QLabel(frame);
        lblDevice_2->setObjectName(QString::fromUtf8("lblDevice_2"));
        lblDevice_2->setGeometry(QRect(16, 50, 41, 21));
        sizePolicy.setHeightForWidth(lblDevice_2->sizePolicy().hasHeightForWidth());
        lblDevice_2->setSizePolicy(sizePolicy);
        lblEnChanel = new QLabel(frame);
        lblEnChanel->setObjectName(QString::fromUtf8("lblEnChanel"));
        lblEnChanel->setGeometry(QRect(16, 84, 111, 22));
        sizePolicy.setHeightForWidth(lblEnChanel->sizePolicy().hasHeightForWidth());
        lblEnChanel->setSizePolicy(sizePolicy);
        lblEnChanel->setMinimumSize(QSize(111, 22));
        lblEnChanel->setMaximumSize(QSize(111, 22));
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(16, 10, 41, 21));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        scrollArea = new QScrollArea(frame);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(14, 131, 311, 181));
        scrollArea->setMinimumSize(QSize(311, 181));
        scrollArea->setMaximumSize(QSize(311, 181));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 309, 0));
        scrollAreaWidgetContents->setMinimumSize(QSize(309, 0));
        scrollArea->setWidget(scrollAreaWidgetContents);
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(66, 50, 171, 21));
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(66, 10, 171, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(16, 110, 311, 16));
        label->setMinimumSize(QSize(311, 16));
        label->setMaximumSize(QSize(311, 16));
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(4, 20, 61, 20));
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(75, 18, 171, 22));
        cmbHostName->setEditable(true);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(260, 20, 51, 21));
#if QT_CONFIG(shortcut)
        lblDevice_2->setBuddy(cmbDevice);
        lblEnChanel->setBuddy(cmbDevice);
        lblDevice->setBuddy(cmbDevice);
        lblHostname->setBuddy(cmbDevice);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(cmbDevice, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(ConfigureDialog);

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "DI Interrupt - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        lblDevice_2->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
        lblEnChanel->setText(QCoreApplication::translate("ConfigureDialog", "Enabled channels:", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        label->setText(QCoreApplication::translate("ConfigureDialog", "   Port No.      Bit7                      4            3                           0 ", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
