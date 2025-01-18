/********************************************************************************
** Form generated from reading UI file 'loadwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADWIDGET_H
#define UI_LOADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadWidget
{
public:
    QWidget *widget;

    void setupUi(QWidget *LoadWidget)
    {
        if (LoadWidget->objectName().isEmpty())
            LoadWidget->setObjectName(QString::fromUtf8("LoadWidget"));
        LoadWidget->resize(700, 342);
        widget = new QWidget(LoadWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 700, 342));

        retranslateUi(LoadWidget);

        QMetaObject::connectSlotsByName(LoadWidget);
    } // setupUi

    void retranslateUi(QWidget *LoadWidget)
    {
        LoadWidget->setWindowTitle(QCoreApplication::translate("LoadWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadWidget: public Ui_LoadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADWIDGET_H
