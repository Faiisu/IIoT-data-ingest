/********************************************************************************
** Form generated from reading UI file 'calibrationitem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONITEM_H
#define UI_CALIBRATIONITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationItemClass
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_header;
    QLabel *lbl_sln_desc;
    QFrame *line;
    QLabel *lbl_sln_instrc;
    QTextEdit *textEdit_sln_instrction;
    QHBoxLayout *horizontalLayout_section;
    QLabel *lbl_sect_name;
    QComboBox *cmb_sect_desc;
    QTextEdit *textEdit_sect_instrc;
    QGridLayout *gridLayout;
    QLabel *lbl_4;
    QLineEdit *lineEdit_read_value;
    QTextEdit *textEdit_subj_instrc;
    QLabel *lbl_subj_target;
    QLabel *lbl_1;
    QSpinBox *spb_adj_code;
    QLabel *lbl_5;
    QLabel *lbl_3;
    QComboBox *cmb_subj_desc;
    QLabel *lbl_2;
    QTableWidget *table_list_result;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_config;
    QLabel *label_blank;
    QPushButton *btn_save;
    QPushButton *btn_stop;
    QPushButton *btn_start;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CalibrationItemClass)
    {
        if (CalibrationItemClass->objectName().isEmpty())
            CalibrationItemClass->setObjectName(QString::fromUtf8("CalibrationItemClass"));
        CalibrationItemClass->setEnabled(true);
        CalibrationItemClass->resize(442, 536);
        verticalLayoutWidget = new QWidget(CalibrationItemClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 0, 421, 517));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_header = new QHBoxLayout();
        horizontalLayout_header->setSpacing(6);
        horizontalLayout_header->setObjectName(QString::fromUtf8("horizontalLayout_header"));
        lbl_sln_desc = new QLabel(verticalLayoutWidget);
        lbl_sln_desc->setObjectName(QString::fromUtf8("lbl_sln_desc"));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        lbl_sln_desc->setFont(font);

        horizontalLayout_header->addWidget(lbl_sln_desc);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_header->addWidget(line);

        horizontalLayout_header->setStretch(0, 1);
        horizontalLayout_header->setStretch(1, 4);

        verticalLayout->addLayout(horizontalLayout_header);

        lbl_sln_instrc = new QLabel(verticalLayoutWidget);
        lbl_sln_instrc->setObjectName(QString::fromUtf8("lbl_sln_instrc"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbl_sln_instrc->sizePolicy().hasHeightForWidth());
        lbl_sln_instrc->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(lbl_sln_instrc);

        textEdit_sln_instrction = new QTextEdit(verticalLayoutWidget);
        textEdit_sln_instrction->setObjectName(QString::fromUtf8("textEdit_sln_instrction"));
        textEdit_sln_instrction->setReadOnly(true);

        verticalLayout->addWidget(textEdit_sln_instrction);

        horizontalLayout_section = new QHBoxLayout();
        horizontalLayout_section->setSpacing(6);
        horizontalLayout_section->setObjectName(QString::fromUtf8("horizontalLayout_section"));
        lbl_sect_name = new QLabel(verticalLayoutWidget);
        lbl_sect_name->setObjectName(QString::fromUtf8("lbl_sect_name"));
        sizePolicy.setHeightForWidth(lbl_sect_name->sizePolicy().hasHeightForWidth());
        lbl_sect_name->setSizePolicy(sizePolicy);

        horizontalLayout_section->addWidget(lbl_sect_name);

        cmb_sect_desc = new QComboBox(verticalLayoutWidget);
        cmb_sect_desc->setObjectName(QString::fromUtf8("cmb_sect_desc"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmb_sect_desc->sizePolicy().hasHeightForWidth());
        cmb_sect_desc->setSizePolicy(sizePolicy1);

        horizontalLayout_section->addWidget(cmb_sect_desc);

        horizontalLayout_section->setStretch(0, 1);
        horizontalLayout_section->setStretch(1, 4);

        verticalLayout->addLayout(horizontalLayout_section);

        textEdit_sect_instrc = new QTextEdit(verticalLayoutWidget);
        textEdit_sect_instrc->setObjectName(QString::fromUtf8("textEdit_sect_instrc"));
        textEdit_sect_instrc->setReadOnly(true);

        verticalLayout->addWidget(textEdit_sect_instrc);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 0);
        lbl_4 = new QLabel(verticalLayoutWidget);
        lbl_4->setObjectName(QString::fromUtf8("lbl_4"));

        gridLayout->addWidget(lbl_4, 3, 0, 1, 1);

        lineEdit_read_value = new QLineEdit(verticalLayoutWidget);
        lineEdit_read_value->setObjectName(QString::fromUtf8("lineEdit_read_value"));

        gridLayout->addWidget(lineEdit_read_value, 3, 2, 1, 1);

        textEdit_subj_instrc = new QTextEdit(verticalLayoutWidget);
        textEdit_subj_instrc->setObjectName(QString::fromUtf8("textEdit_subj_instrc"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit_subj_instrc->sizePolicy().hasHeightForWidth());
        textEdit_subj_instrc->setSizePolicy(sizePolicy2);
        textEdit_subj_instrc->setReadOnly(true);

        gridLayout->addWidget(textEdit_subj_instrc, 1, 2, 1, 1);

        lbl_subj_target = new QLabel(verticalLayoutWidget);
        lbl_subj_target->setObjectName(QString::fromUtf8("lbl_subj_target"));

        gridLayout->addWidget(lbl_subj_target, 2, 2, 1, 1);

        lbl_1 = new QLabel(verticalLayoutWidget);
        lbl_1->setObjectName(QString::fromUtf8("lbl_1"));

        gridLayout->addWidget(lbl_1, 0, 0, 1, 1);

        spb_adj_code = new QSpinBox(verticalLayoutWidget);
        spb_adj_code->setObjectName(QString::fromUtf8("spb_adj_code"));
        spb_adj_code->setKeyboardTracking(true);

        gridLayout->addWidget(spb_adj_code, 4, 2, 1, 1);

        lbl_5 = new QLabel(verticalLayoutWidget);
        lbl_5->setObjectName(QString::fromUtf8("lbl_5"));

        gridLayout->addWidget(lbl_5, 4, 0, 1, 1);

        lbl_3 = new QLabel(verticalLayoutWidget);
        lbl_3->setObjectName(QString::fromUtf8("lbl_3"));

        gridLayout->addWidget(lbl_3, 2, 0, 1, 1);

        cmb_subj_desc = new QComboBox(verticalLayoutWidget);
        cmb_subj_desc->setObjectName(QString::fromUtf8("cmb_subj_desc"));

        gridLayout->addWidget(cmb_subj_desc, 0, 2, 1, 1);

        lbl_2 = new QLabel(verticalLayoutWidget);
        lbl_2->setObjectName(QString::fromUtf8("lbl_2"));

        gridLayout->addWidget(lbl_2, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);

        verticalLayout->addLayout(gridLayout);

        table_list_result = new QTableWidget(verticalLayoutWidget);
        table_list_result->setObjectName(QString::fromUtf8("table_list_result"));

        verticalLayout->addWidget(table_list_result);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_config = new QPushButton(verticalLayoutWidget);
        btn_config->setObjectName(QString::fromUtf8("btn_config"));

        horizontalLayout->addWidget(btn_config);

        label_blank = new QLabel(verticalLayoutWidget);
        label_blank->setObjectName(QString::fromUtf8("label_blank"));

        horizontalLayout->addWidget(label_blank);

        btn_save = new QPushButton(verticalLayoutWidget);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));

        horizontalLayout->addWidget(btn_save);

        btn_stop = new QPushButton(verticalLayoutWidget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));

        horizontalLayout->addWidget(btn_stop);

        btn_start = new QPushButton(verticalLayoutWidget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        horizontalLayout->addWidget(btn_start);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 1);
        verticalLayout->setStretch(6, 6);
        verticalLayout->setStretch(7, 1);
        verticalLayout->setStretch(8, 1);
        verticalLayout->setStretch(9, 1);

        retranslateUi(CalibrationItemClass);

        QMetaObject::connectSlotsByName(CalibrationItemClass);
    } // setupUi

    void retranslateUi(QDialog *CalibrationItemClass)
    {
        CalibrationItemClass->setWindowTitle(QCoreApplication::translate("CalibrationItemClass", "Event Counter", nullptr));
        lbl_sln_desc->setText(QCoreApplication::translate("CalibrationItemClass", "Solution Description", nullptr));
        lbl_sln_instrc->setText(QCoreApplication::translate("CalibrationItemClass", "Solution Instruction", nullptr));
        lbl_sect_name->setText(QCoreApplication::translate("CalibrationItemClass", " Section:", nullptr));
        lbl_4->setText(QCoreApplication::translate("CalibrationItemClass", "Read Value:", nullptr));
        lbl_subj_target->setText(QCoreApplication::translate("CalibrationItemClass", "-------", nullptr));
        lbl_1->setText(QCoreApplication::translate("CalibrationItemClass", "Subject:", nullptr));
        lbl_5->setText(QCoreApplication::translate("CalibrationItemClass", "Adjust Code", nullptr));
        lbl_3->setText(QCoreApplication::translate("CalibrationItemClass", "Target:", nullptr));
        lbl_2->setText(QCoreApplication::translate("CalibrationItemClass", "Instruction:", nullptr));
        btn_config->setText(QCoreApplication::translate("CalibrationItemClass", "Config", nullptr));
        label_blank->setText(QString());
        btn_save->setText(QCoreApplication::translate("CalibrationItemClass", "Save", nullptr));
        btn_stop->setText(QCoreApplication::translate("CalibrationItemClass", "Stop", nullptr));
        btn_start->setText(QCoreApplication::translate("CalibrationItemClass", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalibrationItemClass: public Ui_CalibrationItemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONITEM_H
