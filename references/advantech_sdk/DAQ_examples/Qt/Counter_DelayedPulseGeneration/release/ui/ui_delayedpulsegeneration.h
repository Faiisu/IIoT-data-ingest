/********************************************************************************
** Form generated from reading UI file 'delayedpulsegeneration.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELAYEDPULSEGENERATION_H
#define UI_DELAYEDPULSEGENERATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DelayedPulseGenerationClass
{
public:
    QFrame *bkgrndImage;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *clockCountEditor;
    QLabel *label_shotCount;
    QLineEdit *shotCountEditor;
    QLabel *ExecutionStatus;
    QPushButton *btnConfig;
    QPushButton *btnStart;
    QPushButton *btnStop;

    void setupUi(QDialog *DelayedPulseGenerationClass)
    {
        if (DelayedPulseGenerationClass->objectName().isEmpty())
            DelayedPulseGenerationClass->setObjectName(QString::fromUtf8("DelayedPulseGenerationClass"));
        DelayedPulseGenerationClass->resize(337, 222);
        DelayedPulseGenerationClass->setMinimumSize(QSize(337, 222));
        DelayedPulseGenerationClass->setMaximumSize(QSize(337, 222));
        bkgrndImage = new QFrame(DelayedPulseGenerationClass);
        bkgrndImage->setObjectName(QString::fromUtf8("bkgrndImage"));
        bkgrndImage->setGeometry(QRect(130, -22, 221, 111));
        bkgrndImage->setFrameShape(QFrame::StyledPanel);
        bkgrndImage->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(DelayedPulseGenerationClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(17, 30, 301, 151));
        groupBox->setAutoFillBackground(true);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 67, 83, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        clockCountEditor = new QLineEdit(groupBox);
        clockCountEditor->setObjectName(QString::fromUtf8("clockCountEditor"));
        clockCountEditor->setGeometry(QRect(98, 66, 161, 29));
        sizePolicy.setHeightForWidth(clockCountEditor->sizePolicy().hasHeightForWidth());
        clockCountEditor->setSizePolicy(sizePolicy);
        clockCountEditor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_shotCount = new QLabel(groupBox);
        label_shotCount->setObjectName(QString::fromUtf8("label_shotCount"));
        label_shotCount->setGeometry(QRect(10, 107, 71, 31));
        sizePolicy.setHeightForWidth(label_shotCount->sizePolicy().hasHeightForWidth());
        label_shotCount->setSizePolicy(sizePolicy);
        shotCountEditor = new QLineEdit(groupBox);
        shotCountEditor->setObjectName(QString::fromUtf8("shotCountEditor"));
        shotCountEditor->setGeometry(QRect(98, 108, 161, 29));
        sizePolicy.setHeightForWidth(shotCountEditor->sizePolicy().hasHeightForWidth());
        shotCountEditor->setSizePolicy(sizePolicy);
        shotCountEditor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        shotCountEditor->setReadOnly(true);
        ExecutionStatus = new QLabel(groupBox);
        ExecutionStatus->setObjectName(QString::fromUtf8("ExecutionStatus"));
        ExecutionStatus->setGeometry(QRect(10, 20, 251, 25));
        sizePolicy.setHeightForWidth(ExecutionStatus->sizePolicy().hasHeightForWidth());
        ExecutionStatus->setSizePolicy(sizePolicy);
        btnConfig = new QPushButton(DelayedPulseGenerationClass);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        btnConfig->setGeometry(QRect(31, 189, 88, 25));
        btnStart = new QPushButton(DelayedPulseGenerationClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(140, 190, 75, 25));
        btnStop = new QPushButton(DelayedPulseGenerationClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(240, 190, 75, 25));

        retranslateUi(DelayedPulseGenerationClass);

        QMetaObject::connectSlotsByName(DelayedPulseGenerationClass);
    } // setupUi

    void retranslateUi(QDialog *DelayedPulseGenerationClass)
    {
        DelayedPulseGenerationClass->setWindowTitle(QCoreApplication::translate("DelayedPulseGenerationClass", "Delayed Pulse Generation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DelayedPulseGenerationClass", "Execution status", nullptr));
        label->setText(QCoreApplication::translate("DelayedPulseGenerationClass", "Delay count:", nullptr));
        label_shotCount->setText(QCoreApplication::translate("DelayedPulseGenerationClass", "Delayed Pulse \n"
"count:", nullptr));
        ExecutionStatus->setText(QString());
        btnConfig->setText(QCoreApplication::translate("DelayedPulseGenerationClass", "Configure", nullptr));
        btnStart->setText(QCoreApplication::translate("DelayedPulseGenerationClass", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("DelayedPulseGenerationClass", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DelayedPulseGenerationClass: public Ui_DelayedPulseGenerationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELAYEDPULSEGENERATION_H
