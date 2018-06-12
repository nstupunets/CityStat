#-------------------------------------------------
#
# Project created by QtCreator 2018-06-01T12:37:01
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CityStat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        citystatmainwindow.cpp \
    citystatmodel.cpp \
    dataloader.cpp \
    citystatitemdelegate.cpp \
    addnewcitydialog.cpp \
    cityitem.cpp \
    statusbarwidget.cpp

HEADERS += \
        citystatmainwindow.h \
    citystatmodel.h \
    dataloader.h \
    cityitem.h \
    citystatitemdelegate.h \
    addnewcitydialog.h \
    iaggragateddataprovider.h \
    statusbarwidget.h

FORMS += \
        citystatmainwindow.ui \
    addnewcitydialog.ui

RESOURCES += \
    images.qrc
