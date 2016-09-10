#-------------------------------------------------
#
# Project created by QtCreator 2015-06-05T20:13:52
#
#-------------------------------------------------

#QMAKE_POST_LINK=make_doc.sh

QT       += core gui
QT       += xml
QT       += printsupport
QT       += concurrent
#QT       += svg
#QT       += webenginewidgets

system(touch version.h)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MrWriter
TEMPLATE = app

HEADERS  += version.h \
    pagesettingsdialog.h \
    colorbutton.h \
    stroke.h \
    mrdoc.h

#VERSION_MAJOR = MY_MAJOR_VERSION
#VERSION_MINOR = MY_MINOR_VERSION

SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    document.cpp \
    page.cpp \
    qcompressor.cpp \
    selection.cpp \
    commands.cpp \
    tabletapplication.cpp \
    pagesettingsdialog.cpp \
    colorbutton.cpp \
    stroke.cpp

HEADERS  += mainwindow.h \
    widget.h \
    document.h \
    page.h \
    qcompressor.h \
    selection.h \
    commands.h \
    tictoc.h \
    tabletapplication.h \
    version.h

FORMS    +=

RESOURCES += \
    myresource.qrc

LIBS += -lz

ICON = MyIcon.icns

RC_ICONS = MyIcon.ico

DISTFILES += \
    images/openIcon.png \
    images/newIcon.png \
    Info.plist \
    COPYING

CONFIG += c++11

#QMAKE_CXXFLAGS_RELEASE -= -O
#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2

#QMAKE_CXXFLAGS_RELEASE *= -O3

QMAKE_INFO_PLIST = Info.plist

