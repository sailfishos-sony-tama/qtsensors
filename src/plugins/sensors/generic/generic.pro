TARGET = qtsensors_generic
QT = core sensors

PLUGIN_TYPE = sensors
PLUGIN_CLASS_NAME = genericSensorPlugin
load(qt_plugin)

SOURCES += main.cpp

HEADERS += generictiltsensor.h
SOURCES += generictiltsensor.cpp
DEFINES += QTSENSORS_GENERICTILTSENSOR

!blackberry {
    HEADERS += genericorientationsensor.h\
               genericalssensor.h

    SOURCES += genericorientationsensor.cpp\
               genericalssensor.cpp
    DEFINES += QTSENSORS_GENERICORIENTATIONSENSOR QTSENSORS_GENERICALSSENSOR
}

linux:!android {
   DEFINES += QTSENSORS_GENERICCOMPASS
   HEADERS += genericcompass.h
   SOURCES += genericcompass.cpp
   LIBS += -lrt
}

!blackberry:!android {
    HEADERS += genericrotationsensor.h
    SOURCES += genericrotationsensor.cpp
    DEFINES += QTSENSORS_GENERICROTATIONSENSOR
}

OTHER_FILES = plugin.json
