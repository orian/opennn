TEMPLATE = app
CONFIG += console

TARGET = fed_batch_fermenter

DESTDIR = "$$PWD\bin"

SOURCES += \
    fed_batch_fermenter.cpp \
    main.cpp

HEADERS += \
    fed_batch_fermenter.h

win32{
QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++
QMAKE_LFLAGS += -static-libstdc++
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
