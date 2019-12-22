QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0.0.1
QMAKE_TARGET_DESCRIPTION = Created by: Anton, Dmitriy, Daniil, Vladislav, Oleg, Sergey, Aleksandr x2.
QMAKE_TARGET_COPYRIGHT = KusokGovn@
RC_ICONS = 2.ico

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    edge.cpp \
    graph.cpp \
    main.cpp \
    canvas.cpp \
    mainwindow.cpp \
    saving.cpp \
    tas15.cpp \
    task.cpp \
    task8.cpp \
    task9.cpp \
    vertex.cpp \
    file.cpp

HEADERS += \
    canvas.h \
    edge.h \
    graph.h \
    lab2.h \
    lab3.h \
    lab4.h \
    planar_dual.h \
    saving.h \
    tas15.h \
    task.h \
    task5.h \
    task6.h \
    task8.h \
    task9.h \
    vertex.h \
    delegate.h \
    mainwindow.h \
    file.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32-g++ {
    INCLUDEPATH += C:/boost/boost_1_71_0/boost_mingw_730_64/include/boost-1_71/
    LIBS += -LC:/boost/boost_1_71_0/boost_mingw_730_64/lib

} else:win32-msvc* {
    INCLUDEPATH += C:/boost/boost_1_71_0/boost_msvc2015/include/boost-1_71/
    LIBS += "-LC:/boost/boost_1_71_0/boost_msvc2015/lib" \
              -llibboost_graph-vc140-mt-gd-x32-1_71 \
              -llibboost_graph-vc140-mt-gd-x64-1_71 \
              -llibboost_graph-vc140-mt-sgd-x32-1_71 \
}

FORMS += \
    mainwindow.ui
