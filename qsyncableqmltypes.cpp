#include "qsyncableqmltypes.h"
#include "qsjsonlistmodel.h"
#include "qsuuid.h"
#include "qsyncableqmlwrapper.h"

template <typename T>
static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    T* object = new T();

    return object;
}

void registerQsTypes(const char *uri, int major, int minor) {
    qmlRegisterType<QSJsonListModel>(uri, major, minor, "JsonListModel");
    qmlRegisterSingletonType<QSUuid>(uri, major, minor, "Uuid", provider<QSUuid>);
    qmlRegisterSingletonType<QSyncableQmlWrapper>(uri, major, minor, "QSyncable", provider<QSyncableQmlWrapper>);
}

static void registerTypes() {
    registerQsTypes("QSyncable", 1, 0);
}

#ifndef QML_PLUGIN
Q_COREAPP_STARTUP_FUNCTION(registerTypes)
#endif
