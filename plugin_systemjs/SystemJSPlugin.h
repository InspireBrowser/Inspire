#ifndef SYSTEM_JS_PLUGIN
#define SYSTEM_JS_PLUGIN

#include <QObject>
#include "GenericPlugin.h"

class SystemJSPlugin : public QObject, public GenericPlugin
{
    Q_OBJECT
    Q_INTERFACES(GenericPlugin)

public:
    explicit SystemJSPlugin(QObject* parent = 0);

    bool InitialisePlugin();
    bool DeInitialisePlugin();

    QString GetId();
    QString GetName();
    QString GetDescription();
};

#endif //SYSTEM_JS_PLUGIN
