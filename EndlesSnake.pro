#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T22:05:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EndlesSnake
TEMPLATE = app


SOURCES += main.cpp\
        game.cpp \
    button.cpp \
    wall.cpp \
    snake.cpp \
    playingfield.cpp

HEADERS  += game.h \
    button.h \
    wall.h \
    snake.h \
    playingfield.h

FORMS    +=
