#-------------------------------------------------
#
# Project created by QtCreator 2019-03-30T21:30:38
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Base2B
TEMPLATE = app
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += rendering
INCLUDEPATH += core
INCLUDEPATH += core/testing
INCLUDEPATH += core/testing/testcases
INCLUDEPATH += objects
INCLUDEPATH += objects/player
INCLUDEPATH += objects/entities

SOURCES += \
    objects/entities/colouredentity.cpp \
    objects/entities/entity.cpp \
    objects/entities/entitydecorator.cpp \
    objects/entities/entityfactory.cpp \
    objects/entities/flyingentity.cpp \
    objects/player/jumpingstickman.cpp \
    objects/player/stickman.cpp \
    objects/background.cpp \
    objects/gameobject.cpp \
    objects/moon.cpp \
    rendering/debugrenderer.cpp \
    rendering/renderer.cpp \
    coordinate.cpp \
    main.cpp \
    score.cpp \
    core/testing/testcases/collisiontest.cpp \
    core/testing/testcases/jumptest.cpp \
    core/testing/testingdialog.cpp \
    core/testing/testrunner.cpp \
    core/dialog.cpp \
    core/game.cpp \
    core/gamestage.cpp \
    core/gamestagedecorator.cpp \
    core/stage2dialog.cpp \
    core/swaprendererstage.cpp \
    core/testing/testcases/flyingobstacletest.cpp \
    core/stagefactory.cpp \
    core/stage3dialog.cpp \
    objects/player/walkingstickman.cpp

HEADERS += \
    objects/entities/colouredentity.h \
    objects/entities/entity.h \
    objects/entities/entitydecorator.h \
    objects/entities/entityfactory.h \
    objects/entities/flyingentity.h \
    objects/player/jumpingstickman.h \
    objects/player/stickman.h \
    objects/background.h \
    objects/collision.h \
    objects/gameobject.h \
    objects/moon.h \
    rendering/debugrenderer.h \
    rendering/renderer.h \
    coordinate.h \
    score.h \
    core/testing/testcases/collisiontest.h \
    core/testing/testcases/jumptest.h \
    core/testing/testingdialog.h \
    core/testing/testrunner.h \
    core/dialog.h \
    core/game.h \
    core/gamestage.h \
    core/gamestagedecorator.h \
    core/stage2dialog.h \
    core/swaprendererstage.h \
    core/testing/testcases/flyingobstacletest.h \
    core/stagefactory.h \
    core/stage3dialog.h \
    objects/player/walkingstickman.h

FORMS += \
        dialog.ui

DISTFILES += config.txt

RESOURCES += \
    resources.qrc
