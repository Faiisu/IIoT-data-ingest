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
    QComboBox *cmbHostName;
    QPushButton *btnLogin;
    QLabel *lblHostname;
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
    QComboBox *cmbDevice;
    QLabel *lblDevice;
    QGroupBox *grpTriggerSetting;
    QComboBox *cmbTriggerEdge;
    QLabel *lblTriggerEdge;
    QLabel *lblTriggerDelayCount;
    QLabel *lblTriggerLevelUnit;
    QComboBox *cmbTriggerSource;
    QLineEdit *txtTriggerLevel;
    QLabel *lblTriggerLevel;
    QLineEdit *txtDelayCount;
    QLabel *lblTriggerSource;
    QLabel *lblTriggerIndex;
    QComboBox *cmbTriggerTriggerIndex;
    QLabel *lblProfilePath;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->resize(600, 320);
        ConfigureDialog->setMinimumSize(QSize(600, 320));
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(410, 280, 75, 25));
        btnOK->setMinimumSize(QSize(75, 25));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(500, 280, 75, 25));
        btnCancel->setMinimumSize(QSize(75, 25));
        btnCancel->setAutoDefault(false);
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(90, 8, 421, 22));
        cmbHostName->setEditable(true);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(520, 10, 51, 21));
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 10, 61, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 40, 571, 231));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(500, 0, 51, 23));
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(320, 0, 171, 20));
        grpAISetting = new QGroupBox(frame);
        grpAISetting->setObjectName(QString::fromUtf8("grpAISetting"));
        grpAISetting->setGeometry(QRect(0, 40, 271, 181));
        cmbChannelCount = new QComboBox(grpAISetting);
        cmbChannelCount->setObjectName(QString::fromUtf8("cmbChannelCount"));
        cmbChannelCount->setGeometry(QRect(110, 60, 131, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbChannelCount->sizePolicy().hasHeightForWidth());
        cmbChannelCount->setSizePolicy(sizePolicy1);
        lblChannelCount = new QLabel(grpAISetting);
        lblChannelCount->setObjectName(QString::fromUtf8("lblChannelCount"));
        lblChannelCount->setGeometry(QRect(19, 60, 91, 22));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblChannelCount->sizePolicy().hasHeightForWidth());
        lblChannelCount->setSizePolicy(sizePolicy2);
        lblChannelCount->setMinimumSize(QSize(91, 22));
        lblChannelCount->setMaximumSize(QSize(91, 22));
        lblSectionLength = new QLabel(grpAISetting);
        lblSectionLength->setObjectName(QString::fromUtf8("lblSectionLength"));
        lblSectionLength->setGeometry(QRect(9, 120, 91, 22));
        sizePolicy.setHeightForWidth(lblSectionLength->sizePolicy().hasHeightForWidth());
        lblSectionLength->setSizePolicy(sizePolicy);
        lblRateUnit = new QLabel(grpAISetting);
        lblRateUnit->setObjectName(QString::fromUtf8("lblRateUnit"));
        lblRateUnit->setGeometry(QRect(250, 150, 21, 22));
        sizePolicy.setHeightForWidth(lblRateUnit->sizePolicy().hasHeightForWidth());
        lblRateUnit->setSizePolicy(sizePolicy);
        cmbValueRange = new QComboBox(grpAISetting);
        cmbValueRange->setObjectName(QString::fromUtf8("cmbValueRange"));
        cmbValueRange->setGeometry(QRect(110, 90, 131, 21));
        sizePolicy1.setHeightForWidth(cmbValueRange->sizePolicy().hasHeightForWidth());
        cmbValueRange->setSizePolicy(sizePolicy1);
        cmbChannelStart = new QComboBox(grpAISetting);
        cmbChannelStart->setObjectName(QString::fromUtf8("cmbChannelStart"));
        cmbChannelStart->setGeometry(QRect(110, 30, 131, 21));
        sizePolicy1.setHeightForWidth(cmbChannelStart->sizePolicy().hasHeightForWidth());
        cmbChannelStart->setSizePolicy(sizePolicy1);
        edtClockRatePerChan = new QLineEdit(grpAISetting);
        edtClockRatePerChan->setObjectName(QString::fromUtf8("edtClockRatePerChan"));
        edtClockRatePerChan->setGeometry(QRect(110, 150, 131, 21));
        edtClockRatePerChan->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblValueRange = new QLabel(grpAISetting);
        lblValueRange->setObjectName(QString::fromUtf8("lblValueRange"));
        lblValueRange->setGeometry(QRect(19, 90, 91, 22));
        sizePolicy.setHeightForWidth(lblValueRange->sizePolicy().hasHeightForWidth());
        lblValueRange->setSizePolicy(sizePolicy);
        lblValueRange->setMinimumSize(QSize(91, 22));
        lblValueRange->setMaximumSize(QSize(91, 22));
        lblClockRate = new QLabel(grpAISetting);
        lblClockRate->setObjectName(QString::fromUtf8("lblClockRate"));
        lblClockRate->setGeometry(QRect(19, 150, 91, 22));
        sizePolicy.setHeightForWidth(lblClockRate->sizePolicy().hasHeightForWidth());
        lblClockRate->setSizePolicy(sizePolicy);
        lblClockRate->setMinimumSize(QSize(91, 22));
        lblClockRate->setMaximumSize(QSize(91, 22));
        edtSectionLength = new QLineEdit(grpAISetting);
        edtSectionLength->setObjectName(QString::fromUtf8("edtSectionLength"));
        edtSectionLength->setGeometry(QRect(110, 120, 131, 21));
        edtSectionLength->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblChannelStart = new QLabel(grpAISetting);
        lblChannelStart->setObjectName(QString::fromUtf8("lblChannelStart"));
        lblChannelStart->setGeometry(QRect(19, 30, 91, 22));
        lblChannelStart->setMinimumSize(QSize(91, 22));
        lblChannelStart->setMaximumSize(QSize(91, 22));
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(70, 0, 191, 21));
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(10, 0, 41, 21));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        lblDevice->setMaximumSize(QSize(91, 22));
        grpTriggerSetting = new QGroupBox(frame);
        grpTriggerSetting->setObjectName(QString::fromUtf8("grpTriggerSetting"));
        grpTriggerSetting->setGeometry(QRect(280, 40, 281, 181));
        cmbTriggerEdge = new QComboBox(grpTriggerSetting);
        cmbTriggerEdge->setObjectName(QString::fromUtf8("cmbTriggerEdge"));
        cmbTriggerEdge->setGeometry(QRect(110, 90, 151, 21));
        sizePolicy1.setHeightForWidth(cmbTriggerEdge->sizePolicy().hasHeightForWidth());
        cmbTriggerEdge->setSizePolicy(sizePolicy1);
        lblTriggerEdge = new QLabel(grpTriggerSetting);
        lblTriggerEdge->setObjectName(QString::fromUtf8("lblTriggerEdge"));
        lblTriggerEdge->setGeometry(QRect(20, 90, 91, 22));
        sizePolicy2.setHeightForWidth(lblTriggerEdge->sizePolicy().hasHeightForWidth());
        lblTriggerEdge->setSizePolicy(sizePolicy2);
        lblTriggerEdge->setMinimumSize(QSize(91, 22));
        lblTriggerEdge->setMaximumSize(QSize(91, 22));
        lblTriggerDelayCount = new QLabel(grpTriggerSetting);
        lblTriggerDelayCount->setObjectName(QString::fromUtf8("lblTriggerDelayCount"));
        lblTriggerDelayCount->setGeometry(QRect(20, 120, 91, 22));
        sizePolicy.setHeightForWidth(lblTriggerDelayCount->sizePolicy().hasHeightForWidth());
        lblTriggerDelayCount->setSizePolicy(sizePolicy);
        lblTriggerDelayCount->setMinimumSize(QSize(91, 22));
        lblTriggerDelayCount->setMaximumSize(QSize(91, 22));
        lblTriggerLevelUnit = new QLabel(grpTriggerSetting);
        lblTriggerLevelUnit->setObjectName(QString::fromUtf8("lblTriggerLevelUnit"));
        lblTriggerLevelUnit->setGeometry(QRect(240, 150, 21, 22));
        sizePolicy.setHeightForWidth(lblTriggerLevelUnit->sizePolicy().hasHeightForWidth());
        lblTriggerLevelUnit->setSizePolicy(sizePolicy);
        lblTriggerLevelUnit->setMinimumSize(QSize(21, 22));
        lblTriggerLevelUnit->setMaximumSize(QSize(21, 22));
        cmbTriggerSource = new QComboBox(grpTriggerSetting);
        cmbTriggerSource->setObjectName(QString::fromUtf8("cmbTriggerSource"));
        cmbTriggerSource->setGeometry(QRect(110, 60, 151, 21));
        sizePolicy1.setHeightForWidth(cmbTriggerSource->sizePolicy().hasHeightForWidth());
        cmbTriggerSource->setSizePolicy(sizePolicy1);
        txtTriggerLevel = new QLineEdit(grpTriggerSetting);
        txtTriggerLevel->setObjectName(QString::fromUtf8("txtTriggerLevel"));
        txtTriggerLevel->setGeometry(QRect(110, 150, 121, 21));
        txtTriggerLevel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblTriggerLevel = new QLabel(grpTriggerSetting);
        lblTriggerLevel->setObjectName(QString::fromUtf8("lblTriggerLevel"));
        lblTriggerLevel->setGeometry(QRect(20, 150, 91, 22));
        sizePolicy.setHeightForWidth(lblTriggerLevel->sizePolicy().hasHeightForWidth());
        lblTriggerLevel->setSizePolicy(sizePolicy);
        lblTriggerLevel->setMinimumSize(QSize(91, 22));
        lblTriggerLevel->setMaximumSize(QSize(91, 22));
        txtDelayCount = new QLineEdit(grpTriggerSetting);
        txtDelayCount->setObjectName(QString::fromUtf8("txtDelayCount"));
        txtDelayCount->setGeometry(QRect(110, 120, 121, 21));
        txtDelayCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblTriggerSource = new QLabel(grpTriggerSetting);
        lblTriggerSource->setObjectName(QString::fromUtf8("lblTriggerSource"));
        lblTriggerSource->setGeometry(QRect(20, 60, 91, 22));
        lblTriggerSource->setMinimumSize(QSize(91, 22));
        lblTriggerSource->setMaximumSize(QSize(91, 22));
        lblTriggerIndex = new QLabel(grpTriggerSetting);
        lblTriggerIndex->setObjectName(QString::fromUtf8("lblTriggerIndex"));
        lblTriggerIndex->setGeometry(QRect(20, 30, 91, 22));
        lblTriggerIndex->setMinimumSize(QSize(91, 22));
        lblTriggerIndex->setMaximumSize(QSize(91, 22));
        cmbTriggerTriggerIndex = new QComboBox(grpTriggerSetting);
        cmbTriggerTriggerIndex->setObjectName(QString::fromUtf8("cmbTriggerTriggerIndex"));
        cmbTriggerTriggerIndex->setGeometry(QRect(110, 30, 151, 21));
        sizePolicy1.setHeightForWidth(cmbTriggerTriggerIndex->sizePolicy().hasHeightForWidth());
        cmbTriggerTriggerIndex->setSizePolicy(sizePolicy1);
        lblProfilePath = new QLabel(frame);
        lblProfilePath->setObjectName(QString::fromUtf8("lblProfilePath"));
        lblProfilePath->setGeometry(QRect(270, 0, 51, 21));
        sizePolicy.setHeightForWidth(lblProfilePath->sizePolicy().hasHeightForWidth());
        lblProfilePath->setSizePolicy(sizePolicy);
        lblProfilePath->setMaximumSize(QSize(91, 22));
#if QT_CONFIG(shortcut)
        lblHostname->setBuddy(cmbDevice);
        lblChannelCount->setBuddy(cmbChannelCount);
        lblSectionLength->setBuddy(cmbValueRange);
        lblRateUnit->setBuddy(cmbValueRange);
        lblValueRange->setBuddy(cmbValueRange);
        lblClockRate->setBuddy(cmbValueRange);
        lblChannelStart->setBuddy(cmbChannelStart);
        lblDevice->setBuddy(cmbDevice);
        lblTriggerEdge->setBuddy(cmbChannelCount);
        lblTriggerDelayCount->setBuddy(cmbValueRange);
        lblTriggerLevelUnit->setBuddy(cmbValueRange);
        lblTriggerLevel->setBuddy(cmbValueRange);
        lblTriggerSource->setBuddy(cmbChannelStart);
        lblTriggerIndex->setBuddy(cmbChannelStart);
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
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "Asynchronous One Buffered AI with Trigger Delay to Stop - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        grpAISetting->setTitle(QCoreApplication::translate("ConfigureDialog", "Buffered AI settings", nullptr));
        lblChannelCount->setText(QCoreApplication::translate("ConfigureDialog", "Channel count:", nullptr));
        lblSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "Section Length:", nullptr));
        lblRateUnit->setText(QCoreApplication::translate("ConfigureDialog", "Hz", nullptr));
        edtClockRatePerChan->setText(QCoreApplication::translate("ConfigureDialog", "1000", nullptr));
        lblValueRange->setText(QCoreApplication::translate("ConfigureDialog", "Value range:", nullptr));
        lblClockRate->setText(QCoreApplication::translate("ConfigureDialog", "Clock rate:", nullptr));
        edtSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "1024", nullptr));
        lblChannelStart->setText(QCoreApplication::translate("ConfigureDialog", "Channel start:", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        grpTriggerSetting->setTitle(QCoreApplication::translate("ConfigureDialog", "Trigger settings", nullptr));
        lblTriggerEdge->setText(QCoreApplication::translate("ConfigureDialog", "Edge:", nullptr));
        lblTriggerDelayCount->setText(QCoreApplication::translate("ConfigureDialog", "Delay count:", nullptr));
        lblTriggerLevelUnit->setText(QCoreApplication::translate("ConfigureDialog", "V", nullptr));
        txtTriggerLevel->setText(QCoreApplication::translate("ConfigureDialog", "3", nullptr));
        lblTriggerLevel->setText(QCoreApplication::translate("ConfigureDialog", "Trigger level:", nullptr));
        txtDelayCount->setText(QCoreApplication::translate("ConfigureDialog", "500", nullptr));
        lblTriggerSource->setText(QCoreApplication::translate("ConfigureDialog", "Source:", nullptr));
        lblTriggerIndex->setText(QCoreApplication::translate("ConfigureDialog", "Trigger:", nullptr));
        lblProfilePath->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
