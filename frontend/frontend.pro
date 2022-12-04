QT       += core gui
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debitbalance.cpp \
    debitwindow.cpp \
    main.cpp \
    mainmenu.cpp \
    mainmenucredit.cpp \
    mainwindow.cpp \
    savings.cpp \
    session.cpp \
    transactions.cpp

HEADERS += \
    debitbalance.h \
    debitwindow.h \
    mainmenu.h \
    mainmenucredit.h \
    mainwindow.h \
    savings.h \
    session.h \
    transactions.h

FORMS += \
    debitbalance.ui \
    debitwindow.ui \
    mainmenu.ui \
    mainmenucredit.ui \
    mainwindow.ui \
    savings.ui \
    transactions.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
