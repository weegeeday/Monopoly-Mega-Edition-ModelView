#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T16:42:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monopoly
TEMPLATE = app
RC_ICONS += images/monopoly.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    board.cpp \
    die.cpp \
    actioncard.cpp \
    space.cpp \
    idlespace.cpp \
    propertyspace.cpp \
    cardspace.cpp \
    taxspace.cpp \
    player.cpp \
    gameview.cpp \
    playerview.cpp \
    boardview.cpp \
    spaceview.cpp \
    pieceview.cpp \
    buttondialog.cpp \
    startdialog.cpp \
    turnview.cpp \
    property.cpp \
    busticket.cpp \
    auctiondialog.cpp \
    railroad.cpp \
    streetproperty.cpp \
    utilityproperty.cpp \
    busticketspace.cpp \
    auctionspace.cpp \
    gotojailspace.cpp \
    buyhousesdialog.cpp \
    mortgagedialog.cpp \
    askplayertradedialog.cpp \
    tradedialog.cpp

HEADERS  += mainwindow.h \
    game.h \
    board.h \
    die.h \
    actioncard.h \
    space.h \
    idlespace.h \
    propertyspace.h \
    cardspace.h \
    taxspace.h \
    player.h \
    gameview.h \
    playerview.h \
    boardview.h \
    spaceview.h \
    pieceview.h \
    buttondialog.h \
    startdialog.h \
    turnview.h \
    property.h \
    busticket.h \
    auctiondialog.h \
    railroad.h \
    streetproperty.h \
    utilityproperty.h \
    busticketspace.h \
    auctionspace.h \
    gotojailspace.h \
    buyhousesdialog.h \
    mortgagedialog.h \
    askplayertradedialog.h \
    tradedialog.h


RESOURCES += \
    resources.qrc

