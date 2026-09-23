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
#include <QtWidgets/QGroupBox>
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
    QComboBox *cmbDevice;
    QGroupBox *groupBox2;
    QPushButton *btn03;
    QPushButton *btn02;
    QPushButton *btn01;
    QPushButton *btn00;
    QLineEdit *txtenableChan;
    QComboBox *cmbDIport;
    QLabel *lblDIPort;
    QLabel *lblEnChanel;
    QLineEdit *txtProfilePath;
    QGroupBox *groupBox1;
    QPushButton *btn07;
    QPushButton *btn06;
    QPushButton *btn05;
    QPushButton *btn04;
    QLabel *lblProfile;
    QLabel *lblDevice;
    QPushButton *btnLogin;
    QComboBox *cmbHostName;
    QLabel *lblHostname;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->setEnabled(true);
        ConfigureDialog->resize(350, 290);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigureDialog->sizePolicy().hasHeightForWidth());
        ConfigureDialog->setSizePolicy(sizePolicy);
        ConfigureDialog->setMinimumSize(QSize(350, 290));
        ConfigureDialog->setSizeGripEnabled(false);
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(129, 240, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(220, 240, 75, 23));
        btnCancel->setAutoDefault(false);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(29, 50, 281, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(223, 60, 51, 21));
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(53, 10, 221, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        groupBox2 = new QGroupBox(frame);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(116, 156, 108, 31));
        groupBox2->setMinimumSize(QSize(108, 31));
        btn03 = new QPushButton(groupBox2);
        btn03->setObjectName(QString::fromUtf8("btn03"));
        btn03->setGeometry(QRect(3, 2, 24, 24));
        btn03->setMinimumSize(QSize(24, 24));
        btn03->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn03->setCheckable(false);
        btn03->setFlat(true);
        btn02 = new QPushButton(groupBox2);
        btn02->setObjectName(QString::fromUtf8("btn02"));
        btn02->setGeometry(QRect(29, 2, 24, 24));
        btn02->setMinimumSize(QSize(24, 24));
        btn02->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn02->setCheckable(false);
        btn02->setFlat(true);
        btn01 = new QPushButton(groupBox2);
        btn01->setObjectName(QString::fromUtf8("btn01"));
        btn01->setGeometry(QRect(55, 2, 24, 24));
        btn01->setMinimumSize(QSize(24, 24));
        btn01->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn01->setCheckable(false);
        btn01->setFlat(true);
        btn00 = new QPushButton(groupBox2);
        btn00->setObjectName(QString::fromUtf8("btn00"));
        btn00->setGeometry(QRect(80, 2, 24, 24));
        btn00->setMinimumSize(QSize(24, 24));
        btn00->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn00->setCheckable(false);
        btn00->setFlat(true);
        txtenableChan = new QLineEdit(frame);
        txtenableChan->setObjectName(QString::fromUtf8("txtenableChan"));
        txtenableChan->setGeometry(QRect(233, 160, 24, 24));
        txtenableChan->setMinimumSize(QSize(24, 24));
        txtenableChan->setAlignment(Qt::AlignCenter);
        txtenableChan->setReadOnly(true);
        cmbDIport = new QComboBox(frame);
        cmbDIport->setObjectName(QString::fromUtf8("cmbDIport"));
        cmbDIport->setGeometry(QRect(53, 100, 221, 21));
        sizePolicy1.setHeightForWidth(cmbDIport->sizePolicy().hasHeightForWidth());
        cmbDIport->setSizePolicy(sizePolicy1);
        cmbDIport->setLayoutDirection(Qt::LeftToRight);
        lblDIPort = new QLabel(frame);
        lblDIPort->setObjectName(QString::fromUtf8("lblDIPort"));
        lblDIPort->setGeometry(QRect(3, 100, 51, 22));
        sizePolicy.setHeightForWidth(lblDIPort->sizePolicy().hasHeightForWidth());
        lblDIPort->setSizePolicy(sizePolicy);
        lblDIPort->setMinimumSize(QSize(51, 22));
        lblEnChanel = new QLabel(frame);
        lblEnChanel->setObjectName(QString::fromUtf8("lblEnChanel"));
        lblEnChanel->setGeometry(QRect(3, 130, 91, 22));
        sizePolicy.setHeightForWidth(lblEnChanel->sizePolicy().hasHeightForWidth());
        lblEnChanel->setSizePolicy(sizePolicy);
        lblEnChanel->setMinimumSize(QSize(91, 22));
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(53, 60, 161, 20));
        groupBox1 = new QGroupBox(frame);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(4, 155, 108, 31));
        groupBox1->setMinimumSize(QSize(108, 31));
        btn07 = new QPushButton(groupBox1);
        btn07->setObjectName(QString::fromUtf8("btn07"));
        btn07->setGeometry(QRect(3, 2, 24, 24));
        btn07->setMinimumSize(QSize(24, 24));
        btn07->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn07->setCheckable(false);
        btn07->setFlat(true);
        btn06 = new QPushButton(groupBox1);
        btn06->setObjectName(QString::fromUtf8("btn06"));
        btn06->setGeometry(QRect(29, 2, 24, 24));
        btn06->setMinimumSize(QSize(24, 24));
        btn06->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn06->setCheckable(false);
        btn06->setFlat(true);
        btn05 = new QPushButton(groupBox1);
        btn05->setObjectName(QString::fromUtf8("btn05"));
        btn05->setGeometry(QRect(55, 2, 24, 24));
        btn05->setMinimumSize(QSize(24, 24));
        btn05->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn05->setCheckable(false);
        btn05->setFlat(true);
        btn04 = new QPushButton(groupBox1);
        btn04->setObjectName(QString::fromUtf8("btn04"));
        btn04->setGeometry(QRect(80, 2, 24, 24));
        btn04->setMinimumSize(QSize(24, 24));
        btn04->setStyleSheet(QString::fromUtf8("background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)"));
        btn04->setCheckable(false);
        btn04->setFlat(true);
        lblProfile = new QLabel(frame);
        lblProfile->setObjectName(QString::fromUtf8("lblProfile"));
        lblProfile->setGeometry(QRect(3, 60, 51, 22));
        sizePolicy.setHeightForWidth(lblProfile->sizePolicy().hasHeightForWidth());
        lblProfile->setSizePolicy(sizePolicy);
        lblProfile->setMinimumSize(QSize(51, 22));
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(0, 12, 51, 22));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        lblDevice->setMinimumSize(QSize(51, 22));
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(250, 22, 51, 21));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(81, 20, 161, 22));
        cmbHostName->setEditable(true);
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 22, 61, 20));
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
#if QT_CONFIG(shortcut)
        lblDIPort->setBuddy(cmbDIport);
        lblEnChanel->setBuddy(cmbDevice);
        lblProfile->setBuddy(cmbDevice);
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
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "DI Status Change Interrupt - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        groupBox2->setTitle(QString());
        btn03->setText(QString());
        btn02->setText(QString());
        btn01->setText(QString());
        btn00->setText(QString());
        txtenableChan->setText(QCoreApplication::translate("ConfigureDialog", "0", nullptr));
        lblDIPort->setText(QCoreApplication::translate("ConfigureDialog", "DI port:", nullptr));
        lblEnChanel->setText(QCoreApplication::translate("ConfigureDialog", "Enabled channels:", nullptr));
        groupBox1->setTitle(QString());
        btn07->setText(QString());
        btn06->setText(QString());
        btn05->setText(QString());
        btn04->setText(QString());
        lblProfile->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
