TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/dna_to_bin.cpp

HEADERS += \
    binary.h \
    src/bitset.h \
    src/hash_tables.h \
    src/dynamic_bitset.h \
    src/int_array.h \
    src/benchmarks_tools.h \
    src/utils.h
