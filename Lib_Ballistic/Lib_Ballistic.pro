QT += widgets printsupport

TEMPLATE = lib
DEFINES += LIB_BALLISTIC_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AirDensity.cpp \
    Atmosphere.cpp \
    BallisticProjector.cpp \
    BallisticTrajectory.cpp \
    BulletCondition.cpp \
    Conversions.cpp \
    DragFunction.cpp \
    EnumDragFunction.cpp \
    FlightSpeed.cpp \
    Gun.cpp \
    TrajectoryMatch.cpp \
    Util.cpp \
    Wind.cpp \
    jsoncpp.cpp \
    lib_ballistic.cpp \
    qcustomplot.cpp

HEADERS += \
    AirDensity.h \
    Atmosphere.h \
    BallisticProjector.h \
    BallisticTrajectory.h \
    BarrettM82A1.h \
    Bora12.h \
    BulletCondition.h \
    Conversions.h \
    DragFunction.h \
    EnumDragFunction.h \
    FN_Minimi.h \
    FlightSpeed.h \
    Glock19.h \
    Gun.h \
    ImpalaPlus12.h \
    KNT76.h \
    Kilinc2000.h \
    Law.h \
    Lib_Ballistic_global.h \
    M2Browning.h \
    MK19Bomb.h \
    MP5.h \
    MPT55.h \
    MPT76.h \
    RPG7.h \
    Sar109T.h \
    SigSauer.h \
    TrajectoryMatch.h \
    UT1Havan.h \
    Util.h \
    Wind.h \
    json-forwards.h \
    json.h \
    lib_ballistic.h \
    qcustomplot.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
