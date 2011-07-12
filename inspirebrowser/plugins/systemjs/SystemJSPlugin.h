#ifndef SYSTEM_JS_PLUGIN
#define SYSTEM_JS_PLUGIN

#include <QObject>
#include "GenericPlugin.h"

class SystemJSPlugin : public QObject, GenericPlugin
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

#endif //SYSTEM_JS_PLUGIN
