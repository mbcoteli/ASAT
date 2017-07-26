#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T12:06:27
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MicrophoneArray
TEMPLATE = app


SOURCES += main.cpp \
    audiocapture.cpp \
    lebedevpoints.cpp \
    maincontroller.cpp \
    mainwindow.cpp \
    microphonequadrature.cpp \
    my_qlistview.cpp \
    qcustomplot.cpp \
    worker.cpp \
    algorithmthreadlebedev.cpp \
    algorithmthreadhealpix.cpp

HEADERS  += \
    AlgorithmCalc.h \
    audiocapture.h \
    lebedevpoints.h \
    maincontroller.h \
    mainwindow.h \
    mataudio.h \
    microphonequadrature.h \
    my_qlistview.h \
    qcustomplot.h \
    spatialalgorithm.h \
    worker.h \
    algorithmthreadlebedev.h \
    algorithmthreadhealpix.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += C:/Spatial_audio/boost_1_61_0/boost_1_61_0 C:/Spatial_audio/fftw-3.3.2/fftw-3.3.2/api

LIBS += "-LC:/Spatial_audio/boost_1_61_0/boost_1_61_0/stage/lib" "-LC:/Spatial_audio/fftw-3.3.2/fftw-3.3.2/fftw-3.3-libs/Debug" -llibfftw-3.3

QMAKE_LFLAGS +=/INCREMENTAL:NO

QMAKE_LFLAGS += /STACK:32000000

QMAKE_LFLAGS += /HEAP:32000000


DISTFILES += \
    icon/1486002287_user_full_add.png \
    icon/1486002368_user_profile_edit.png \
    icon/1486002396_server_settings.png \
    icon/1486002413_arrow_full_right.png \
    icon/1486002464_edit.png \
    icon/add_icon.png \
    icon/analyze_icon.png \
    icon/barcode_icon.png \
    icon/delete_icon.png \
    icon/next_icon.png \
    icon/None.png \
    icon/open_icon.png \
    icon/open_port.png \
    icon/paint_icon.png \
    icon/save_icon.png \
    icon/start_icon.png
