#include "BrowserJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "IBrowserJSBinding.h"

bool BrowserJSPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());

        this->GetWebView()->addJavascriptBinding("IBrowser", new IBrowserJSBinding(this));

	return true;
}

bool BrowserJSPlugin::DeInitialisePlugin()
{
	return true;
}

QString BrowserJSPlugin::GetId()
{
	return "browserjs";
}

QString BrowserJSPlugin::GetName()
{
	return "Browser JS Binding";
}

QString BrowserJSPlugin::GetDescription()
{
	return "Plugin that provides the iBrowser JavaScript Binding";
}

Q_EXPORT_PLUGIN2(browserjs, BrowserJSPlugin);
