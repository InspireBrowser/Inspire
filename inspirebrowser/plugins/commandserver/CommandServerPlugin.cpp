#include <QtPlugin>
#include "CommandServerPlugin.h"

#include <QxtLogger>

bool CommandServerPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());
	return true;
}

bool CommandServerPlugin::DeInitialisePlugin()
{
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
