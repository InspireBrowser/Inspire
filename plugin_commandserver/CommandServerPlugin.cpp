#include "CommandServerPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "CommandServer.h"
#include "Settings.h"

CommandServerPlugin::CommandServerPlugin(QObject* parent) :
    QObject(parent), GenericPlugin()
{
    Settings::Get()->addSetting(this->GetId(), Settings::Title, this->GetName() + " Plugin");
    Settings::Get()->addSetting(this->GetId() + "-disable", Settings::Boolean, "Disable the " + this->GetName() + " Plugin");
}

bool CommandServerPlugin::InitialisePlugin()
{
    if(SETTING(this->GetId() + "-disable", false).toBool()) {
        qxtLog->info("Not initializing plugin as option " + this->GetId() + "-disable has been set");
        return false;
    }

    qxtLog->info("Initialising " + this->GetName());

#warning TODO: Add Config check to see if we should start listening

    _server = new CommandServer(this);
    _server->startListening();

    return true;
}

bool CommandServerPlugin::DeInitialisePlugin()
{
    _server->stopListening();
    return true;
}

QString CommandServerPlugin::GetId()
{
    return "commandserver";
}

QString CommandServerPlugin::GetName()
{
    return "Command Server";
}

QString CommandServerPlugin::GetDescription()
{
    return "Plugin that handles the sending of commands to the browser from remote machines";
}

Q_EXPORT_PLUGIN2(commandserver, CommandServerPlugin);
