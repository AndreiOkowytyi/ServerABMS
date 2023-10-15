QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    queue_for_working_with_threads.cpp \
    secondary_task_control_unit.cpp \
    server.cpp \
    flow_control_block.cpp \
    working_thread.cpp

HEADERS += \
    mainwindow.h \
    queue_for_working_with_threads.h \
    secondary_task_control_unit.h \
    server.h \
    flow_control_block.h \
    working_thread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
