TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    mesh.cpp \
    point.cpp \
    triangle.cpp \
    city.cpp \
    detail.cpp \
    quadarea.cpp \
    trianglearea.cpp \
    function.cpp \
    line.cpp \
    groundfloor.cpp \
    floor.cpp \
    roof.cpp \
    quad.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mesh.h \
    point.h \
    triangle.h \
    city.h \
    detail.h \
    quadarea.h \
    trianglearea.h \
    line.h \
    groundfloor.h \
    floor.h \
    roof.h \
    function.h \
    quad.h
