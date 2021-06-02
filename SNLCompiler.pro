QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global.cpp \
    lexer.cpp \
    lexerimp.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    parserll1.cpp \
    parserrecursivedescent.cpp \
    syntaxtree.cpp \
    token.cpp \
    tokenlist.cpp

HEADERS += \
    global.h \
    lexer.h \
    lexerimp.h \
    mainwindow.h \
    parser.h \
    parserll1.h \
    parserrecursivedescent.h \
    syntaxtree.h \
    token.h \
    tokenlist.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
