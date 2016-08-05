#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T15:23:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qtHaveModule(printsupport): QT += printsupport

#CONFIG  += C++11
QMAKE_CXXFLAGS += -std=c++0x

TARGET = ICCardApp
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    TabWidgets/tabwidget_ownercard.cpp \
    TabWidgets/tabwidget_managercard.cpp \
    TabWidgets/tabwidget_functioncard.cpp \
    TabWidgets/tabwidget_remoteoperation.cpp \
    TabWidgets/tabwidget_statisticalanalysis.cpp \
    TabWidgets/tabwidget_elevatormanage.cpp \
    TabWidgets/tabwidget_systemsetting.cpp \
    TabWidgets/tabwidget_helpsupport.cpp \
    dialogsignin.cpp \
    CH375/ch375rw.cpp \
    Tools/typeconvert.cpp \
    DataStructure/ds_timesetting.cpp \
    DataStructure/ds_clearmemory.cpp \
    DataStructure/ds_enablecard.cpp \
    DataBase/sqldb.cpp \
    SubDlg/addliftdlg.cpp \
    SubDlg/addchargestddlg.cpp \
    SubDlg/selectliftdlg.cpp \
    DataBase/sqldbmodel.cpp \
    SubDlg/addusrdlg.cpp \
    SubDlg/selectfloordlg.cpp \
    DataStructure/ds_sysswitchcard.cpp \
    SubDlg/selectsysswitchdlg.cpp \
    DataStructure/ds_usercard.cpp

HEADERS  += mainwindow.h \
    TabWidgets/tabwidget_ownercard.h \
    TabWidgets/tabwidget_managercard.h \
    TabWidgets/tabwidget_functioncard.h \
    TabWidgets/tabwidget_remoteoperation.h \
    TabWidgets/tabwidget_statisticalanalysis.h \
    TabWidgets/tabwidget_elevatormanage.h \
    TabWidgets/tabwidget_systemsetting.h \
    TabWidgets/tabwidget_helpsupport.h \
    TabWidgets/includetabs.h \
    dialogsignin.h \
    CH375/CH375DLL.H \
    CH375/ch375rw.h \
    Tools/typeconvert.h \
    DataStructure/ds_timesetting.h \
    DataStructure/ds_clearmemory.h \
    DataStructure/ds_enablecard.h \
    DataBase/sqldb.h \
    SubDlg/addliftdlg.h \
    SubDlg/addchargestddlg.h \
    SubDlg/selectliftdlg.h \
    DataBase/sqldbmodel.h \
    SubDlg/addusrdlg.h \
    SubDlg/selectfloordlg.h \
    DataStructure/ds_sysswitchcard.h \
    SubDlg/selectsysswitchdlg.h \
    DataStructure/ds_usercard.h

FORMS    += mainwindow.ui \
    TabWidgets/tabwidget_ownercard.ui \
    TabWidgets/tabwidget_managercard.ui \
    TabWidgets/tabwidget_functioncard.ui \
    TabWidgets/tabwidget_remoteoperation.ui \
    TabWidgets/tabwidget_statisticalanalysis.ui \
    TabWidgets/tabwidget_elevatormanage.ui \
    TabWidgets/tabwidget_systemsetting.ui \
    TabWidgets/tabwidget_helpsupport.ui \
    dialogsignin.ui \
    SubDlg/addliftdlg.ui \
    SubDlg/addchargestddlg.ui \
    SubDlg/selectliftdlg.ui \
    SubDlg/addusrdlg.ui \
    SubDlg/selectfloordlg.ui \
    SubDlg/selectsysswitchdlg.ui

RESOURCES += \
    iccardapp.qrc

DESTDIR = ../Output

#¾²Ì¬Á¬½Ó
LIBS += -L../Output -lCH375DLL
LIBS += -L../Output -llibmysql
