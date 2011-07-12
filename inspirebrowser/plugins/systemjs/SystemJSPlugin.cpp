#include <QtPlugin>
#include "SystemJSPlugin.h"

#include <QxtLogger>

bool SystemJSPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());
	return true;
}

bool SystemJSPlugin::DeInitialisePlugin()
{
	return true;
}

QString SystemJSPlugin::GetId()
{
	return "systemjs";
}

QString SystemJSPlugin::GetName()
{
	return "System JS Binding";
}

QString SystemJSPlugin::GetDescription()
{
	return "Plugin that provides the iSystem JavaScript Binding";
}

Q_EXPORT_PLUGIN2(systemjs, SystemJSPlugin);
