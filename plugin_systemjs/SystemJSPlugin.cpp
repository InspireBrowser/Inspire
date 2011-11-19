#include "SystemJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "ISystemJSBinding.h"
#include "PluginManager.h"
#include "Settings.h"

SystemJSPlugin::SystemJSPlugin(QObject* parent) :
    QObject(parent), GenericPlugin()
{
    Settings::Get()->addSetting(this->GetId(), Settings::Title, this->GetName() + " Plugin");
    Settings::Get()->addSetting(this->GetId() + "-disable", Settings::Boolean, "Disable the " + this->GetName() + " Plugin");
}

bool SystemJSPlugin::InitialisePlugin()
{
    if(SETTING(this->GetId() + "-disable", false).toBool()) {
        qxtLog->info("Not initializing plugin as option " + this->GetId() + "-disable has been set");
        return false;
    }

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
