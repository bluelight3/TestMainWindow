/********************************************************************************
** Form generated from reading UI file 'myitemidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYITEMIDGET_H
#define UI_MYITEMIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyItemidget
{
public:
    QWidget *titleBarWidget;
    QPushButton *btn_close;
    QLabel *lbl_title;
    QWidget *centralWidget;
    QLabel *lbl_itemPicture;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_ok;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_cancel;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *lbl_itemName;
    QComboBox *comboBox_itemMyType;
    QLabel *lbl_itemMyType;
    QLineEdit *txt_itemName;
    QLabel *lbl_itemToggle;
    QLineEdit *txt_itemToggle;

    void setupUi(QWidget *MyItemidget)
    {
        if (MyItemidget->objectName().isEmpty())
            MyItemidget->setObjectName(QString::fromUtf8("MyItemidget"));
        MyItemidget->resize(505, 268);
        MyItemidget->setStyleSheet(QString::fromUtf8("#centralWidget {\n"
"    background: #CCC;\n"
"}\n"
"\n"
"#titleBarWidget {\n"
"    background: #888;\n"
"    min-height: 40px;\n"
"    max-height: 40px;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"}\n"
"\n"
"#titleBarWidget QPushButton {\n"
"    min-width: 20px;\n"
"    max-width: 20px;\n"
"    min-height: 20px;\n"
"    max-height: 20px;\n"
"    padding: 0;\n"
"    color: #CCC;\n"
"    background: #333;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#titleLabel {\n"
"    font-size: 14px;\n"
"}"));
        titleBarWidget = new QWidget(MyItemidget);
        titleBarWidget->setObjectName(QString::fromUtf8("titleBarWidget"));
        titleBarWidget->setGeometry(QRect(0, 0, 501, 40));
        btn_close = new QPushButton(titleBarWidget);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(470, 10, 20, 20));
        lbl_title = new QLabel(titleBarWidget);
        lbl_title->setObjectName(QString::fromUtf8("lbl_title"));
        lbl_title->setGeometry(QRect(10, 11, 221, 21));
        centralWidget = new QWidget(MyItemidget);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setGeometry(QRect(0, 40, 531, 231));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        lbl_itemPicture = new QLabel(centralWidget);
        lbl_itemPicture->setObjectName(QString::fromUtf8("lbl_itemPicture"));
        lbl_itemPicture->setGeometry(QRect(50, 30, 131, 121));
        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(60, 170, 401, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_ok = new QPushButton(layoutWidget_2);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));

        horizontalLayout->addWidget(btn_ok);

        horizontalSpacer = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_cancel = new QPushButton(layoutWidget_2);
        btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));

        horizontalLayout->addWidget(btn_cancel);

        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 40, 251, 93));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lbl_itemName = new QLabel(layoutWidget);
        lbl_itemName->setObjectName(QString::fromUtf8("lbl_itemName"));

        gridLayout->addWidget(lbl_itemName, 0, 0, 1, 1);

        comboBox_itemMyType = new QComboBox(layoutWidget);
        comboBox_itemMyType->addItem(QString());
        comboBox_itemMyType->addItem(QString());
        comboBox_itemMyType->setObjectName(QString::fromUtf8("comboBox_itemMyType"));

        gridLayout->addWidget(comboBox_itemMyType, 1, 1, 1, 1);

        lbl_itemMyType = new QLabel(layoutWidget);
        lbl_itemMyType->setObjectName(QString::fromUtf8("lbl_itemMyType"));

        gridLayout->addWidget(lbl_itemMyType, 1, 0, 1, 1);

        txt_itemName = new QLineEdit(layoutWidget);
        txt_itemName->setObjectName(QString::fromUtf8("txt_itemName"));

        gridLayout->addWidget(txt_itemName, 0, 1, 1, 1);

        lbl_itemToggle = new QLabel(layoutWidget);
        lbl_itemToggle->setObjectName(QString::fromUtf8("lbl_itemToggle"));

        gridLayout->addWidget(lbl_itemToggle, 2, 0, 1, 1);

        txt_itemToggle = new QLineEdit(layoutWidget);
        txt_itemToggle->setObjectName(QString::fromUtf8("txt_itemToggle"));

        gridLayout->addWidget(txt_itemToggle, 2, 1, 1, 1);


        retranslateUi(MyItemidget);

        QMetaObject::connectSlotsByName(MyItemidget);
    } // setupUi

    void retranslateUi(QWidget *MyItemidget)
    {
        MyItemidget->setWindowTitle(QCoreApplication::translate("MyItemidget", "Form", nullptr));
        btn_close->setText(QCoreApplication::translate("MyItemidget", "X", nullptr));
        lbl_title->setText(QCoreApplication::translate("MyItemidget", "\346\240\207\351\242\230", nullptr));
        lbl_itemPicture->setText(QString());
        btn_ok->setText(QCoreApplication::translate("MyItemidget", "\347\241\256\345\256\232", nullptr));
        btn_cancel->setText(QCoreApplication::translate("MyItemidget", "\345\217\226\346\266\210", nullptr));
        lbl_itemName->setText(QCoreApplication::translate("MyItemidget", "Item\345\220\215\347\247\260", nullptr));
        comboBox_itemMyType->setItemText(0, QCoreApplication::translate("MyItemidget", "Test1", nullptr));
        comboBox_itemMyType->setItemText(1, QCoreApplication::translate("MyItemidget", "Test2", nullptr));

        lbl_itemMyType->setText(QCoreApplication::translate("MyItemidget", "Item\347\261\273\345\210\253", nullptr));
        lbl_itemToggle->setText(QCoreApplication::translate("MyItemidget", "Item\346\263\250\351\207\212", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyItemidget: public Ui_MyItemidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYITEMIDGET_H
