#-------------------------------------------------
#
# Project created by QtCreator 2013-08-16T16:51:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = opencvtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += objectDetection.cpp #   facedetect.cpp

LIBS += -lopencv_objdetect \
        -lopencv_ocl
