#ifndef COMMAND_SERVER_PLUGIN
#define COMMAND_SERVER_PLUGIN

#include "GenericPlugin.h"

class CommandServer;

class CommandServerPlugin : public GenericPlugin
{
	Q_OBJECT
	Q_INTERFACES(GenericPlugin)

public:
	bool InitialisePlugin();
	bool DeInitialisePlugin();

	QString GetId();	
	QString GetName();
	QString GetDescription();

private:
        CommandServer* _server;
};

#endif //COMMAND_SERVER_PLUGIN
