/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionSaveAs;
    QAction *actionexit;
    QAction *actionShowStatus;
    QAction *actionDelete;
    QAction *actionleftRotate;
    QAction *actionrightRotate;
    QAction *actionToFront;
    QAction *actionToBack;
    QAction *actionToGroup;
    QAction *actiongroupBreak;
    QAction *actionBold;
    QAction *actionUnderLine;
    QAction *actionItalic;
    QAction *actionLineColor;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionConnectLine;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu_file;
    QMenu *menu_edit;
    QMenu *menu_show;
    QMenu *menu_item;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1081, 779);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/images/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon3);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/images/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon4);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/images/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon5);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionexit = new QAction(MainWindow);
        actionexit->setObjectName(QString::fromUtf8("actionexit"));
        actionShowStatus = new QAction(MainWindow);
        actionShowStatus->setObjectName(QString::fromUtf8("actionShowStatus"));
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon6);
        actionleftRotate = new QAction(MainWindow);
        actionleftRotate->setObjectName(QString::fromUtf8("actionleftRotate"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/images/rotateleft.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionleftRotate->setIcon(icon7);
        actionrightRotate = new QAction(MainWindow);
        actionrightRotate->setObjectName(QString::fromUtf8("actionrightRotate"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/images/rotateright.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrightRotate->setIcon(icon8);
        actionToFront = new QAction(MainWindow);
        actionToFront->setObjectName(QString::fromUtf8("actionToFront"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/images/bringtofront.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToFront->setIcon(icon9);
        actionToBack = new QAction(MainWindow);
        actionToBack->setObjectName(QString::fromUtf8("actionToBack"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/images/sendtoback.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToBack->setIcon(icon10);
        actionToGroup = new QAction(MainWindow);
        actionToGroup->setObjectName(QString::fromUtf8("actionToGroup"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/image/images/group.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToGroup->setIcon(icon11);
        actiongroupBreak = new QAction(MainWindow);
        actiongroupBreak->setObjectName(QString::fromUtf8("actiongroupBreak"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/image/images/ungroup.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiongroupBreak->setIcon(icon12);
        actionBold = new QAction(MainWindow);
        actionBold->setObjectName(QString::fromUtf8("actionBold"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBold->setIcon(icon13);
        actionUnderLine = new QAction(MainWindow);
        actionUnderLine->setObjectName(QString::fromUtf8("actionUnderLine"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/images/underline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUnderLine->setIcon(icon14);
        actionItalic = new QAction(MainWindow);
        actionItalic->setObjectName(QString::fromUtf8("actionItalic"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/images/italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionItalic->setIcon(icon15);
        actionLineColor = new QAction(MainWindow);
        actionLineColor->setObjectName(QString::fromUtf8("actionLineColor"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/images/linecolor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLineColor->setIcon(icon16);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/image/images/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon17);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/images/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon18.addFile(QString::fromUtf8(":/image/images/redo.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actionRedo->setIcon(icon18);
        actionConnectLine = new QAction(MainWindow);
        actionConnectLine->setObjectName(QString::fromUtf8("actionConnectLine"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/images/linepointer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnectLine->setIcon(icon19);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1081, 26));
        menu_file = new QMenu(menubar);
        menu_file->setObjectName(QString::fromUtf8("menu_file"));
        menu_edit = new QMenu(menubar);
        menu_edit->setObjectName(QString::fromUtf8("menu_edit"));
        menu_show = new QMenu(menubar);
        menu_show->setObjectName(QString::fromUtf8("menu_show"));
        menu_item = new QMenu(menubar);
        menu_item->setObjectName(QString::fromUtf8("menu_item"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_file->menuAction());
        menubar->addAction(menu_edit->menuAction());
        menubar->addAction(menu_item->menuAction());
        menubar->addAction(menu_show->menuAction());
        menu_file->addAction(actionNew);
        menu_file->addAction(actionOpen);
        menu_file->addAction(actionSave);
        menu_file->addAction(actionSaveAs);
        menu_file->addSeparator();
        menu_file->addAction(actionexit);
        menu_edit->addAction(actionUndo);
        menu_edit->addAction(actionRedo);
        menu_edit->addSeparator();
        menu_edit->addAction(actionCut);
        menu_edit->addAction(actionCopy);
        menu_edit->addAction(actionPaste);
        menu_edit->addSeparator();
        menu_edit->addAction(actionDelete);
        menu_edit->addAction(actionleftRotate);
        menu_edit->addAction(actionrightRotate);
        menu_show->addAction(actionShowStatus);
        menu_item->addAction(actionToFront);
        menu_item->addAction(actionToBack);
        menu_item->addAction(actionToGroup);
        menu_item->addAction(actiongroupBreak);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionleftRotate);
        toolBar->addAction(actionrightRotate);
        toolBar->addAction(actionToFront);
        toolBar->addAction(actionToBack);
        toolBar->addAction(actionToGroup);
        toolBar->addAction(actiongroupBreak);
        toolBar->addSeparator();
        toolBar->addAction(actionBold);
        toolBar->addAction(actionItalic);
        toolBar->addAction(actionUnderLine);
        toolBar->addAction(actionLineColor);
        toolBar->addSeparator();
        toolBar->addAction(actionUndo);
        toolBar->addAction(actionRedo);
        toolBar->addSeparator();
        toolBar->addAction(actionConnectLine);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\205\203\344\272\244\344\272\222\350\275\257\344\273\266 Beta\347\211\210\357\274\214\344\273\205\350\207\252\346\210\221\345\255\246\344\271\240\347\224\250", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272(&N)", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveAs->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionexit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(&Q)", nullptr));
#if QT_CONFIG(tooltip)
        actionexit->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionexit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionShowStatus->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\347\212\266\346\200\201", nullptr));
#if QT_CONFIG(shortcut)
        actionShowStatus->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
#if QT_CONFIG(tooltip)
        actionDelete->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDelete->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionleftRotate->setText(QCoreApplication::translate("MainWindow", "\345\267\246\346\227\213", nullptr));
#if QT_CONFIG(tooltip)
        actionleftRotate->setToolTip(QCoreApplication::translate("MainWindow", "\345\267\246\346\227\213", nullptr));
#endif // QT_CONFIG(tooltip)
        actionrightRotate->setText(QCoreApplication::translate("MainWindow", "\345\217\263\346\227\213", nullptr));
#if QT_CONFIG(tooltip)
        actionrightRotate->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\263\346\227\213", nullptr));
#endif // QT_CONFIG(tooltip)
        actionToFront->setText(QCoreApplication::translate("MainWindow", "\345\211\215\347\275\256", nullptr));
#if QT_CONFIG(tooltip)
        actionToFront->setToolTip(QCoreApplication::translate("MainWindow", "\345\211\215\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        actionToBack->setText(QCoreApplication::translate("MainWindow", "\345\220\216\347\275\256", nullptr));
#if QT_CONFIG(tooltip)
        actionToBack->setToolTip(QCoreApplication::translate("MainWindow", "\345\220\216\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        actionToGroup->setText(QCoreApplication::translate("MainWindow", "\347\273\204\345\220\210", nullptr));
#if QT_CONFIG(tooltip)
        actionToGroup->setToolTip(QCoreApplication::translate("MainWindow", "\347\273\204\345\220\210", nullptr));
#endif // QT_CONFIG(tooltip)
        actiongroupBreak->setText(QCoreApplication::translate("MainWindow", "\346\211\223\346\225\243", nullptr));
#if QT_CONFIG(tooltip)
        actiongroupBreak->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\346\225\243", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBold->setText(QCoreApplication::translate("MainWindow", "\345\212\240\347\262\227", nullptr));
#if QT_CONFIG(tooltip)
        actionBold->setToolTip(QCoreApplication::translate("MainWindow", "\345\212\240\347\262\227", nullptr));
#endif // QT_CONFIG(tooltip)
        actionUnderLine->setText(QCoreApplication::translate("MainWindow", "\344\270\213\345\210\222\347\272\277", nullptr));
        actionItalic->setText(QCoreApplication::translate("MainWindow", "\346\226\234\344\275\223", nullptr));
        actionLineColor->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "\346\222\244\345\233\236", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215", nullptr));
#if QT_CONFIG(tooltip)
        actionRedo->setToolTip(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215", nullptr));
#endif // QT_CONFIG(tooltip)
        actionConnectLine->setText(QCoreApplication::translate("MainWindow", "\350\277\236\347\272\277", nullptr));
        menu_file->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_edit->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menu_show->setTitle(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272", nullptr));
        menu_item->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\205\203", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
