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
    QLabel *lblDevice;
    QLineEdit *txtProfilePath;
    QGroupBox *grpTriggerSetting_2;
    QComboBox *cmbTriggerEdge_2;
    QLabel *lblTriggerEdge_2;
    QLabel *lblTriggerDelayCount_2;
    QLabel *lblTriggerLevelUnit_2;
    QComboBox *cmbTriggerSource_2;
    QLineEdit *txtTriggerLevel_2;
    QLabel *lblTriggerLevel_2;
    QLineEdit *txtDelayCount_2;
    QLabel *lblTriggerSource_2;
    QLabel *lblProfileName;
    QGroupBox *grpAISetting;
    QComboBox *cmbChannelCount;
    QLabel *lblChannelCount;
    QLabel *lblRateUnit;
    QComboBox *cmbValueRange;
    QComboBox *cmbChannelStart;
    QLineEdit *edtClockRatePerChan;
    QLabel *lblValueRange;
    QLabel *lblClockRate;
    QLabel *lblChannelStart;
    QLineEdit *edtSectionLength;
    QLabel *lblSectionLength;
    QLineEdit *edtCycles;
    QLabel *lblCycles;
    QComboBox *cmbDevice;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->resize(600, 420);
        ConfigureDialog->setMinimumSize(QSize(600, 420));
        ConfigureDialog->setMaximumSize(QSize(643, 500));
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(320, 380, 75, 25));
        btnOK->setMinimumSize(QSize(75, 25));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(470, 380, 75, 25));
        btnCancel->setMinimumSize(QSize(75, 25));
        btnCancel->setAutoDefault(false);
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(80, 18, 441, 22));
        cmbHostName->setEditable(true);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(530, 20, 51, 21));
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 20, 61, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 50, 571, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(510, 10, 51, 23));
        grpTriggerSetting = new QGroupBox(frame);
        grpTriggerSetting->setObjectName(QString::fromUtf8("grpTriggerSetting"));
        grpTriggerSetting->setGeometry(QRect(280, 40, 281, 131));
        cmbTriggerEdge = new QComboBox(grpTriggerSetting);
        cmbTriggerEdge->setObjectName(QString::fromUtf8("cmbTriggerEdge"));
        cmbTriggerEdge->setGeometry(QRect(110, 47, 151, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbTriggerEdge->sizePolicy().hasHeightForWidth());
        cmbTriggerEdge->setSizePolicy(sizePolicy1);
        lblTriggerEdge = new QLabel(grpTriggerSetting);
        lblTriggerEdge->setObjectName(QString::fromUtf8("lblTriggerEdge"));
        lblTriggerEdge->setGeometry(QRect(19, 45, 91, 22));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblTriggerEdge->sizePolicy().hasHeightForWidth());
        lblTriggerEdge->setSizePolicy(sizePolicy2);
        lblTriggerEdge->setMinimumSize(QSize(91, 22));
        lblTriggerEdge->setMaximumSize(QSize(91, 22));
        lblTriggerDelayCount = new QLabel(grpTriggerSetting);
        lblTriggerDelayCount->setObjectName(QString::fromUtf8("lblTriggerDelayCount"));
        lblTriggerDelayCount->setGeometry(QRect(19, 76, 91, 22));
        sizePolicy.setHeightForWidth(lblTriggerDelayCount->sizePolicy().hasHeightForWidth());
        lblTriggerDelayCount->setSizePolicy(sizePolicy);
        lblTriggerDelayCount->setMinimumSize(QSize(91, 22));
        lblTriggerDelayCount->setMaximumSize(QSize(91, 22));
        lblTriggerLevelUnit = new QLabel(grpTriggerSetting);
        lblTriggerLevelUnit->setObjectName(QString::fromUtf8("lblTriggerLevelUnit"));
        lblTriggerLevelUnit->setGeometry(QRect(235, 102, 21, 22));
        sizePolicy.setHeightForWidth(lblTriggerLevelUnit->sizePolicy().hasHeightForWidth());
        lblTriggerLevelUnit->setSizePolicy(sizePolicy);
        lblTriggerLevelUnit->setMinimumSize(QSize(21, 22));
        lblTriggerLevelUnit->setMaximumSize(QSize(21, 22));
        cmbTriggerSource = new QComboBox(grpTriggerSetting);
        cmbTriggerSource->setObjectName(QString::fromUtf8("cmbTriggerSource"));
        cmbTriggerSource->setGeometry(QRect(110, 18, 151, 21));
        sizePolicy1.setHeightForWidth(cmbTriggerSource->sizePolicy().hasHeightForWidth());
        cmbTriggerSource->setSizePolicy(sizePolicy1);
        txtTriggerLevel = new QLineEdit(grpTriggerSetting);
        txtTriggerLevel->setObjectName(QString::fromUtf8("txtTriggerLevel"));
        txtTriggerLevel->setGeometry(QRect(110, 103, 121, 21));
        txtTriggerLevel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblTriggerLevel = new QLabel(grpTriggerSetting);
        lblTriggerLevel->setObjectName(QString::fromUtf8("lblTriggerLevel"));
        lblTriggerLevel->setGeometry(QRect(19, 103, 91, 22));
        sizePolicy.setHeightForWidth(lblTriggerLevel->sizePolicy().hasHeightForWidth());
        lblTriggerLevel->setSizePolicy(sizePolicy);
        lblTriggerLevel->setMinimumSize(QSize(91, 22));
        lblTriggerLevel->setMaximumSize(QSize(91, 22));
        txtDelayCount = new QLineEdit(grpTriggerSetting);
        txtDelayCount->setObjectName(QString::fromUtf8("txtDelayCount"));
        txtDelayCount->setGeometry(QRect(110, 75, 121, 21));
        txtDelayCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblTriggerSource = new QLabel(grpTriggerSetting);
        lblTriggerSource->setObjectName(QString::fromUtf8("lblTriggerSource"));
        lblTriggerSource->setGeometry(QRect(19, 18, 91, 22));
        lblTriggerSource->setMinimumSize(QSize(91, 22));
        lblTriggerSource->setMaximumSize(QSize(91, 22));
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(10, 10, 51, 22));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        lblDevice->setMaximumSize(QSize(91, 22));
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(300, 10, 201, 21));
        txtProfilePath->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        grpTriggerSetting_2 = new QGroupBox(frame);
        grpTriggerSetting_2->setObjectName(QString::fromUtf8("grpTriggerSetting_2"));
        grpTriggerSetting_2->setGeometry(QRect(280, 170, 281, 141));
        cmbTriggerEdge_2 = new QComboBox(grpTriggerSetting_2);
        cmbTriggerEdge_2->setObjectName(QString::fromUtf8("cmbTriggerEdge_2"));
        cmbTriggerEdge_2->setGeometry(QRect(110, 50, 151, 21));
        sizePolicy1.setHeightForWidth(cmbTriggerEdge_2->sizePolicy().hasHeightForWidth());
        cmbTriggerEdge_2->setSizePolicy(sizePolicy1);
        lblTriggerEdge_2 = new QLabel(grpTriggerSetting_2);
        lblTriggerEdge_2->setObjectName(QString::fromUtf8("lblTriggerEdge_2"));
        lblTriggerEdge_2->setGeometry(QRect(19, 50, 91, 22));
        sizePolicy2.setHeightForWidth(lblTriggerEdge_2->sizePolicy().hasHeightForWidth());
        lblTriggerEdge_2->setSizePolicy(sizePolicy2);
        lblTriggerEdge_2->setMinimumSize(QSize(91, 22));
        lblTriggerEdge_2->setMaximumSize(QSize(91, 22));
        lblTriggerDelayCount_2 = new QLabel(grpTriggerSetting_2);
        lblTriggerDelayCount_2->setObjectName(QString::fromUtf8("lblTriggerDelayCount_2"));
        lblTriggerDelayCount_2->setGeometry(QRect(19, 79, 91, 22));
        sizePolicy.setHeightForWidth(lblTriggerDelayCount_2->sizePolicy().hasHeightForWidth());
        lblTriggerDelayCount_2->setSizePolicy(sizePolicy);
        lblTriggerDelayCount_2->setMinimumSize(QSize(91, 22));
        lblTriggerDelayCount_2->setMaximumSize(QSize(91, 22));
        lblTriggerLevelUnit_2 = new QLabel(grpTriggerSetting_2);
        lblTriggerLevelUnit_2->setObjectName(QString::fromUtf8("lblTriggerLevelUnit_2"));
        lblTriggerLevelUnit_2->setGeometry(QRect(235, 108, 21, 22));
        sizePolicy.setHeightForWidth(lblTriggerLevelUnit_2->sizePolicy().hasHeightForWidth());
        lblTriggerLevelUnit_2->setSizePolicy(sizePolicy);
        lblTriggerLevelUnit_2->setMinimumSize(QSize(21, 22));
        lblTriggerLevelUnit_2->setMaximumSize(QSize(21, 22));
        cmbTriggerSource_2 = new QComboBox(grpTriggerSetting_2);
        cmbTriggerSource_2->setObjectName(QString::fromUtf8("cmbTriggerSource_2"));
        cmbTriggerSource_2->setGeometry(QRect(110, 18, 151, 21));
        sizePolicy1.setHeightForWidth(cmbTriggerSource_2->sizePolicy().hasHeightForWidth());
        cmbTriggerSource_2->setSizePolicy(sizePolicy1);
        txtTriggerLevel_2 = new QLineEdit(grpTriggerSetting_2);
        txtTriggerLevel_2->setObjectName(QString::fromUtf8("txtTriggerLevel_2"));
        txtTriggerLevel_2->setGeometry(QRect(110, 109, 121, 21));
        txtTriggerLevel_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblTriggerLevel_2 = new QLabel(grpTriggerSetting_2);
        lblTriggerLevel_2->setObjectName(QString::fromUtf8("lblTriggerLevel_2"));
        lblTriggerLevel_2->setGeometry(QRect(19, 109, 91, 22));
        sizePolicy.setHeightForWidth(lblTriggerLevel_2->sizePolicy().hasHeightForWidth());
        lblTriggerLevel_2->setSizePolicy(sizePolicy);
        lblTriggerLevel_2->setMinimumSize(QSize(91, 22));
        lblTriggerLevel_2->setMaximumSize(QSize(91, 22));
        txtDelayCount_2 = new QLineEdit(grpTriggerSetting_2);
        txtDelayCount_2->setObjectName(QString::fromUtf8("txtDelayCount_2"));
        txtDelayCount_2->setGeometry(QRect(110, 79, 121, 21));
        txtDelayCount_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblTriggerSource_2 = new QLabel(grpTriggerSetting_2);
        lblTriggerSource_2->setObjectName(QString::fromUtf8("lblTriggerSource_2"));
        lblTriggerSource_2->setGeometry(QRect(19, 18, 91, 22));
        lblTriggerSource_2->setMinimumSize(QSize(91, 22));
        lblTriggerSource_2->setMaximumSize(QSize(91, 22));
        lblProfileName = new QLabel(frame);
        lblProfileName->setObjectName(QString::fromUtf8("lblProfileName"));
        lblProfileName->setGeometry(QRect(250, 10, 41, 22));
        sizePolicy.setHeightForWidth(lblProfileName->sizePolicy().hasHeightForWidth());
        lblProfileName->setSizePolicy(sizePolicy);
        lblProfileName->setMaximumSize(QSize(91, 22));
        grpAISetting = new QGroupBox(frame);
        grpAISetting->setObjectName(QString::fromUtf8("grpAISetting"));
        grpAISetting->setGeometry(QRect(0, 40, 271, 271));
        cmbChannelCount = new QComboBox(grpAISetting);
        cmbChannelCount->setObjectName(QString::fromUtf8("cmbChannelCount"));
        cmbChannelCount->setGeometry(QRect(110, 70, 151, 21));
        sizePolicy1.setHeightForWidth(cmbChannelCount->sizePolicy().hasHeightForWidth());
        cmbChannelCount->setSizePolicy(sizePolicy1);
        lblChannelCount = new QLabel(grpAISetting);
        lblChannelCount->setObjectName(QString::fromUtf8("lblChannelCount"));
        lblChannelCount->setGeometry(QRect(20, 70, 91, 22));
        sizePolicy2.setHeightForWidth(lblChannelCount->sizePolicy().hasHeightForWidth());
        lblChannelCount->setSizePolicy(sizePolicy2);
        lblChannelCount->setMinimumSize(QSize(91, 22));
        lblChannelCount->setMaximumSize(QSize(91, 22));
        lblRateUnit = new QLabel(grpAISetting);
        lblRateUnit->setObjectName(QString::fromUtf8("lblRateUnit"));
        lblRateUnit->setGeometry(QRect(250, 150, 21, 22));
        sizePolicy.setHeightForWidth(lblRateUnit->sizePolicy().hasHeightForWidth());
        lblRateUnit->setSizePolicy(sizePolicy);
        cmbValueRange = new QComboBox(grpAISetting);
        cmbValueRange->setObjectName(QString::fromUtf8("cmbValueRange"));
        cmbValueRange->setGeometry(QRect(110, 110, 151, 21));
        sizePolicy1.setHeightForWidth(cmbValueRange->sizePolicy().hasHeightForWidth());
        cmbValueRange->setSizePolicy(sizePolicy1);
        cmbChannelStart = new QComboBox(grpAISetting);
        cmbChannelStart->setObjectName(QString::fromUtf8("cmbChannelStart"));
        cmbChannelStart->setGeometry(QRect(110, 30, 151, 21));
        sizePolicy1.setHeightForWidth(cmbChannelStart->sizePolicy().hasHeightForWidth());
        cmbChannelStart->setSizePolicy(sizePolicy1);
        edtClockRatePerChan = new QLineEdit(grpAISetting);
        edtClockRatePerChan->setObjectName(QString::fromUtf8("edtClockRatePerChan"));
        edtClockRatePerChan->setGeometry(QRect(110, 150, 131, 21));
        edtClockRatePerChan->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblValueRange = new QLabel(grpAISetting);
        lblValueRange->setObjectName(QString::fromUtf8("lblValueRange"));
        lblValueRange->setGeometry(QRect(20, 110, 91, 22));
        sizePolicy.setHeightForWidth(lblValueRange->sizePolicy().hasHeightForWidth());
        lblValueRange->setSizePolicy(sizePolicy);
        lblValueRange->setMinimumSize(QSize(91, 22));
        lblValueRange->setMaximumSize(QSize(91, 22));
        lblClockRate = new QLabel(grpAISetting);
        lblClockRate->setObjectName(QString::fromUtf8("lblClockRate"));
        lblClockRate->setGeometry(QRect(20, 150, 91, 22));
        sizePolicy.setHeightForWidth(lblClockRate->sizePolicy().hasHeightForWidth());
        lblClockRate->setSizePolicy(sizePolicy);
        lblClockRate->setMinimumSize(QSize(91, 22));
        lblClockRate->setMaximumSize(QSize(91, 22));
        lblChannelStart = new QLabel(grpAISetting);
        lblChannelStart->setObjectName(QString::fromUtf8("lblChannelStart"));
        lblChannelStart->setGeometry(QRect(20, 30, 91, 22));
        lblChannelStart->setMinimumSize(QSize(91, 22));
        lblChannelStart->setMaximumSize(QSize(91, 22));
        edtSectionLength = new QLineEdit(grpAISetting);
        edtSectionLength->setObjectName(QString::fromUtf8("edtSectionLength"));
        edtSectionLength->setGeometry(QRect(110, 190, 141, 21));
        edtSectionLength->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblSectionLength = new QLabel(grpAISetting);
        lblSectionLength->setObjectName(QString::fromUtf8("lblSectionLength"));
        lblSectionLength->setGeometry(QRect(20, 190, 91, 22));
        sizePolicy.setHeightForWidth(lblSectionLength->sizePolicy().hasHeightForWidth());
        lblSectionLength->setSizePolicy(sizePolicy);
        lblSectionLength->setMinimumSize(QSize(91, 22));
        lblSectionLength->setMaximumSize(QSize(91, 22));
        edtCycles = new QLineEdit(grpAISetting);
        edtCycles->setObjectName(QString::fromUtf8("edtCycles"));
        edtCycles->setGeometry(QRect(110, 230, 141, 21));
        edtCycles->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblCycles = new QLabel(grpAISetting);
        lblCycles->setObjectName(QString::fromUtf8("lblCycles"));
        lblCycles->setGeometry(QRect(20, 230, 91, 22));
        sizePolicy.setHeightForWidth(lblCycles->sizePolicy().hasHeightForWidth());
        lblCycles->setSizePolicy(sizePolicy);
        lblCycles->setMinimumSize(QSize(91, 22));
        lblCycles->setMaximumSize(QSize(91, 22));
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(60, 10, 171, 21));
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
#if QT_CONFIG(shortcut)
        lblHostname->setBuddy(cmbDevice);
        lblTriggerEdge->setBuddy(cmbChannelCount);
        lblTriggerDelayCount->setBuddy(cmbValueRange);
        lblTriggerLevelUnit->setBuddy(cmbValueRange);
        lblTriggerLevel->setBuddy(cmbValueRange);
        lblTriggerSource->setBuddy(cmbChannelStart);
        lblDevice->setBuddy(cmbDevice);
        lblTriggerEdge_2->setBuddy(cmbChannelCount);
        lblTriggerDelayCount_2->setBuddy(cmbValueRange);
        lblTriggerLevelUnit_2->setBuddy(cmbValueRange);
        lblTriggerLevel_2->setBuddy(cmbValueRange);
        lblTriggerSource_2->setBuddy(cmbChannelStart);
        lblProfileName->setBuddy(cmbDevice);
        lblChannelCount->setBuddy(cmbChannelCount);
        lblRateUnit->setBuddy(cmbValueRange);
        lblValueRange->setBuddy(cmbValueRange);
        lblClockRate->setBuddy(cmbValueRange);
        lblChannelStart->setBuddy(cmbChannelStart);
        lblSectionLength->setBuddy(cmbValueRange);
        lblCycles->setBuddy(cmbValueRange);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(cmbDevice, cmbChannelStart);
        QWidget::setTabOrder(cmbChannelStart, cmbChannelCount);
        QWidget::setTabOrder(cmbChannelCount, cmbValueRange);
        QWidget::setTabOrder(cmbValueRange, edtClockRatePerChan);
        QWidget::setTabOrder(edtClockRatePerChan, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(ConfigureDialog);

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "Streaming AI with Retrigger - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        grpTriggerSetting->setTitle(QCoreApplication::translate("ConfigureDialog", "Trigger settings", nullptr));
        lblTriggerEdge->setText(QCoreApplication::translate("ConfigureDialog", "Edge:", nullptr));
        lblTriggerDelayCount->setText(QCoreApplication::translate("ConfigureDialog", "Delay count:", nullptr));
        lblTriggerLevelUnit->setText(QCoreApplication::translate("ConfigureDialog", "V", nullptr));
        txtTriggerLevel->setText(QCoreApplication::translate("ConfigureDialog", "3", nullptr));
        lblTriggerLevel->setText(QCoreApplication::translate("ConfigureDialog", "Trigger level:", nullptr));
        txtDelayCount->setText(QCoreApplication::translate("ConfigureDialog", "500", nullptr));
        lblTriggerSource->setText(QCoreApplication::translate("ConfigureDialog", "Source:", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        txtProfilePath->setText(QString());
        grpTriggerSetting_2->setTitle(QCoreApplication::translate("ConfigureDialog", "Trigger 1 settings", nullptr));
        lblTriggerEdge_2->setText(QCoreApplication::translate("ConfigureDialog", "Edge:", nullptr));
        lblTriggerDelayCount_2->setText(QCoreApplication::translate("ConfigureDialog", "Delay count:", nullptr));
        lblTriggerLevelUnit_2->setText(QCoreApplication::translate("ConfigureDialog", "V", nullptr));
        txtTriggerLevel_2->setText(QCoreApplication::translate("ConfigureDialog", "3", nullptr));
        lblTriggerLevel_2->setText(QCoreApplication::translate("ConfigureDialog", "Trigger level:", nullptr));
        txtDelayCount_2->setText(QCoreApplication::translate("ConfigureDialog", "500", nullptr));
        lblTriggerSource_2->setText(QCoreApplication::translate("ConfigureDialog", "Source:", nullptr));
        lblProfileName->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
        grpAISetting->setTitle(QCoreApplication::translate("ConfigureDialog", "Streaming AI settings", nullptr));
        lblChannelCount->setText(QCoreApplication::translate("ConfigureDialog", "Channel count:", nullptr));
        lblRateUnit->setText(QCoreApplication::translate("ConfigureDialog", "Hz", nullptr));
        edtClockRatePerChan->setText(QCoreApplication::translate("ConfigureDialog", "10000", nullptr));
        lblValueRange->setText(QCoreApplication::translate("ConfigureDialog", "Value range:", nullptr));
        lblClockRate->setText(QCoreApplication::translate("ConfigureDialog", "Clock rate:", nullptr));
        lblChannelStart->setText(QCoreApplication::translate("ConfigureDialog", "Channel start:", nullptr));
        edtSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "10240", nullptr));
        lblSectionLength->setText(QCoreApplication::translate("ConfigureDialog", "Section Length:", nullptr));
        edtCycles->setText(QCoreApplication::translate("ConfigureDialog", "2", nullptr));
        lblCycles->setText(QCoreApplication::translate("ConfigureDialog", "Cycles:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
