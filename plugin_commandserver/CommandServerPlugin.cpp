/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Filename: CommandServerPlugin.cpp
 * Class: CommandServerPlugin
 * Description: The plugin class that when initialised provides a socket
 *              that listens for commands sent via the Inspire Remote
 */
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

    Settings::Get()->addSetting("commandserver-port", Settings::Integer, "The port number to list to [default 4774]");
    Settings::Get()->addSetting("commandserver-bind-address", Settings::String, "The address to bind to [default 0.0.0.0]");
}

bool CommandServerPlugin::InitialisePlugin()
{
    if(SETTING(this->GetId() + "-disable", false).toBool()) {
        qxtLog->info("Not initializing plugin as option " + this->GetId() + "-disable has been set");
        return false;
    }

    qxtLog->info("Initialising " + this->GetName());

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
