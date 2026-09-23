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
    QPushButton *btnLogin;
    QLabel *lblHostname;
    QFrame *frame;
    QLabel *lblDevice;
    QGroupBox *groupBox;
    QComboBox *cmbChannelStart;
    QLabel *lblValueRange;
    QLabel *lblChannelCount;
    QLabel *lblChannelStart;
    QComboBox *cmbValueRange;
    QComboBox *cmbChannelCount;
    QPushButton *btnBrowse;
    QComboBox *cmbDevice;
    QLabel *lblDevice_2;
    QLineEdit *txtProfilePath;
    QComboBox *cmbHostName;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->resize(370, 290);
        ConfigureDialog->setMinimumSize(QSize(370, 290));
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(143, 256, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(240, 256, 75, 23));
        btnCancel->setAutoDefault(false);
        btnLogin = new QPushButton(ConfigureDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(280, 14, 51, 21));
        lblHostname = new QLabel(ConfigureDialog);
        lblHostname->setObjectName(QString::fromUtf8("lblHostname"));
        lblHostname->setGeometry(QRect(10, 14, 61, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblHostname->sizePolicy().hasHeightForWidth());
        lblHostname->setSizePolicy(sizePolicy);
        frame = new QFrame(ConfigureDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 40, 321, 211));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lblDevice = new QLabel(frame);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setGeometry(QRect(10, 10, 51, 16));
        sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(3, 80, 311, 121));
        cmbChannelStart = new QComboBox(groupBox);
        cmbChannelStart->setObjectName(QString::fromUtf8("cmbChannelStart"));
        cmbChannelStart->setGeometry(QRect(105, 20, 201, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbChannelStart->sizePolicy().hasHeightForWidth());
        cmbChannelStart->setSizePolicy(sizePolicy1);
        lblValueRange = new QLabel(groupBox);
        lblValueRange->setObjectName(QString::fromUtf8("lblValueRange"));
        lblValueRange->setGeometry(QRect(14, 84, 91, 22));
        sizePolicy.setHeightForWidth(lblValueRange->sizePolicy().hasHeightForWidth());
        lblValueRange->setSizePolicy(sizePolicy);
        lblValueRange->setMinimumSize(QSize(91, 22));
        lblValueRange->setMaximumSize(QSize(91, 22));
        lblChannelCount = new QLabel(groupBox);
        lblChannelCount->setObjectName(QString::fromUtf8("lblChannelCount"));
        lblChannelCount->setGeometry(QRect(14, 52, 91, 22));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblChannelCount->sizePolicy().hasHeightForWidth());
        lblChannelCount->setSizePolicy(sizePolicy2);
        lblChannelCount->setMinimumSize(QSize(91, 22));
        lblChannelCount->setMaximumSize(QSize(91, 22));
        lblChannelStart = new QLabel(groupBox);
        lblChannelStart->setObjectName(QString::fromUtf8("lblChannelStart"));
        lblChannelStart->setGeometry(QRect(14, 20, 91, 22));
        lblChannelStart->setMinimumSize(QSize(91, 22));
        lblChannelStart->setMaximumSize(QSize(91, 22));
        cmbValueRange = new QComboBox(groupBox);
        cmbValueRange->setObjectName(QString::fromUtf8("cmbValueRange"));
        cmbValueRange->setGeometry(QRect(105, 84, 201, 20));
        sizePolicy1.setHeightForWidth(cmbValueRange->sizePolicy().hasHeightForWidth());
        cmbValueRange->setSizePolicy(sizePolicy1);
        cmbChannelCount = new QComboBox(groupBox);
        cmbChannelCount->setObjectName(QString::fromUtf8("cmbChannelCount"));
        cmbChannelCount->setGeometry(QRect(105, 52, 201, 20));
        sizePolicy1.setHeightForWidth(cmbChannelCount->sizePolicy().hasHeightForWidth());
        cmbChannelCount->setSizePolicy(sizePolicy1);
        btnBrowse = new QPushButton(frame);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(260, 50, 51, 21));
        cmbDevice = new QComboBox(frame);
        cmbDevice->setObjectName(QString::fromUtf8("cmbDevice"));
        cmbDevice->setGeometry(QRect(70, 10, 241, 20));
        sizePolicy1.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy1);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        lblDevice_2 = new QLabel(frame);
        lblDevice_2->setObjectName(QString::fromUtf8("lblDevice_2"));
        lblDevice_2->setGeometry(QRect(10, 50, 41, 20));
        sizePolicy.setHeightForWidth(lblDevice_2->sizePolicy().hasHeightForWidth());
        lblDevice_2->setSizePolicy(sizePolicy);
        txtProfilePath = new QLineEdit(frame);
        txtProfilePath->setObjectName(QString::fromUtf8("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(70, 50, 181, 20));
        cmbHostName = new QComboBox(ConfigureDialog);
        cmbHostName->setObjectName(QString::fromUtf8("cmbHostName"));
        cmbHostName->setGeometry(QRect(90, 12, 181, 22));
        cmbHostName->setEditable(true);
#if QT_CONFIG(shortcut)
        lblHostname->setBuddy(cmbDevice);
        lblDevice->setBuddy(cmbDevice);
        lblValueRange->setBuddy(cmbValueRange);
        lblChannelCount->setBuddy(cmbChannelCount);
        lblChannelStart->setBuddy(cmbChannelStart);
        lblDevice_2->setBuddy(cmbDevice);
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
        ConfigureDialog->setWindowTitle(QCoreApplication::translate("ConfigureDialog", "Instant AI-Configuration", nullptr));
        btnOK->setText(QCoreApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("ConfigureDialog", "Cancel", nullptr));
        btnLogin->setText(QCoreApplication::translate("ConfigureDialog", "Login", nullptr));
        lblHostname->setText(QCoreApplication::translate("ConfigureDialog", "Host Name:", nullptr));
        lblDevice->setText(QCoreApplication::translate("ConfigureDialog", "Device:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConfigureDialog", "Instant AI settings", nullptr));
        lblValueRange->setText(QCoreApplication::translate("ConfigureDialog", "Value range:", nullptr));
        lblChannelCount->setText(QCoreApplication::translate("ConfigureDialog", "Channel count:", nullptr));
        lblChannelStart->setText(QCoreApplication::translate("ConfigureDialog", "Channel start:", nullptr));
        btnBrowse->setText(QCoreApplication::translate("ConfigureDialog", "Browse", nullptr));
        lblDevice_2->setText(QCoreApplication::translate("ConfigureDialog", "Profile:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
