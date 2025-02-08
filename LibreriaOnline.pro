QT       += widgets

CONFIG   += c++11
TARGET = LibreriaOnline
TEMPLATE = app

# File sorgente
SOURCES += \
    main.cpp \
    model/Media.cpp \
    model/Libro.cpp \
    model/Film.cpp \
    model/Serie_TV.cpp \
    model/MediaManager.cpp \
    persistence/PersistenceManager.cpp \
    gui/MainWindow.cpp \
    gui/DialogMedia.cpp

# File header
HEADERS += \
    model/Media.h \
    model/Libro.h \
    model/Film.h \
    model/Serie_TV.h \
    model/MediaManager.h \
    persistence/PersistenceManager.h \
    gui/MainWindow.h \
    gui/DialogMedia.h

# File di interfaccia grafica
FORMS += \
    gui/MainWindow.ui \
    gui/DialogMedia.ui
