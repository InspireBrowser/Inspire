#ifndef BROWSER_JS_PLUGIN
#define BROWSER_JS_PLUGIN

#include <QObject>
#include "GenericPlugin.h"

class BrowserJSPlugin : public QObject, public GenericPlugin
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

#endif //BROWSER_JS_PLUGIN
