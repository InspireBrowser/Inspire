#include "CommandServerPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "CommandServer.h"

bool CommandServerPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());

	#warning TODO: Add Config check to see if we should start listening

	_server = new CommandServer(this);
	_server->startListening();

	return true;
}

bool CommandServerPlugin::DeInitialisePlugin()
{
        _server->stopListening();
	return true;
}

QString CommandServerPlugin::GetId()
{
	return "commandserver";
}

QString CommandServerPlugin::GetName()
{
	return "Command Server";
}

QString CommandServerPlugin::GetDescription()
{
	return "Plugin that handles the sending of commands to the browser from remote machines";
}

Q_EXPORT_PLUGIN2(commandserver, CommandServerPlugin);
