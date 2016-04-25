TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/main.cpp \
    src/dna_to_bin.cpp

HEADERS += \
    binary.h \
    src/binary.h \
    src/bool_vector.h
