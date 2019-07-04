#-------------------------------------------------
#
# Project created by QtCreator 2019-07-02T21:40:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled2
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
        addequipment.cpp \
        body.cpp \
        createproject.cpp \
        equipment.cpp \
        equipmentcreator.cpp \
        inputconnector.cpp \
        main.cpp \
        mainwindow.cpp \
        outputconnector.cpp \
        selectpath.cpp

HEADERS += \
        addequipment.h \
        body.h \
        createproject.h \
        equipment.h \
        equipmentcreator.h \
        inputconnector.h \
        mainwindow.h \
        outputconnector.h \
        selectpath.h

FORMS += \
        addequipment.ui \
        createproject.ui \
        equipmentcreator.ui \
        mainwindow.ui \
        selectpath.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    projects/connections.xml \
    projects/equipment.xml \
    projects/Новый текстовый документ (2).txt \
    projects/Новый текстовый документ.txt
