QT       += core gui widgets sql
#QT       += mqtt

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    basededonnees.cpp \
    communicationmqtt.cpp \
    ecoclassroom.cpp \
    etatssalle.cpp \
    mesures.cpp \
    salle.cpp \
    main.cpp

HEADERS += \
    basededonnees.h \
    communicationmqtt.h \
    ecoclassroom.h \
    etatssalle.h \
    mesures.h \
    salle.h

RESOURCES += \
    ressources.qrc

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
