#ifndef COMMAND_SERVER_PLUGIN
#define COMMAND_SERVER_PLUGIN

#include "GenericPlugin.h"

class CommandServerPlugin : public QObject, GenericPlugin
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

#endif //COMMAND_SERVER_PLUGIN
