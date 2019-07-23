#-------------------------------------------------
#
# Project created by QtCreator 2019-07-20T15:30:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bibliothek
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

CONFIG += c++11

SOURCES += \
        acceptlending.cpp \
        addmedia.cpp \
        adduser.cpp \
        book.cpp \
        cd.cpp \
        library.cpp \
        main.cpp \
        mainwindow.cpp \
        medium.cpp \
        notewindow.cpp \
        showmedia.cpp \
        user.cpp

HEADERS += \
        acceptlending.h \
        addmedia.h \
        adduser.h \
        book.h \
        cd.h \
        library.h \
        mainwindow.h \
        medium.h \
        notewindow.h \
        showmedia.h \
        user.h

FORMS += \
        acceptlending.ui \
        addmedia.ui \
        adduser.ui \
        mainwindow.ui \
        notewindow.ui \
        showmedia.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
