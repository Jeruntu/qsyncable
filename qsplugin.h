#ifndef QMLQSYNCABLEPLUGIN_H
#define QMLQSYNCABLEPLUGIN_H

#include <QQmlExtensionPlugin>

class QmlQSyncablePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // QMLQSYNCABLEPLUGIN_H

