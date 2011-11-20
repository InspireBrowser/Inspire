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
 * Filename: GenericPlugin.h
 * Class: GenericPlugin
 * Description: The abstract class that plugins must implement to be
 *              picked up by the PluginManager.
 */
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
    virtual bool DeInitialisePlugin() {
        return true;
    }

    virtual QString GetId() = 0;
    virtual QString GetName() = 0;
    virtual QString GetDescription() = 0;

    PluginManager* pluginManager() {
        return _pluginManager;
    }
    void setPluginManager(PluginManager* pluginManager) {
        _pluginManager = pluginManager;
    }
};

Q_DECLARE_INTERFACE(GenericPlugin, "org.inspirebrowser.Plugins.GenericPlugin/1.0")

#endif
