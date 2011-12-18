/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Filename: BrowserJSPlugin.cpp
 * Class: BrowserJSPlugin
 * Description: The plugin class that when initialised provides a JavaScript
 *              Binding for interactions with the browser.
 */
#include "BrowserJSPlugin.h"

#include <QtPlugin>
#include <QxtLogger>

#include "IBrowserJSBinding.h"
#include "PluginManager.h"
#include "Settings.h"

BrowserJSPlugin::BrowserJSPlugin(QObject* parent) :
    QObject(parent), GenericPlugin()
{
    Settings::Get()->addSetting(this->GetId(), Settings::Title, this->GetName() + " Plugin");
    Settings::Get()->addSetting(this->GetId() + "-disable", Settings::Boolean, "Disable the " + this->GetName() + " Plugin");
}

bool BrowserJSPlugin::InitialisePlugin()
{
    if(SETTING(this->GetId() + "-disable", false).toBool()) {
        qxtLog->info("Not initializing plugin as option " + this->GetId() + "-disable has been set");
        return false;
    }

    qxtLog->info("Initialising " + this->GetName());

    IBrowserJSBinding* javascriptBinding = new IBrowserJSBinding(this);
    javascriptBinding->setMainWindow(this->pluginManager()->GetMainWindow());
    javascriptBinding->Initialise();
    this->pluginManager()->GetWebView()->addJavascriptBinding("IBrowser", javascriptBinding);

    return true;
}

bool BrowserJSPlugin::DeInitialisePlugin()
{
    return true;
}

QString BrowserJSPlugin::GetId()
{
    return "browserjs";
}

QString BrowserJSPlugin::GetName()
{
    return "Browser JS Binding";
}

QString BrowserJSPlugin::GetDescription()
{
    return "Plugin that provides the iBrowser JavaScript Binding";
}

Q_EXPORT_PLUGIN2(browserjs, BrowserJSPlugin);
