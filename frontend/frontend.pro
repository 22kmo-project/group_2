QT       += core gui
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    askforreceipt.cpp \
    debitbalance.cpp \
    debitwindow.cpp \
    main.cpp \
    mainmenu.cpp \
    mainmenucredit.cpp \
    mainwindow.cpp \
    receiptwindow.cpp \
    savings.cpp \
    session.cpp \
    transactions.cpp

HEADERS += \
    askforreceipt.h \
    debitbalance.h \
    debitwindow.h \
    mainmenu.h \
    mainmenucredit.h \
    mainwindow.h \
    receiptwindow.h \
    savings.h \
    session.h \
    transactions.h

FORMS += \
    askforreceipt.ui \
    debitbalance.ui \
    debitwindow.ui \
    mainmenu.ui \
    mainmenucredit.ui \
    mainwindow.ui \
    receiptwindow.ui \
    savings.ui \
    transactions.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
