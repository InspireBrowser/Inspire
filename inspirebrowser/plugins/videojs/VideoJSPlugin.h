#ifndef VIDEO_JS_PLUGIN
#define VIDEO_JS_PLUGIN

#include <QObject>
#include "GenericPlugin.h"

class VideoJSPlugin : public GenericPlugin
{
	Q_OBJECT
	Q_INTERFACES(GenericPlugin)

public:
	bool InitialisePlugin();
	bool DeInitialisePlugin();

	QString GetId();	
	QString GetName();
	QString GetDescription();
};

#endif //VIDEO_JS_PLUGIN
