#include "BrowserJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "IBrowserJSBinding.h"
#include "PluginManager.h"
#include "Settings.h"

BrowserJSPlugin::BrowserJSPlugin(QObject* parent) :
	QObject(parent), GenericPlugin()
{
	Settings::Get()->addSetting(this->GetId(), Settings::Title, this->GetName() + " Plugin");
	Settings::Get()->addSetting(this->GetId() + "-disable", Settings::Boolean, "Disable the " + this->GetName() + " Plugin");
}

bool BrowserJSPlugin::InitialisePlugin()
{
	if(SETTING(this->GetId() + "-disable", false).toBool()) {
		qxtLog->info("Not initializing plugin as option " + this->GetId() + "-disable has been set");
		return false;
    }

    qxtLog->info("Initialising " + this->GetName());

	IBrowserJSBinding* javascriptBinding = new IBrowserJSBinding(this);
	javascriptBinding->setMainWindow(this->pluginManager()->GetMainWindow());
	javascriptBinding->Initialise();
	this->pluginManager()->GetWebView()->addJavascriptBinding("IBrowser", javascriptBinding);

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
