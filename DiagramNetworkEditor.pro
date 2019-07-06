#-------------------------------------------------
#
# Project created by QtCreator 2019-07-05T14:06:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiagramNetworkEditor
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
        equipment.cpp \
        equipmentcreator.cpp \
        equipmentrender.cpp \
        fileorganizer.cpp \
        inputconnector.cpp \
        main.cpp \
        mainwindow.cpp \
        outputconnector.cpp \
        projectname.cpp

HEADERS += \
        addequipment.h \
        body.h \
        equipment.h \
        equipmentcreator.h \
        equipmentrender.h \
        fileorganizer.h \
        inputconnector.h \
        mainwindow.h \
        outputconnector.h \
        projectname.h

FORMS += \
        addequipment.ui \
        equipmentcreator.ui \
        mainwindow.ui \
        projectname.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    img/BlueIn.png \
    img/RedIn.png \
    img/add.png \
    img/blue_in.png \
    img/blue_out.png \
    img/create equip.png \
    img/create new.png \
    img/cyan_in.png \
    img/cyan_out.png \
    img/edit.png \
    img/exit.png \
    img/green_in.png \
    img/green_out.png \
    img/icon_application.png \
    img/open.png \
    img/red_in.png \
    img/red_out.png \
    img/save as.png \
    img/save.png \
    img/yellow_in.png \
    img/yellow_out.png
