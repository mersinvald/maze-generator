TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c11

LIBS += -lGL -lSDL2 -lpng

SOURCES += \
    common.c \
    funcs.c \
    generator.c \
    main.c \
    renderer.c \
    seeker.c \
    stack.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    common.h \
    funcs.h \
    generator.h \
    renderer.h \
    seeker.h \
    stack.h \
    types.h

