QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataLoader.cpp \
    DataSaver.cpp \
    Edge.cpp \
    FileManager.cpp \
    Graph.cpp \
    GraphPage.cpp \
    HomePage.cpp \
    LoginPage.cpp \
    Manager.cpp \
    Node.cpp \
    PathFinder.cpp \
    PathPage.cpp \
    Tools.cpp \
    User.cpp \
    bfsnode.cpp \
    history.cpp \
    main.cpp \
    mainwindow.cpp \
    profile.cpp \
    traverse.cpp

HEADERS += \
    DataLoader.h \
    DataSaver.h \
    Edge.h \
    FileManager.h \
    Globals.h \
    Graph.h \
    GraphPage.h \
    HomePage.h \
    LoginPage.h \
    Manager.h \
    Node.h \
    Path.h \
    PathFinder.h \
    PathPage.h \
    Tools.h \
    User.h \
    bfsnode.h \
    history.h \
    mainwindow.h \
    profile.h \
    traverse.h

FORMS += \
    GraphPage.ui \
    HomePage.ui \
    LoginPage.ui \
    PathPage.ui \
    history.ui \
    mainwindow.ui \
    traverse.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    QtWidgetsApplication1.qrc \
    graph.qrc \
    log.qrc

DISTFILES += \
    car-background.png \
    car.png \
    city1.png \
    city10.png \
    city11.png \
    city12.png \
    city13.png \
    city14.png \
    city15.png \
    city16.png \
    city17.png \
    city18.png \
    city2.png \
    city20.png \
    city21.png \
    city3.png \
    city4.png \
    city5.png \
    city6.png \
    city8.png \
    city9.png \
    color-backgrond.jpg \
    undoicon.png
