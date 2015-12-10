TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

DISTFILES += \
    ../CalculatorExt/input.txt \
    ../CalculatorExt/input.zip


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libzip
