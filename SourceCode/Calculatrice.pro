#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T18:05:35
#
#-------------------------------------------------

QT       += core gui

TARGET = Calculatrice
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Constantes/Rationnel.cpp \
    Constantes/Constante.cpp \
    Constantes/Complexe.cpp \
    Calculatrice.cpp \
    Constantes/Pile.cpp \
    Constantes/Expression.cpp \
    Apropos.cpp \
    Parametres.cpp \
    Aide.cpp \
    Erreurs.cpp

HEADERS  += mainwindow.h \
    Constantes/Rationnel.h \
    Constantes/Constante.h \
    Constantes/Complexe.h \
    Calculatrice.h \
    Constantes/Pile.h \
    Constantes/Expression.h \
    Apropos.h \
    Parametres.h \
    Aide.h \
    Erreurs.h

FORMS    += mainwindow.ui \
    Apropos.ui \
    Parametres.ui \
    aide.ui
RC_FILE = myapp.rc
