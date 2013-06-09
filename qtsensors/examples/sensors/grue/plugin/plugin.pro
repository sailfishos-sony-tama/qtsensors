TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(qtsensors_grue)
PLUGIN_TYPE = sensors

QT = core sensors

INCLUDEPATH += $$PWD/../lib
LIBS += -L$$OUT_PWD/../lib -lgruesensor

# Shared gruesensor library will be installed in parent directory.
# Define rpath so that this plugin will know where to look for it.
unix:!mac: QMAKE_LFLAGS += -Wl,-rpath,\\\$\$ORIGIN/..

HEADERS += gruesensorimpl.h\

SOURCES += gruesensorimpl.cpp\
           main.cpp\


# Install the plugin under Grue example directory
target.path=$$[QT_INSTALL_EXAMPLES]/qtsensors/grue/$$PLUGIN_TYPE
INSTALLS += target

OTHER_FILES += \
    plugin.json