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


linux:!android {
    LIBS += -L"/usr/local/lib" -lsecp256k1
}

android {
    LIBS += -L$$PWD/prebuild/android/secp256k1/armeabi-v7a/lib -lsecp256k1

    ANDROID_EXTRA_LIBS = \
       $$PWD/prebuild/android/openssl/armeabi-v7a/libcrypto.so \
       $$PWD/prebuild/android/openssl/armeabi-v7a/libssl.so
}


DEPENDPATH += $$PWD/prebuild/include

INCLUDEPATH += "/usr/local/include" $$PWD/prebuild/android/secp256k1/armeabi-v7a/include

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    command.cpp \
    apicaller.cpp \
    api.cpp \
    loginwindow.cpp \
    paymentdialog.cpp \
    commandsender.cpp \
    cmdsender.cpp \
    socketsender.cpp \
    transactionerrordialog.cpp \
    loaderdialog.cpp \
    Transaction.cpp \
    Response.cpp \
    lib/Signer.cpp \
    lib/Auth.cpp \
    lib/bs58/QBS58.cpp \
    lib/bs58/base58_c.cpp

HEADERS += \
        mainwindow.h \
    command.h \
    apicaller.h \
    api.h \
    loginwindow.h \
    paymentdialog.h \
    commandsender.h \
    cmdsender.h \
    socketsender.h \
    transactionerrordialog.h \
    loaderdialog.h \
    Transaction.h \
    Response.h \
    lib/Signer.h \
    lib/Auth.h \
    lib/bs58/QBS58.h \
    lib/bs58/libbase58.h

FORMS += \
        mainwindow.ui \
    loginwindow.ui \
    paymentdialog.ui \
    paymentdialog.ui \
    transactionerrordialog.ui \
    loaderdialog.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
