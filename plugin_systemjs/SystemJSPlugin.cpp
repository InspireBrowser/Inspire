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
 * Filename: SystemJSPlugin.cpp
 * Class: SystemJSPlugin
 * Description: The plugin class that when initialised provides a JavaScript
 *              Binding for interactions with the system
 */
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
