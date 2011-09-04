#include "VideoJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "IVideoJSBinding.h"

bool VideoJSPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());

        this->GetWebView()->addJavascriptBinding("IVideo", new IVideoJSBinding(this));

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
