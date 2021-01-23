#include "qsplugin.h"
#include "qsyncableqmltypes.h"

#include <qqml.h>

void QmlQSyncablePlugin::registerTypes(const char *uri) {
    registerQsTypes(uri, QML_IMPORT_MAJOR_VERSION, QML_IMPORT_MINOR_VERSION);
}
