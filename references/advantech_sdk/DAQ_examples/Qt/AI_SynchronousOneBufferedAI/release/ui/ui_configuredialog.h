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
    QPushButton *btnCancel;
    QPushButton *btnOK;
    QComboBox *cmbHostName;
    QPushButton *btnLogin;
    QLabel *lblHostname;
    QFrame *frame;
    QPushButton *btnBrowse;
    QLineEdit *txtProfilePath;
    QGroupBox *groupBox;
    QLineEdit *edtClockRatePerChan;
    QComboBox *cmbChannelStart;
    QLabel *lblChannelCount;
    QLabel *lblSectionLength;
    QLabel *lblChannelStart;
    QComboBox *cmbChannelCount;
    QComboBox *cmbValueRange;
    QLabel *lblClockRate;
    QLineEdit *edtSectionLength;
    QLabel *lblValueRange;
    QLabel *lblRateUnit;
    QLabel *lblDevice;
    QComboBox *cmbDevice;
    QLabel *lblProfilePath;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->resize(374, 350);
        ConfigureDialog->setMinimumSize(QSize(374, 350));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(250, 313, 75, 23));
        btnCancel->setAutoDefault(false);
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(140, 313, 75, 23));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(80, 11, 191, 22));
        cmbHostName->setEditable(true);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(280, 13, 51, 21));
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 13, 61, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 43, 341, 271));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(260, 50, 51, 21));
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(70, 50, 181, 20));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 80, 331, 181));
        edtClockRatePerChan = new QLineEdit(groupBox);
        edtClockRatePerChan->setObjectName(QString::fromUtf8("edtClockRatePerChan"));
        edtClockRatePerChan->setGeometry(QRect(101, 150, 201, 20));
        edtClockRatePerChan->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        cmbChannelStart = new QComboBox(groupBox);
        cmbChannelStart->setObjectName(QString::fromUtf8("cmbChannelStart"));
        cmbChannelStart->setGeometry(QRect(101, 26, 201, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbChannelStart->sizePolicy().hasHeightForWidth());
        cmbChannelStart->setSizePolicy(sizePolicy1);
        lblChannelCount = new QLabel(groupBox);
        lblChannelCount->setObjectName(QString::fromUtf8("lblChannelCount"));
        lblChannelCount->setGeometry(QRect(10, 58, 91, 22));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblChannelCount->sizePolicy().hasHeightForWidth());
        lblChannelCount->setSizePolicy(sizePolicy2);
        lblChannelCount->setMinimumSize(QSize(91, 22));
        lblChannelCount->setMaximumSize(QSize(91, 22));
        lblSectionLength = new QLabel(groupBox);
        lblSectionLength->setObjectName(QString::fromUtf8("lblSectionLength"));
        lblSectionLength->setGeometry(QRect(10, 120, 91, 16));
        sizePolicy.setHeightForWidth(lblSectionLength->sizePolicy().hasHeightForWidth());
        lblSectionLength->setSizePolicy(sizePolicy);
        lblChannelStart = new QLabel(groupBox);
        lblChannelStart->setObjectName(QString::fromUtf8("lblChannelStart"));
        lblChannelStart->setGeometry(QRect(10, 26, 91, 22));
        lblChannelStart->setMinimumSize(QSize(91, 22));
        lblChannelStart->setMaximumSize(QSize(91, 22));
        cmbChannelCount = new QComboBox(groupBox);
        cmbChannelCount->setObjectName(QString::fromUtf8("cmbChannelCount"));
        cmbChannelCount->setGeometry(QRect(101, 58, 201, 20));
        sizePolicy1.setHeightForWidth(cmbChannelCount->sizePolicy().hasHeightForWidth());
        cmbChannelCount->setSizePolicy(sizePolicy1);
        cmbValueRange = new QComboBox(groupBox);
        cmbValueRange->setObjectName(QString::fromUtf8("cmbValueRange"));
        cmbValueRange->setGeometry(QRect(101, 90, 201, 20));
        sizePolicy1.setHeightForWidth(cmbValueRange->sizePolicy().hasHeightForWidth());
        cmbValueRange->setSizePolicy(sizePolicy1);
        lblClockRate = new QLabel(groupBox);
        lblClockRate->setObjectName(QString::fromUtf8("lblClockRate"));
        lblClockRate->setGeometry(QRect(10, 150, 71, 16));
        sizePolicy.setHeightForWidth(lblClockRate->sizePolicy().hasHeightForWidth());
        lblClockRate->setSizePolicy(sizePolicy);
        edtSectionLength = new QLineEdit(groupBox);
        edtSectionLength->setObjectName(QString::fromUtf8("edtSectionLength"));
        edtSectionLength->setGeometry(QRect(101, 120, 201, 20));
        edtSectionLength->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblValueRange = new QLabel(groupBox);
        lblValueRange->setObjectName(QString::fromUtf8("lblValueRange"));
        lblValueRange->setGeometry(QRect(10, 90, 81, 16));
        sizePolicy.setHeightForWidth(lblValueRange->sizePolicy().hasHeightForWidth());
        lblValueRange->setSizePolicy(sizePolicy);
        lblValueRange->setMaximumSize(QSize(91, 22));
        lblRateUnit = new QLabel(groupBox);
        lblRateUnit->setObjectName(QString::fromUtf8("lblRateUnit"));
        lblRateUnit->setGeometry(QRect(303, 150, 21, 22));
        sizePolicy.setHeightForWidth(lblRateUnit->sizePolicy().hasHeightForWidth());
        lblRateUnit->setSizePolicy(sizePolicy);
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(10, 11, 51, 16));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(60, 10, 241, 20));
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        lblProfilePath = new QLabel(frame);
        lblProfilePath->setObjectName(QString::fromUtf8("lblProfilePath"));
        lblProfilePath->setGeometry(QRect(10, 50, 51, 20));
        sizePolicy.setHeightForWidth(lblProfilePath->sizePolicy().hasHeightForWidth());
        lblProfilePath->setSizePolicy(sizePolicy);
#if QT_CONFIG(shortcut)
        lblHostname->setBuddy(cmbDevice);
        lblChannelCount->setBuddy(cmbChannelCount);
        lblSectionLength->setBuddy(cmbValueRange);
        lblChannelStart->setBuddy(cmbChannelStart);
        lblClockRate->setBuddy(cmbValueRange);
        lblValueRange->setBuddy(cmbValueRange);
        lblRateUnit->setBuddy(cmbValueRange);
        lblDevice->setBuddy(cmbDevice);
        lblProfilePath->setBuddy(cmbDevice);
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
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "Synchronous One Buffered AI - Configuration", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConfigureDialog", "Buffered AI setting", nullptr));
        edtClockRatePerChan->setText(QCoreApplication::translate("ConfigureDialog", "1000", nullptr));
        lblChannelCount->setText(QCoreApplication::translate("ConfigureDialog", "Channel count:", nullptr));
        lblSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "Section Length:", nullptr));
        lblChannelStart->setText(QCoreApplication::translate("ConfigureDialog", "Channel start:", nullptr));
        lblClockRate->setText(QCoreApplication::translate("ConfigureDialog", "Clock rate:", nullptr));
        edtSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "1024", nullptr));
        lblValueRange->setText(QCoreApplication::translate("ConfigureDialog", "Value range:", nullptr));
        lblRateUnit->setText(QCoreApplication::translate("ConfigureDialog", "Hz", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        lblProfilePath->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
