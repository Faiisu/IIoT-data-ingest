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
    QLineEdit *txtenableChan;
    QLabel *Profile;
    QLineEdit *txtProfilePath;
    QGroupBox *groupBox4;
    QPushButton *btn13;
    QPushButton *btn12;
    QPushButton *btn11;
    QPushButton *btn10;
    QLabel *lblDevice;
    QLineEdit *edtpmValue;
    QGroupBox *groupBox1;
    QPushButton *btn07;
    QPushButton *btn06;
    QPushButton *btn05;
    QPushButton *btn04;
    QGroupBox *groupBox3;
    QPushButton *btn17;
    QPushButton *btn16;
    QPushButton *btn15;
    QPushButton *btn14;
    QLabel *lblDIPort;
    QComboBox *cmbDIport;
    QGroupBox *groupBox2;
    QPushButton *btn03;
    QPushButton *btn02;
    QPushButton *btn01;
    QPushButton *btn00;
    QLabel *lblEnChanel;
    QLabel *lblMatValue;
    QComboBox *cmbDevice;
    QPushButton *btnLogin;
    QComboBox *cmbHostName;
    QLabel *lblHostname;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->setEnabled(true);
        ConfigureDialog->resize(350, 340);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigureDialog->sizePolicy().hasHeightForWidth());
        ConfigureDialog->setSizePolicy(sizePolicy);
        ConfigureDialog->setMinimumSize(QSize(350, 340));
        ConfigureDialog->setSizeGripEnabled(false);
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(139, 300, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(230, 300, 75, 23));
        btnCancel->setAutoDefault(false);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(30, 50, 301, 241));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(230, 50, 51, 23));
        txtenableChan = new QLineEdit(frame);
        txtenableChan->setObjectName(QString::fromUtf8("txtenableChan"));
        txtenableChan->setGeometry(QRect(240, 150, 24, 24));
        txtenableChan->setMinimumSize(QSize(24, 24));
        txtenableChan->setAlignment(Qt::AlignCenter);
        txtenableChan->setReadOnly(true);
        Profile = new QLabel(frame);
        Profile->setObjectName(QString::fromUtf8("Profile"));
        Profile->setGeometry(QRect(10, 50, 51, 22));
        sizePolicy.setHeightForWidth(Profile->sizePolicy().hasHeightForWidth());
        Profile->setSizePolicy(sizePolicy);
        Profile->setMinimumSize(QSize(51, 22));
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(60, 50, 161, 20));
        groupBox4 = new QGroupBox(frame);
        groupBox4->setObjectName(QString::fromUtf8("groupBox4"));
        groupBox4->setGeometry(QRect(122, 206, 108, 31));
        groupBox4->setMinimumSize(QSize(108, 31));
        btn13 = new QPushButton(groupBox4);
        btn13->setObjectName(QString::fromUtf8("btn13"));
        btn13->setGeometry(QRect(3, 2, 24, 24));
        btn13->setMinimumSize(QSize(24, 24));
        btn13->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn13->setCheckable(false);
        btn13->setFlat(true);
        btn12 = new QPushButton(groupBox4);
        btn12->setObjectName(QString::fromUtf8("btn12"));
        btn12->setGeometry(QRect(29, 2, 24, 24));
        btn12->setMinimumSize(QSize(24, 24));
        btn12->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn12->setCheckable(false);
        btn12->setFlat(true);
        btn11 = new QPushButton(groupBox4);
        btn11->setObjectName(QString::fromUtf8("btn11"));
        btn11->setGeometry(QRect(55, 2, 24, 24));
        btn11->setMinimumSize(QSize(24, 24));
        btn11->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn11->setCheckable(false);
        btn11->setFlat(true);
        btn10 = new QPushButton(groupBox4);
        btn10->setObjectName(QString::fromUtf8("btn10"));
        btn10->setGeometry(QRect(80, 2, 24, 24));
        btn10->setMinimumSize(QSize(24, 24));
        btn10->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn10->setCheckable(false);
        btn10->setFlat(true);
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(10, 10, 51, 22));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        lblDevice->setMinimumSize(QSize(51, 22));
        edtpmValue = new QLineEdit(frame);
        edtpmValue->setObjectName(QString::fromUtf8("edtpmValue"));
        edtpmValue->setGeometry(QRect(240, 210, 24, 24));
        edtpmValue->setMinimumSize(QSize(24, 24));
        edtpmValue->setAlignment(Qt::AlignCenter);
        edtpmValue->setReadOnly(true);
        groupBox1 = new QGroupBox(frame);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(11, 145, 108, 31));
        groupBox1->setMinimumSize(QSize(108, 31));
        btn07 = new QPushButton(groupBox1);
        btn07->setObjectName(QString::fromUtf8("btn07"));
        btn07->setGeometry(QRect(3, 2, 24, 24));
        btn07->setMinimumSize(QSize(24, 24));
        btn07->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn07->setCheckable(false);
        btn07->setFlat(true);
        btn06 = new QPushButton(groupBox1);
        btn06->setObjectName(QString::fromUtf8("btn06"));
        btn06->setGeometry(QRect(29, 2, 24, 24));
        btn06->setMinimumSize(QSize(24, 24));
        btn06->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn06->setCheckable(false);
        btn06->setFlat(true);
        btn05 = new QPushButton(groupBox1);
        btn05->setObjectName(QString::fromUtf8("btn05"));
        btn05->setGeometry(QRect(55, 2, 24, 24));
        btn05->setMinimumSize(QSize(24, 24));
        btn05->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn05->setCheckable(false);
        btn05->setFlat(true);
        btn04 = new QPushButton(groupBox1);
        btn04->setObjectName(QString::fromUtf8("btn04"));
        btn04->setGeometry(QRect(80, 2, 24, 24));
        btn04->setMinimumSize(QSize(24, 24));
        btn04->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn04->setCheckable(false);
        btn04->setFlat(true);
        groupBox3 = new QGroupBox(frame);
        groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
        groupBox3->setGeometry(QRect(11, 206, 108, 31));
        groupBox3->setMinimumSize(QSize(108, 31));
        btn17 = new QPushButton(groupBox3);
        btn17->setObjectName(QString::fromUtf8("btn17"));
        btn17->setGeometry(QRect(3, 2, 24, 24));
        btn17->setMinimumSize(QSize(24, 24));
        btn17->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn17->setCheckable(false);
        btn17->setFlat(true);
        btn16 = new QPushButton(groupBox3);
        btn16->setObjectName(QString::fromUtf8("btn16"));
        btn16->setGeometry(QRect(29, 2, 24, 24));
        btn16->setMinimumSize(QSize(24, 24));
        btn16->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn16->setCheckable(false);
        btn16->setFlat(true);
        btn15 = new QPushButton(groupBox3);
        btn15->setObjectName(QString::fromUtf8("btn15"));
        btn15->setGeometry(QRect(55, 2, 24, 24));
        btn15->setMinimumSize(QSize(24, 24));
        btn15->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn15->setCheckable(false);
        btn15->setFlat(true);
        btn14 = new QPushButton(groupBox3);
        btn14->setObjectName(QString::fromUtf8("btn14"));
        btn14->setGeometry(QRect(80, 2, 24, 24));
        btn14->setMinimumSize(QSize(24, 24));
        btn14->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)"));
        btn14->setCheckable(false);
        btn14->setFlat(true);
        lblDIPort = new QLabel(frame);
        lblDIPort->setObjectName(QString::fromUtf8("lblDIPort"));
        lblDIPort->setGeometry(QRect(10, 90, 51, 22));
        sizePolicy.setHeightForWidth(lblDIPort->sizePolicy().hasHeightForWidth());
        lblDIPort->setSizePolicy(sizePolicy);
        lblDIPort->setMinimumSize(QSize(51, 22));
        cmbDIport = new QComboBox(frame);
        cmbDIport->setObjectName(QString::fromUtf8("cmbDIport"));
        cmbDIport->setGeometry(QRect(60, 90, 221, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbDIport->sizePolicy().hasHeightForWidth());
        cmbDIport->setSizePolicy(sizePolicy1);
        cmbDIport->setLayoutDirection(Qt::LeftToRight);
        groupBox2 = new QGroupBox(frame);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(123, 146, 108, 31));
        groupBox2->setMinimumSize(QSize(108, 31));
        btn03 = new QPushButton(groupBox2);
        btn03->setObjectName(QString::fromUtf8("btn03"));
        btn03->setGeometry(QRect(3, 2, 24, 24));
        btn03->setMinimumSize(QSize(24, 24));
        btn03->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn03->setCheckable(false);
        btn03->setFlat(true);
        btn02 = new QPushButton(groupBox2);
        btn02->setObjectName(QString::fromUtf8("btn02"));
        btn02->setGeometry(QRect(29, 2, 24, 24));
        btn02->setMinimumSize(QSize(24, 24));
        btn02->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn02->setCheckable(false);
        btn02->setFlat(true);
        btn01 = new QPushButton(groupBox2);
        btn01->setObjectName(QString::fromUtf8("btn01"));
        btn01->setGeometry(QRect(55, 2, 24, 24));
        btn01->setMinimumSize(QSize(24, 24));
        btn01->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn01->setCheckable(false);
        btn01->setFlat(true);
        btn00 = new QPushButton(groupBox2);
        btn00->setObjectName(QString::fromUtf8("btn00"));
        btn00->setGeometry(QRect(80, 2, 24, 24));
        btn00->setMinimumSize(QSize(24, 24));
        btn00->setStyleSheet(QString::fromUtf8("background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)"));
        btn00->setCheckable(false);
        btn00->setFlat(true);
        lblEnChanel = new QLabel(frame);
        lblEnChanel->setObjectName(QString::fromUtf8("lblEnChanel"));
        lblEnChanel->setGeometry(QRect(10, 120, 91, 22));
        sizePolicy.setHeightForWidth(lblEnChanel->sizePolicy().hasHeightForWidth());
        lblEnChanel->setSizePolicy(sizePolicy);
        lblEnChanel->setMinimumSize(QSize(91, 22));
        lblMatValue = new QLabel(frame);
        lblMatValue->setObjectName(QString::fromUtf8("lblMatValue"));
        lblMatValue->setGeometry(QRect(10, 183, 91, 22));
        sizePolicy.setHeightForWidth(lblMatValue->sizePolicy().hasHeightForWidth());
        lblMatValue->setSizePolicy(sizePolicy);
        lblMatValue->setMinimumSize(QSize(91, 22));
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(60, 10, 221, 21));
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(260, 20, 51, 21));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(91, 18, 161, 22));
        cmbHostName->setEditable(true);
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(20, 20, 61, 20));
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
#if QT_CONFIG(shortcut)
        Profile->setBuddy(cmbDevice);
        lblDevice->setBuddy(cmbDevice);
        lblDIPort->setBuddy(cmbDIport);
        lblEnChanel->setBuddy(cmbDevice);
        lblMatValue->setBuddy(cmbDevice);
        lblHostname->setBuddy(cmbDevice);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(cmbDevice, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(ConfigureDialog);

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "DI Pattern Match Interrupt - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        txtenableChan->setText(QCoreApplication::translate("ConfigureDialog", "0", nullptr));
        Profile->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
        groupBox4->setTitle(QString());
        btn13->setText(QString());
        btn12->setText(QString());
        btn11->setText(QString());
        btn10->setText(QString());
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        edtpmValue->setText(QCoreApplication::translate("ConfigureDialog", "FF", nullptr));
        groupBox1->setTitle(QString());
        btn07->setText(QString());
        btn06->setText(QString());
        btn05->setText(QString());
        btn04->setText(QString());
        groupBox3->setTitle(QString());
        btn17->setText(QString());
        btn16->setText(QString());
        btn15->setText(QString());
        btn14->setText(QString());
        lblDIPort->setText(QCoreApplication::translate("ConfigureDialog", "DI port:", nullptr));
        groupBox2->setTitle(QString());
        btn03->setText(QString());
        btn02->setText(QString());
        btn01->setText(QString());
        btn00->setText(QString());
        lblEnChanel->setText(QCoreApplication::translate("ConfigureDialog", "Enabled channels:", nullptr));
        lblMatValue->setText(QCoreApplication::translate("ConfigureDialog", "Matched value:", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
