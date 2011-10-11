#include "VideoJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "IVideoJSBinding.h"
#include "PluginManager.h"

bool VideoJSPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());

	IVideoJSBinding* javascriptBinding = new IVideoJSBinding(this);
	javascriptBinding->setMainWindow(this->pluginManager()->GetMainWindow());
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

Q_EXPORT_PLUGIN2(videojs, VideoJSPlugin);
