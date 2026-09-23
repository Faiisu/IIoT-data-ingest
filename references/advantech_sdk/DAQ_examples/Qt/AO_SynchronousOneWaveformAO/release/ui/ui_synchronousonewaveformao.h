/********************************************************************************
** Form generated from reading UI file 'synchronousonewaveformao.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCHRONOUSONEWAVEFORMAO_H
#define UI_SYNCHRONOUSONEWAVEFORMAO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SynchronousOneWaveformAOClass
{
public:
    QFrame *background;
    QPushButton *BtnSineA;
    QPushButton *BtnSquareA;
    QPushButton *BtnTriangleA;
    QPushButton *BtnSineB;
    QPushButton *BtnTriangleB;
    QPushButton *BtnSquareB;
    QLineEdit *txtboxHiLevelA;
    QLineEdit *txtboxLoLevelA;
    QLineEdit *txtboxLoLevelB;
    QLineEdit *txtboxHiLevelB;
    QLabel *chLabelA;
    QLabel *chLabelB;
    QPushButton *btnConfigure;
    QPushButton *btnStart;

    void setupUi(QDialog *SynchronousOneWaveformAOClass)
    {
        if (SynchronousOneWaveformAOClass->objectName().isEmpty())
            SynchronousOneWaveformAOClass->setObjectName(QString::fromUtf8("SynchronousOneWaveformAOClass"));
        SynchronousOneWaveformAOClass->resize(339, 430);
        SynchronousOneWaveformAOClass->setMinimumSize(QSize(339, 430));
        SynchronousOneWaveformAOClass->setMaximumSize(QSize(339, 430));
        background = new QFrame(SynchronousOneWaveformAOClass);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(-4, -3, 340, 431));
        background->setMinimumSize(QSize(340, 431));
        background->setStyleSheet(QString::fromUtf8("QFrame#background{background-image:url(:/SynchronousOneWaveformAO/Resources/ao.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        BtnSineA = new QPushButton(background);
        BtnSineA->setObjectName(QString::fromUtf8("BtnSineA"));
        BtnSineA->setGeometry(QRect(79, 127, 51, 51));
        BtnSineA->setMinimumSize(QSize(51, 51));
        BtnSineA->setMaximumSize(QSize(51, 51));
        BtnSineA->setStyleSheet(QString::fromUtf8("background:url(:/SynchronousOneWaveformAO/Resources/sine.png)"));
        BtnSineA->setCheckable(true);
        BtnSineA->setFlat(true);
        BtnSquareA = new QPushButton(background);
        BtnSquareA->setObjectName(QString::fromUtf8("BtnSquareA"));
        BtnSquareA->setGeometry(QRect(218, 127, 51, 51));
        BtnSquareA->setMinimumSize(QSize(51, 51));
        BtnSquareA->setMaximumSize(QSize(51, 51));
        BtnSquareA->setStyleSheet(QString::fromUtf8("background:url(:/SynchronousOneWaveformAO/Resources/square.png)"));
        BtnSquareA->setCheckable(true);
        BtnSquareA->setFlat(true);
        BtnTriangleA = new QPushButton(background);
        BtnTriangleA->setObjectName(QString::fromUtf8("BtnTriangleA"));
        BtnTriangleA->setGeometry(QRect(148, 127, 51, 51));
        BtnTriangleA->setMinimumSize(QSize(51, 51));
        BtnTriangleA->setMaximumSize(QSize(51, 51));
        BtnTriangleA->setStyleSheet(QString::fromUtf8("background:url(:/SynchronousOneWaveformAO/Resources/triangle.png)"));
        BtnTriangleA->setCheckable(true);
        BtnTriangleA->setFlat(true);
        BtnSineB = new QPushButton(background);
        BtnSineB->setObjectName(QString::fromUtf8("BtnSineB"));
        BtnSineB->setGeometry(QRect(79, 310, 51, 51));
        BtnSineB->setMinimumSize(QSize(51, 51));
        BtnSineB->setMaximumSize(QSize(51, 51));
        BtnSineB->setStyleSheet(QString::fromUtf8("background:url(:/SynchronousOneWaveformAO/Resources/sine.png)"));
        BtnSineB->setCheckable(true);
        BtnSineB->setFlat(true);
        BtnTriangleB = new QPushButton(background);
        BtnTriangleB->setObjectName(QString::fromUtf8("BtnTriangleB"));
        BtnTriangleB->setGeometry(QRect(150, 310, 51, 51));
        BtnTriangleB->setMinimumSize(QSize(51, 51));
        BtnTriangleB->setMaximumSize(QSize(51, 51));
        BtnTriangleB->setStyleSheet(QString::fromUtf8("background:url(:/SynchronousOneWaveformAO/Resources/triangle.png)"));
        BtnTriangleB->setCheckable(true);
        BtnTriangleB->setFlat(true);
        BtnSquareB = new QPushButton(background);
        BtnSquareB->setObjectName(QString::fromUtf8("BtnSquareB"));
        BtnSquareB->setGeometry(QRect(218, 310, 51, 51));
        BtnSquareB->setMinimumSize(QSize(51, 51));
        BtnSquareB->setMaximumSize(QSize(51, 51));
        BtnSquareB->setStyleSheet(QString::fromUtf8("background:url(:/SynchronousOneWaveformAO/Resources/square.png)"));
        BtnSquareB->setCheckable(true);
        BtnSquareB->setFlat(true);
        txtboxHiLevelA = new QLineEdit(background);
        txtboxHiLevelA->setObjectName(QString::fromUtf8("txtboxHiLevelA"));
        txtboxHiLevelA->setGeometry(QRect(83, 91, 73, 20));
        txtboxHiLevelA->setMinimumSize(QSize(73, 20));
        txtboxHiLevelA->setMaximumSize(QSize(73, 20));
        txtboxLoLevelA = new QLineEdit(background);
        txtboxLoLevelA->setObjectName(QString::fromUtf8("txtboxLoLevelA"));
        txtboxLoLevelA->setGeometry(QRect(193, 90, 73, 20));
        txtboxLoLevelA->setMinimumSize(QSize(73, 20));
        txtboxLoLevelA->setMaximumSize(QSize(73, 20));
        txtboxLoLevelB = new QLineEdit(background);
        txtboxLoLevelB->setObjectName(QString::fromUtf8("txtboxLoLevelB"));
        txtboxLoLevelB->setGeometry(QRect(193, 275, 73, 20));
        txtboxLoLevelB->setMinimumSize(QSize(73, 20));
        txtboxLoLevelB->setMaximumSize(QSize(73, 20));
        txtboxHiLevelB = new QLineEdit(background);
        txtboxHiLevelB->setObjectName(QString::fromUtf8("txtboxHiLevelB"));
        txtboxHiLevelB->setGeometry(QRect(83, 276, 73, 20));
        txtboxHiLevelB->setMinimumSize(QSize(73, 20));
        txtboxHiLevelB->setMaximumSize(QSize(73, 20));
        chLabelA = new QLabel(background);
        chLabelA->setObjectName(QString::fromUtf8("chLabelA"));
        chLabelA->setGeometry(QRect(228, 33, 16, 16));
        chLabelA->setMinimumSize(QSize(16, 16));
        chLabelA->setMaximumSize(QSize(16, 16));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        chLabelA->setFont(font);
        chLabelA->setStyleSheet(QString::fromUtf8("color:rgb(255, 170, 0)"));
        chLabelA->setTextFormat(Qt::RichText);
        chLabelA->setAlignment(Qt::AlignCenter);
        chLabelB = new QLabel(background);
        chLabelB->setObjectName(QString::fromUtf8("chLabelB"));
        chLabelB->setGeometry(QRect(229, 218, 16, 16));
        chLabelB->setMinimumSize(QSize(16, 16));
        chLabelB->setMaximumSize(QSize(16, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        chLabelB->setFont(font1);
        chLabelB->setStyleSheet(QString::fromUtf8("color:rgb(255, 170, 0)"));
        chLabelB->setTextFormat(Qt::RichText);
        chLabelB->setAlignment(Qt::AlignCenter);
        btnConfigure = new QPushButton(background);
        btnConfigure->setObjectName(QString::fromUtf8("btnConfigure"));
        btnConfigure->setGeometry(QRect(125, 394, 75, 23));
        btnConfigure->setMinimumSize(QSize(75, 23));
        btnConfigure->setMaximumSize(QSize(75, 23));
        btnStart = new QPushButton(background);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(226, 394, 75, 23));
        btnStart->setMinimumSize(QSize(75, 23));
        btnStart->setMaximumSize(QSize(75, 23));

        retranslateUi(SynchronousOneWaveformAOClass);

        QMetaObject::connectSlotsByName(SynchronousOneWaveformAOClass);
    } // setupUi

    void retranslateUi(QDialog *SynchronousOneWaveformAOClass)
    {
        SynchronousOneWaveformAOClass->setWindowTitle(QCoreApplication::translate("SynchronousOneWaveformAOClass", "Synchronous One Waveform AO", nullptr));
        BtnSineA->setText(QString());
        BtnSquareA->setText(QString());
        BtnTriangleA->setText(QString());
        BtnSineB->setText(QString());
        BtnTriangleB->setText(QString());
        BtnSquareB->setText(QString());
        txtboxHiLevelA->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "5", nullptr));
        txtboxLoLevelA->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "-5", nullptr));
        txtboxLoLevelB->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "-5", nullptr));
        txtboxHiLevelB->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "5", nullptr));
        chLabelA->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "0", nullptr));
        chLabelB->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "1", nullptr));
        btnConfigure->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "Configure", nullptr));
        btnStart->setText(QCoreApplication::translate("SynchronousOneWaveformAOClass", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SynchronousOneWaveformAOClass: public Ui_SynchronousOneWaveformAOClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCHRONOUSONEWAVEFORMAO_H
