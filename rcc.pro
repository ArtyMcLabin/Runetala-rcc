TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++1z


SOURCES += main.cpp \
    engine.cpp \
    compiler.cpp

HEADERS += \
    engine.h \
    compiler.h


win32{
    DEFINES += ON_WINDOWS \
        #"CPP_COMPILER_SETTING=\\\"g++ \\-std\\=c++1z\\\""
}

unix{
    DEFINES += ON_UNIX \
        #"CPP_COMPILER_SETTING=g++ -std=c++1z"
}


#link boost
    #win32:CONFIG(release, debug|release):       LIBS += -L$$PWD/../../../../../../../Boost/boost_1_62_0/stage/lib/     -lboost_system-mgw53-mt-1_62.a      -lboost_filesystem-mgw53-mt-1_62
    #else:win32:CONFIG(debug, debug|release):    LIBS += -L$$PWD/../../../../../../../Boost/boost_1_62_0/stage/lib/     -lboost_system-mgw53-mt-d-1_62.a      -lboost_filesystem-mgw53-mt-d-1_62
    #else:unix:                                  LIBS += -L$$PWD/../../../../../../../Boost/boost_1_62_0/stage/lib/     -lboost_system-mgw53-mt-1_62.a      -lboost_filesystem-mgw53-mt-1_62

    #INCLUDEPATH += $$PWD/../../../../../../../Boost/boost_1_62_0
    #DEPENDPATH += $$PWD/../../../../../../../Boost/boost_1_62_0
