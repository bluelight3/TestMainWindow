QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MyHelper.cpp \
    arrow.cpp \
    command.cpp \
    control.cpp \
    diagramitem.cpp \
    diagramtextitem.cpp \
    generateprojectform.cpp \
    generateprojectthread.cpp \
    loadwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    myitem.cpp \
    myitemwidget.cpp \
    myscene.cpp \
    mytextitem.cpp \
    myview.cpp \
    searchwidget.cpp

HEADERS += \
    MyHelper.h \
    arrow.h \
    command.h \
    control.h \
    diagramitem.h \
    diagramtextitem.h \
    generateprojectform.h \
    generateprojectthread.h \
    global.h \
    loadwidget.h \
    mainwindow.h \
    myitem.h \
    myitemwidget.h \
    myscene.h \
    mytextitem.h \
    myview.h \
    searchwidget.h

FORMS += \
    generateprojectform.ui \
    loadwidget.ui \
    mainwindow.ui \
    myitemwidget.ui \
    searchwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    circuit.qrc \
    diagramscene.qrc \
    myimages.qrc \
    qss.qrc

DISTFILES += \
    labelQss.qss \
    更新记录
