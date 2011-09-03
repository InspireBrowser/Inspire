#include "GenericPlugin.h"

#include "PluginManager.h"
#include "MainWindow.h"
#include "InspireWebView.h"

GenericPlugin::GenericPlugin(QObject* parent) :
        QObject(parent)
{
}

PluginManager* GenericPlugin::GetPluginManager()
{
	return qobject_cast<PluginManager*>(this->parent());
}

InspireWebView* GenericPlugin::GetWebView()
{
    PluginManager* manager = this->GetPluginManager();
    if(!manager)
        return 0;

    MainWindow* window = manager->GetMainWindow();
    if(!window)
        return 0;

    return window->webView();
}
