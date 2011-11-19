#include "VideoJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "IVideoJSBinding.h"
#include "PluginManager.h"
#include "Settings.h"

VideoJSPlugin::VideoJSPlugin(QObject* parent) :
	QObject(parent), GenericPlugin()
{
	Settings::Get()->addSetting(this->GetId(), Settings::Title, this->GetName() + " Plugin");
	Settings::Get()->addSetting(this->GetId() + "-disable", Settings::Boolean, "Disable the " + this->GetName() + " Plugin");
}

bool VideoJSPlugin::InitialisePlugin()
{
	if(SETTING(this->GetId() + "-disable", false).toBool()) {
		qxtLog->info("Not initializing plugin as option " + this->GetId() + "-disable has been set");
		return false;
	}

	qxtLog->info("Initialising " + this->GetName());

	IVideoJSBinding* javascriptBinding = new IVideoJSBinding(this);
	javascriptBinding->setMainWindow(this->pluginManager()->GetMainWindow());
	javascriptBinding->Initialise();
	this->pluginManager()->GetWebView()->addJavascriptBinding("IVideo", javascriptBinding);

	return true;
}

bool VideoJSPlugin::DeInitialisePlugin()
{
	return true;
}

QString VideoJSPlugin::GetId()
{
	return "videojs";
}

QString VideoJSPlugin::GetName()
{
	return "Video JS Binding";
}

QString VideoJSPlugin::GetDescription()
{
	return "Plugin that provides the iVideo JavaScript Binding";
}

Q_EXPORT_PLUGIN2(videojs_vlc, VideoJSPlugin);
