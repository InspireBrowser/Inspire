#include "SystemJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "ISystemJSBinding.h"
#include "PluginManager.h"

bool SystemJSPlugin::InitialisePlugin()
{
    qxtLog->info("Initialising " + this->GetName());

    ISystemJSBinding* javascriptBinding = new ISystemJSBinding(this);
    javascriptBinding->setMainWindow(this->pluginManager()->GetMainWindow());
	javascriptBinding->Initialise();
    this->pluginManager()->GetWebView()->addJavascriptBinding("ISystem", javascriptBinding);

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
