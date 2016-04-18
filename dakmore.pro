TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG -= app_bundle

TARGET = dakmore
INCLUDEPATH += .

# Input
HEADERS += actor.h \
           bsp.h \
           bsplistener.h \
           engine.h \
           gui.h \
           map.h \
           monster.h \
           player.h \
           random.h \
	   sprites.h

SOURCES += actor.cpp \
           bsp.cpp \
           bsplistener.cpp \
           engine.cpp \
           gui.cpp \
           main.cpp \
           map.cpp \
           monster.cpp \
           player.cpp \
           random.cpp

INCLUDEPATH += SDL2/include/

LIBS += "C:\Users\robin\Source\Repos\dakmore\SDL2\lib\x86\SDL2main.lib"
LIBS += "C:\Users\robin\Source\Repos\dakmore\SDL2\lib\x86\SDL2.lib"
LIBS += "C:\Users\robin\Source\Repos\dakmore\SDL2\lib\libSDL2_image.dll.a"
