#include <QtPlugin>
#include "VideoJSPlugin.h"

#include <QxtLogger>

bool VideoJSPlugin::InitialisePlugin()
{
	qxtLog->info("Initialising " + this->GetName());
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
