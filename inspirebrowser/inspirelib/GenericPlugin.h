#ifndef GENERIC_PLUGIN_H
#define GENERIC_PLUGIN_H

#include <QObject>
#include <QString>

#include "InspireWebView.h"

class PluginManager;
class MainWindow;

class GenericPlugin : public QObject
{
    Q_OBJECT

public:
	explicit GenericPlugin(QObject* parent = 0);
	virtual ~GenericPlugin() {}

	virtual bool InitialisePlugin() = 0;
	virtual bool DeInitialisePlugin() { return true; }

	virtual QString GetId() = 0;
	virtual QString GetName() = 0;
	virtual QString GetDescription() = 0;

    PluginManager* GetPluginManager();
    MainWindow* GetMainWindow();
    InspireWebView* GetWebView();
};

Q_DECLARE_INTERFACE(GenericPlugin, "org.inspirebrowser.Plugins.GenericPlugin/1.0");

#endif
