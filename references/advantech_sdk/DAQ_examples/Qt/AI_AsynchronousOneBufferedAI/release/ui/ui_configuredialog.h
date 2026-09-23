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
    QLineEdit *txtProfilePath;
    QGroupBox *grpAISetting;
    QComboBox *cmbChannelCount;
    QLabel *lblChannelCount;
    QLabel *lblSectionLength;
    QLabel *lblRateUnit;
    QComboBox *cmbValueRange;
    QComboBox *cmbChannelStart;
    QLineEdit *edtClockRatePerChan;
    QLabel *lblValueRange;
    QLabel *lblClockRate;
    QLineEdit *edtSectionLength;
    QLabel *lblChannelStart;
    QLabel *lblDevice;
    QComboBox *cmbDevice;
    QLabel *lblDevice_2;
    QComboBox *cmbHostName;
    QPushButton *btnLogin;
    QLabel *lblHostname;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->resize(380, 340);
        ConfigureDialog->setMinimumSize(QSize(380, 340));
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(190, 300, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(290, 300, 75, 23));
        btnCancel->setAutoDefault(false);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 40, 351, 261));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(260, 50, 51, 21));
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(60, 50, 191, 20));
        grpAISetting = new QGroupBox(frame);
        grpAISetting->setObjectName(QString::fromUtf8("grpAISetting"));
        grpAISetting->setGeometry(QRect(0, 80, 341, 171));
        cmbChannelCount = new QComboBox(grpAISetting);
        cmbChannelCount->setObjectName(QString::fromUtf8("cmbChannelCount"));
        cmbChannelCount->setGeometry(QRect(110, 50, 201, 20));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbChannelCount->sizePolicy().hasHeightForWidth());
        cmbChannelCount->setSizePolicy(sizePolicy);
        lblChannelCount = new QLabel(grpAISetting);
        lblChannelCount->setObjectName(QString::fromUtf8("lblChannelCount"));
        lblChannelCount->setGeometry(QRect(19, 50, 91, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblChannelCount->sizePolicy().hasHeightForWidth());
        lblChannelCount->setSizePolicy(sizePolicy1);
        lblSectionLength = new QLabel(grpAISetting);
        lblSectionLength->setObjectName(QString::fromUtf8("lblSectionLength"));
        lblSectionLength->setGeometry(QRect(9, 112, 91, 20));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblSectionLength->sizePolicy().hasHeightForWidth());
        lblSectionLength->setSizePolicy(sizePolicy2);
        lblRateUnit = new QLabel(grpAISetting);
        lblRateUnit->setObjectName(QString::fromUtf8("lblRateUnit"));
        lblRateUnit->setGeometry(QRect(320, 140, 16, 21));
        sizePolicy2.setHeightForWidth(lblRateUnit->sizePolicy().hasHeightForWidth());
        lblRateUnit->setSizePolicy(sizePolicy2);
        cmbValueRange = new QComboBox(grpAISetting);
        cmbValueRange->setObjectName(QString::fromUtf8("cmbValueRange"));
        cmbValueRange->setGeometry(QRect(110, 82, 201, 20));
        sizePolicy.setHeightForWidth(cmbValueRange->sizePolicy().hasHeightForWidth());
        cmbValueRange->setSizePolicy(sizePolicy);
        cmbChannelStart = new QComboBox(grpAISetting);
        cmbChannelStart->setObjectName(QString::fromUtf8("cmbChannelStart"));
        cmbChannelStart->setGeometry(QRect(110, 18, 201, 20));
        sizePolicy.setHeightForWidth(cmbChannelStart->sizePolicy().hasHeightForWidth());
        cmbChannelStart->setSizePolicy(sizePolicy);
        edtClockRatePerChan = new QLineEdit(grpAISetting);
        edtClockRatePerChan->setObjectName(QString::fromUtf8("edtClockRatePerChan"));
        edtClockRatePerChan->setGeometry(QRect(110, 142, 201, 20));
        edtClockRatePerChan->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblValueRange = new QLabel(grpAISetting);
        lblValueRange->setObjectName(QString::fromUtf8("lblValueRange"));
        lblValueRange->setGeometry(QRect(19, 82, 81, 16));
        sizePolicy2.setHeightForWidth(lblValueRange->sizePolicy().hasHeightForWidth());
        lblValueRange->setSizePolicy(sizePolicy2);
        lblClockRate = new QLabel(grpAISetting);
        lblClockRate->setObjectName(QString::fromUtf8("lblClockRate"));
        lblClockRate->setGeometry(QRect(19, 142, 71, 16));
        sizePolicy2.setHeightForWidth(lblClockRate->sizePolicy().hasHeightForWidth());
        lblClockRate->setSizePolicy(sizePolicy2);
        edtSectionLength = new QLineEdit(grpAISetting);
        edtSectionLength->setObjectName(QString::fromUtf8("edtSectionLength"));
        edtSectionLength->setGeometry(QRect(110, 112, 202, 20));
        edtSectionLength->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblChannelStart = new QLabel(grpAISetting);
        lblChannelStart->setObjectName(QString::fromUtf8("lblChannelStart"));
        lblChannelStart->setGeometry(QRect(19, 18, 91, 20));
        lblChannelStart->setMaximumSize(QSize(91, 22));
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(10, 10, 51, 16));
        sizePolicy2.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy2);
        lblDevice->setMaximumSize(QSize(91, 22));
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(60, 10, 251, 20));
        sizePolicy.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy);
        lblDevice_2 = new QLabel(frame);
        lblDevice_2->setObjectName(QString::fromUtf8("lblDevice_2"));
        lblDevice_2->setGeometry(QRect(10, 50, 51, 16));
        sizePolicy2.setHeightForWidth(lblDevice_2->sizePolicy().hasHeightForWidth());
        lblDevice_2->setSizePolicy(sizePolicy2);
        lblDevice_2->setMaximumSize(QSize(91, 22));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(80, 8, 191, 22));
        cmbHostName->setEditable(true);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(280, 10, 51, 21));
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 10, 61, 20));
        sizePolicy2.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy2);
#if QT_CONFIG(shortcut)
        lblChannelCount->setBuddy(cmbChannelCount);
        lblSectionLength->setBuddy(cmbValueRange);
        lblRateUnit->setBuddy(cmbValueRange);
        lblValueRange->setBuddy(cmbValueRange);
        lblClockRate->setBuddy(cmbValueRange);
        lblChannelStart->setBuddy(cmbChannelStart);
        lblDevice->setBuddy(cmbDevice);
        lblDevice_2->setBuddy(cmbDevice);
        lblHostname->setBuddy(cmbDevice);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(cmbDevice, cmbChannelStart);
        QWidget::setTabOrder(cmbChannelStart, cmbChannelCount);
        QWidget::setTabOrder(cmbChannelCount, cmbValueRange);
        QWidget::setTabOrder(cmbValueRange, edtSectionLength);
        QWidget::setTabOrder(edtSectionLength, edtClockRatePerChan);
        QWidget::setTabOrder(edtClockRatePerChan, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(ConfigureDialog);

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "Asynchronous One Buffered AI - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        grpAISetting->setTitle(QCoreApplication::translate("ConfigureDialog", "Buffered AI general settings", nullptr));
        lblChannelCount->setText(QCoreApplication::translate("ConfigureDialog", "Channel count:", nullptr));
        lblSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "Section Length:", nullptr));
        lblRateUnit->setText(QCoreApplication::translate("ConfigureDialog", "Hz", nullptr));
        edtClockRatePerChan->setText(QCoreApplication::translate("ConfigureDialog", "1000", nullptr));
        lblValueRange->setText(QCoreApplication::translate("ConfigureDialog", "Value range:", nullptr));
        lblClockRate->setText(QCoreApplication::translate("ConfigureDialog", "Clock rate:", nullptr));
        edtSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "1024", nullptr));
        lblChannelStart->setText(QCoreApplication::translate("ConfigureDialog", "Channel start:", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        lblDevice_2->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
