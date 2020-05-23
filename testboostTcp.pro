TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        TcpClient.cpp \
        main.cpp \
        main2.cpp

HEADERS += \
    TcpClient.h
# boost
LIBS += -lboost_system -lpthread -lboost_thread
