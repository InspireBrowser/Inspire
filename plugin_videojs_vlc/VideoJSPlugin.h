#ifndef VIDEO_JS_PLUGIN
#define VIDEO_JS_PLUGIN

#include <QObject>
#include "GenericPlugin.h"

class VideoJSPlugin : public QObject, public GenericPlugin
{
    Q_OBJECT
    Q_INTERFACES(GenericPlugin)

public:
    explicit VideoJSPlugin(QObject* parent = 0);

    bool InitialisePlugin();
    bool DeInitialisePlugin();

    QString GetId();
    QString GetName();
    QString GetDescription();
};

#endif //VIDEO_JS_PLUGIN
