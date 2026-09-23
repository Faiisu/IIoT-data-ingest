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
    QLabel *lblDevice;
    QLabel *label_2;
    QLineEdit *txtProfilePath;
    QComboBox *cmbCountingType;
    QLabel *label;
    QComboBox *cmbDevice;
    QLabel *lblProfilePath;
    QComboBox *cmbCounterChannel;
    QLabel *lblHostname;
    QPushButton *btnLogin;
    QComboBox *cmbHostName;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->setEnabled(true);
        ConfigureDialog->resize(330, 260);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigureDialog->sizePolicy().hasHeightForWidth());
        ConfigureDialog->setSizePolicy(sizePolicy);
        ConfigureDialog->setMinimumSize(QSize(330, 260));
        ConfigureDialog->setSizeGripEnabled(false);
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(70, 220, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(160, 220, 75, 23));
        btnCancel->setAutoDefault(false);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 40, 291, 161));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(230, 50, 51, 23));
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(10, 10, 41, 16));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 120, 51, 41));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(60, 50, 161, 21));
        cmbCountingType = new QComboBox(frame);
        cmbCountingType->setObjectName(QString::fromUtf8("cmbCountingType"));
        cmbCountingType->setGeometry(QRect(60, 130, 161, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbCountingType->sizePolicy().hasHeightForWidth());
        cmbCountingType->setSizePolicy(sizePolicy1);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 80, 41, 41));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(60, 10, 161, 21));
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        lblProfilePath = new QLabel(frame);
        lblProfilePath->setObjectName(QString::fromUtf8("lblProfilePath"));
        lblProfilePath->setGeometry(QRect(10, 50, 41, 21));
        sizePolicy.setHeightForWidth(lblProfilePath->sizePolicy().hasHeightForWidth());
        lblProfilePath->setSizePolicy(sizePolicy);
        cmbCounterChannel = new QComboBox(frame);
        cmbCounterChannel->setObjectName(QString::fromUtf8("cmbCounterChannel"));
        cmbCounterChannel->setGeometry(QRect(60, 90, 161, 21));
        sizePolicy1.setHeightForWidth(cmbCounterChannel->sizePolicy().hasHeightForWidth());
        cmbCounterChannel->setSizePolicy(sizePolicy1);
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 12, 61, 20));
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(250, 12, 51, 21));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(80, 10, 161, 22));
        cmbHostName->setEditable(true);
#if QT_CONFIG(shortcut)
        lblDevice->setBuddy(cmbDevice);
        lblProfilePath->setBuddy(cmbDevice);
        lblHostname->setBuddy(cmbDevice);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(cmbDevice, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(ConfigureDialog);

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "Snap Counter - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        label_2->setText(QCoreApplication::translate("ConfigureDialog", "Counting\n"
"Type:", nullptr));
        label->setText(QCoreApplication::translate("ConfigureDialog", "Counter\n"
"Channel:", nullptr));
        lblProfilePath->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
