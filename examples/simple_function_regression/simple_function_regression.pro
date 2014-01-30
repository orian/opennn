###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.intelnics.com/opennn                                                                      #
#                                                                                                 #
#   S I M P L E   F U N C I O N   R E G R E S S I O N   P R O J E C T                             #
#                                                                                                 #
#   Roberto Lopez                                                                                 #
#   Intelnics - The artificial intelligence company                                               #
#   robertolopez@intelnics.com                                                                    #
#                                                                                                 #
###################################################################################################

TEMPLATE = app
CONFIG += console

TARGET = simple_function_regression

DESTDIR = "$$PWD\bin"

SOURCES = main.cpp

win32{
QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++
QMAKE_LFLAGS += -static
}

# OpenNN library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../source/release/ -lopennn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../source/debug/ -lopennn
else:unix: LIBS += -L$$OUT_PWD/../../source/ -lopennn

INCLUDEPATH += $$PWD/../../source
DEPENDPATH += $$PWD/../../source

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../source/release/libopennn.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../source/debug/libopennn.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../source/libopennn.a

# TinyXML2 library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../tinyxml2/release/ -ltinyxml2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../tinyxml2/debug/ -ltinyxml2
else:unix: LIBS += -L$$OUT_PWD/../../tinyxml2/ -ltinyxml2

INCLUDEPATH += $$PWD/../../tinyxml2
DEPENDPATH += $$PWD/../../tinyxml2

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../tinyxml2/release/libtinyxml2.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../tinyxml2/debug/libtinyxml2.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../tinyxml2/libtinyxml2.a
