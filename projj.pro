QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += network
QT       += core gui network

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cashpayment.cpp \
    flights.cpp \
    graph.cpp \
    interface.cpp \
    invoicewallet.cpp \
    main.cpp \
    payment.cpp \
    paymentinvoice.cpp \
    paymentui.cpp \
    signin.cpp \
    signup.cpp \
    smtp.cpp \
    visa_payment.cpp \
    wallet.cpp \
    walletfiller.cpp

HEADERS += \
    cashpayment.h \
    flights.h \
    graph.h \
    interface.h \
    invoicewallet.h \
    payment.h \
    paymentinvoice.h \
    paymentui.h \
    signin.h \
    signup.h \
    smtp.h \
    visa_payment.h \
    wallet.h \
    walletfiller.h

FORMS += \
    flights.ui \
    interface.ui \
    invoicewallet.ui \
    payment.ui \
    paymentinvoice.ui \
    paymentui.ui \
    signin.ui \
    signup.ui \
    wallet.ui \
    walletfiller.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Background.qrc
