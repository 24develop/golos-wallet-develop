#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T08:42:20
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = golos-wallet
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
        mainwindow.cpp \
    websocketclient.cpp \
    command.cpp \
    apicaller.cpp \
    api.cpp \
    cmd.cpp \
    loginwindow.cpp \
    paymentdialog.cpp

HEADERS += \
        mainwindow.h \
    websocketclient.h \
    command.h \
    apicaller.h \
    api.h \
    cmd.h \
    loginwindow.h \
    paymentdialog.h

FORMS += \
        mainwindow.ui \
    loginwindow.ui \
    paymentdialog.ui \
    paymentdialog.ui
