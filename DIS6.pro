#-------------------------------------------------
#
# Project created by QtCreator 2018-02-19T13:11:04
#
#-------------------------------------------------

QT       -= core gui

TARGET = DIS6
TEMPLATE = lib

DEFINES += DIS6_LIBRARY

CONFIG += c++1z

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
        dis6.cpp \
    header.cpp \
    pdu.cpp \
    datastream.cpp \
    entitystatepdu.cpp \
    entityid.cpp \
    utils.cpp

HEADERS += \
        dis6.h \
    header.h \
    pdu.h \
    datastream.h \
    entitystatepdu.h \
    entityid.h \
    entitytype.h \
    utils.h \
    dis6_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
