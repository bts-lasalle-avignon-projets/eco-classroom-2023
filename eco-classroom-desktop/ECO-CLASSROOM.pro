QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    basededonnees.cpp \
    communicationmqtt.cpp \
    ecoclassroom.cpp \
    etatsalle.cpp \
    mesures.cpp \
    salle.cpp \
    main.cpp

HEADERS += \
    basededonnees.h \
    communicationmqtt.h \
    ecoclassroom.h \
    etatsalle.h \
    mesures.h \
    salle.h

RESOURCES += \
    ressources.qrc

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT

QT += mqtt
