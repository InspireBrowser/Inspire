#include <QtPlugin>
#include "CommandServerPlugin.h"

#include <QxtLogger>

bool CommandServerPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());

	#warning TODO: Start the command server listening
	#warning TODO: Add Config check to see if we should start listening
	return true;
}

bool CommandServerPlugin::DeInitialisePlugin()
{
	#warning TODO: Stop the command server listening
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
