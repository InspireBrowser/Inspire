#ifndef GENERIC_PLUGIN_H
#define GENERIC_PLUGIN_H

#include <QObject>
#include <QString>

#include "InspireWebView.h"

class PluginManager;
class MainWindow;

class GenericPlugin
{    
private:
	PluginManager* _pluginManager;

public:
	virtual ~GenericPlugin() {}

	virtual bool InitialisePlugin() = 0;
	virtual bool DeInitialisePlugin() { return true; }

	virtual QString GetId() = 0;
	virtual QString GetName() = 0;
	virtual QString GetDescription() = 0;

	PluginManager* pluginManager() { return _pluginManager; }
	void setPluginManager(PluginManager *pluginManager) { _pluginManager = pluginManager; }
};

Q_DECLARE_INTERFACE(GenericPlugin, "org.inspirebrowser.Plugins.GenericPlugin/1.0")

#endif