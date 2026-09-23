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

QT_BEGIN_NAMESPACE

class Ui_ConfigureDialog
{
public:
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QFrame *frame;
    QPushButton *btnBrowse;
    QComboBox *cmbCounterChannel;
    QLabel *lblDevice_2;
    QLabel *label;
    QComboBox *cmbDevice;
    QLabel *lblDevice;
    QLineEdit *txtProfilePath;
    QLabel *lblHostname;
    QPushButton *btnLogin;
    QComboBox *cmbHostName;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->setEnabled(true);
        ConfigureDialog->resize(320, 230);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigureDialog->sizePolicy().hasHeightForWidth());
        ConfigureDialog->setSizePolicy(sizePolicy);
        ConfigureDialog->setMinimumSize(QSize(320, 230));
        ConfigureDialog->setSizeGripEnabled(false);
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(80, 190, 61, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(170, 190, 61, 23));
        btnCancel->setAutoDefault(false);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(27, 50, 281, 121));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(220, 50, 51, 23));
        cmbCounterChannel = new QComboBox(frame);
        cmbCounterChannel->setObjectName(QString::fromUtf8("cmbCounterChannel"));
        cmbCounterChannel->setGeometry(QRect(56, 90, 151, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbCounterChannel->sizePolicy().hasHeightForWidth());
        cmbCounterChannel->setSizePolicy(sizePolicy1);
        lblDevice_2 = new QLabel(frame);
        lblDevice_2->setObjectName(QString::fromUtf8("lblDevice_2"));
        lblDevice_2->setGeometry(QRect(6, 50, 41, 16));
        sizePolicy.setHeightForWidth(lblDevice_2->sizePolicy().hasHeightForWidth());
        lblDevice_2->setSizePolicy(sizePolicy);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 80, 51, 41));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(56, 10, 151, 21));
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(6, 10, 41, 16));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(56, 50, 151, 20));
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 22, 61, 20));
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(250, 22, 51, 21));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(82, 20, 151, 22));
        cmbHostName->setEditable(true);
#if QT_CONFIG(shortcut)
        lblDevice_2->setBuddy(cmbDevice);
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
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "DelayedPulseGeneration - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        lblDevice_2->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
        label->setText(QCoreApplication::translate("ConfigureDialog", "Counter\n"
"Channel:", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
