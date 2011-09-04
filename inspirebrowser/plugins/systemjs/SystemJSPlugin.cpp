#include "SystemJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "ISystemJSBinding.h"

bool SystemJSPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());

        this->GetWebView()->addJavascriptBinding("ISystem", new ISystemJSBinding(this));

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
