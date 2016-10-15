TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++1z


SOURCES += main.cpp \
    engine.cpp \
    compiler.cpp \
    CompilationObject.cpp \
    runes/Rune_X.cpp \
    runes/Rune_C.cpp \
    runes/Rune_A.cpp \
    runes/Rune_N.cpp \
    runes/Rune_I.cpp \
    runes/Rune_O.cpp \
    runes/Rune_R.cpp \
    runes/Rune_L.cpp \
    rune_common.cpp \
    ChronicsFile.cpp \
    Runic_Inscription.cpp \
    runetala.cpp \
    runes/Data_Rune.cpp \
    runes/Action_Rune.cpp \
    runes/Param_Rune.cpp

HEADERS += \
    engine.h \
    compiler.h \
    CompilationObject.h \
    runes/Rune_X.h \
    runes/Rune_C.h \
    runes/Rune_A.h \
    runes/Rune_N.h \
    runes/Rune_I.h \
    runes/Rune_O.h \
    runes/Rune_R.h \
    runes/Rune_L.h \
    rune_common.h \
    ChronicsFile.h \
    Runic_Inscription.h \
    runetala.h \
    runes/Data_Rune.h \
    runes/Action_Rune.h \
    runes/Param_Rune.h


win32{
    DEFINES += ON_WINDOWS \
        "CPP_COMPILER_SETTING=\\\"g++\\ -std=c++1z\\ -static-libgcc\\ -static-libstdc++\\ -static\\\"" \
        "EXECUTABLE_EXTENSION=\\\".exe\\\""
}


unix{
    DEFINES += ON_UNIX \
        "CPP_COMPILER_SETTING=\\\"g++\\ -std=c++1z\\ -static-libgcc\\ -static-libstdc++\\ -static\\\"" \
        "EXECUTABLE_EXTENSION=\\\"\\\""
}


#link boost
    #win32:CONFIG(release, debug|release):       LIBS += -L$$PWD/../../../../../../../Boost/boost_1_62_0/stage/lib/     -lboost_system-mgw53-mt-1_62.a      -lboost_filesystem-mgw53-mt-1_62
    #else:win32:CONFIG(debug, debug|release):    LIBS += -L$$PWD/../../../../../../../Boost/boost_1_62_0/stage/lib/     -lboost_system-mgw53-mt-d-1_62.a      -lboost_filesystem-mgw53-mt-d-1_62
    #else:unix:                                  LIBS += -L$$PWD/../../../../../../../Boost/boost_1_62_0/stage/lib/     -lboost_system-mgw53-mt-1_62.a      -lboost_filesystem-mgw53-mt-1_62

    #INCLUDEPATH += $$PWD/../../../../../../../Boost/boost_1_62_0
    #DEPENDPATH += $$PWD/../../../../../../../Boost/boost_1_62_0
