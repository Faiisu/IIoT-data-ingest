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
    QGroupBox *groupBox;
    QComboBox *cmbChannelStart;
    QLabel *lblValueRange;
    QLabel *lblChannelCount;
    QLabel *lblChannelStart;
    QComboBox *cmbValueRange;
    QComboBox *cmbChannelCount;
    QLabel *label_3;
    QLineEdit *txtClockRate;
    QLabel *labelclockRate;
    QGroupBox *groupBox_2;
    QLineEdit *txtPointCount;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *cmbHostName;
    QLabel *lblHostname;
    QPushButton *btnLogin;
    QFrame *frame;
    QPushButton *btnBrowse;
    QLineEdit *txtProfilePath;
    QLabel *lblDevice;
    QComboBox *cmbDevice;
    QLabel *lblProfilePath;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->resize(540, 260);
        ConfigureDialog->setMinimumSize(QSize(540, 260));
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(283, 220, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(380, 220, 75, 23));
        btnCancel->setAutoDefault(false);
        groupBox = new QGroupBox(ConfigureDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(12, 100, 243, 151));
        cmbChannelStart = new QComboBox(groupBox);
        cmbChannelStart->setObjectName(QString::fromUtf8("cmbChannelStart"));
        cmbChannelStart->setGeometry(QRect(98, 20, 131, 21));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbChannelStart->sizePolicy().hasHeightForWidth());
        cmbChannelStart->setSizePolicy(sizePolicy);
        lblValueRange = new QLabel(groupBox);
        lblValueRange->setObjectName(QString::fromUtf8("lblValueRange"));
        lblValueRange->setGeometry(QRect(8, 84, 91, 22));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblValueRange->sizePolicy().hasHeightForWidth());
        lblValueRange->setSizePolicy(sizePolicy1);
        lblValueRange->setMinimumSize(QSize(91, 22));
        lblValueRange->setMaximumSize(QSize(91, 22));
        lblChannelCount = new QLabel(groupBox);
        lblChannelCount->setObjectName(QString::fromUtf8("lblChannelCount"));
        lblChannelCount->setGeometry(QRect(8, 52, 91, 22));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblChannelCount->sizePolicy().hasHeightForWidth());
        lblChannelCount->setSizePolicy(sizePolicy2);
        lblChannelCount->setMinimumSize(QSize(91, 22));
        lblChannelCount->setMaximumSize(QSize(91, 22));
        lblChannelStart = new QLabel(groupBox);
        lblChannelStart->setObjectName(QString::fromUtf8("lblChannelStart"));
        lblChannelStart->setGeometry(QRect(8, 20, 91, 22));
        lblChannelStart->setMinimumSize(QSize(91, 22));
        lblChannelStart->setMaximumSize(QSize(91, 22));
        cmbValueRange = new QComboBox(groupBox);
        cmbValueRange->setObjectName(QString::fromUtf8("cmbValueRange"));
        cmbValueRange->setGeometry(QRect(99, 84, 131, 21));
        sizePolicy.setHeightForWidth(cmbValueRange->sizePolicy().hasHeightForWidth());
        cmbValueRange->setSizePolicy(sizePolicy);
        cmbChannelCount = new QComboBox(groupBox);
        cmbChannelCount->setObjectName(QString::fromUtf8("cmbChannelCount"));
        cmbChannelCount->setGeometry(QRect(99, 52, 131, 21));
        sizePolicy.setHeightForWidth(cmbChannelCount->sizePolicy().hasHeightForWidth());
        cmbChannelCount->setSizePolicy(sizePolicy);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(217, 121, 16, 16));
        label_3->setMinimumSize(QSize(16, 16));
        txtClockRate = new QLineEdit(groupBox);
        txtClockRate->setObjectName(QString::fromUtf8("txtClockRate"));
        txtClockRate->setGeometry(QRect(104, 116, 108, 25));
        txtClockRate->setMinimumSize(QSize(108, 25));
        txtClockRate->setCursor(QCursor(Qt::IBeamCursor));
        labelclockRate = new QLabel(groupBox);
        labelclockRate->setObjectName(QString::fromUtf8("labelclockRate"));
        labelclockRate->setGeometry(QRect(9, 115, 91, 22));
        sizePolicy1.setHeightForWidth(labelclockRate->sizePolicy().hasHeightForWidth());
        labelclockRate->setSizePolicy(sizePolicy1);
        labelclockRate->setMinimumSize(QSize(91, 22));
        labelclockRate->setMaximumSize(QSize(91, 22));
        groupBox_2 = new QGroupBox(ConfigureDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(263, 100, 261, 111));
        txtPointCount = new QLineEdit(groupBox_2);
        txtPointCount->setObjectName(QString::fromUtf8("txtPointCount"));
        txtPointCount->setGeometry(QRect(10, 42, 113, 25));
        txtPointCount->setMinimumSize(QSize(113, 25));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(8, 73, 251, 31));
        label_2->setMinimumSize(QSize(161, 31));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 14, 161, 20));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(80, 19, 351, 22));
        cmbHostName->setEditable(true);
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(9, 21, 61, 20));
        sizePolicy1.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy1);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(460, 20, 51, 21));
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 50, 521, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(450, 10, 51, 23));
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(260, 10, 161, 20));
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(7, 10, 41, 20));
        sizePolicy1.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy1);
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(50, 10, 151, 21));
        sizePolicy.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        lblProfilePath = new QLabel(frame);
        lblProfilePath->setObjectName(QString::fromUtf8("lblProfilePath"));
        lblProfilePath->setGeometry(QRect(210, 10, 51, 20));
        sizePolicy1.setHeightForWidth(lblProfilePath->sizePolicy().hasHeightForWidth());
        lblProfilePath->setSizePolicy(sizePolicy1);
#if QT_CONFIG(shortcut)
        lblValueRange->setBuddy(cmbValueRange);
        lblChannelCount->setBuddy(cmbChannelCount);
        lblChannelStart->setBuddy(cmbChannelStart);
        labelclockRate->setBuddy(cmbValueRange);
        lblHostname->setBuddy(cmbDevice);
        lblDevice->setBuddy(cmbDevice);
        lblProfilePath->setBuddy(cmbDevice);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(cmbDevice, cmbChannelStart);
        QWidget::setTabOrder(cmbChannelStart, cmbChannelCount);
        QWidget::setTabOrder(cmbChannelCount, cmbValueRange);
        QWidget::setTabOrder(cmbValueRange, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(ConfigureDialog);

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "Asynchronous One Waveform AO - Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConfigureDialog", "Buffered AO settings", nullptr));
        lblValueRange->setText(QCoreApplication::translate("ConfigureDialog", "Value range:", nullptr));
        lblChannelCount->setText(QCoreApplication::translate("ConfigureDialog", "Channel count:", nullptr));
        lblChannelStart->setText(QCoreApplication::translate("ConfigureDialog", "Channel start:", nullptr));
        label_3->setText(QCoreApplication::translate("ConfigureDialog", "Hz", nullptr));
        txtClockRate->setText(QCoreApplication::translate("ConfigureDialog", "1000", nullptr));
        labelclockRate->setText(QCoreApplication::translate("ConfigureDialog", "Clock Rate:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ConfigureDialog", "Output wave settings", nullptr));
        txtPointCount->setText(QCoreApplication::translate("ConfigureDialog", "400", nullptr));
        label_2->setText(QCoreApplication::translate("ConfigureDialog", "The data number of AO to form a waveform", nullptr));
        label_4->setText(QCoreApplication::translate("ConfigureDialog", "Points for each waveform:", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        lblProfilePath->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
