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
 * Filename: PluginManager.cpp
 * Class: PluginManager
 * Description: Responsible for the loading and initialisation of plugins
 */
#include "PluginManager.h"

#include <QApplication>
#include <QPluginLoader>
#include <QxtLogger>

#include "GenericPlugin.h"
#include "MainWindow.h"
#include "InspireWebView.h"
#include "Settings.h"

PluginManager::PluginManager(QObject* parent) :
    QObject(parent)
{
}

void PluginManager::LoadPlugins()
{
    if(SETTING("plugins-disable", false).toBool()) {
        qxtLog->info("Plugin loading disabled");
        return;
    }

    QDir pluginsDir = this->GetPluginsDir();

    qxtLog->info("Scanning for plugins in: " + pluginsDir.absolutePath());
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        this->LoadPluginFromFile(pluginsDir.absoluteFilePath(fileName));
    }
}

void PluginManager::InitialisePlugins()
{
    QHashIterator<QString, GenericPlugin*> i(_plugins);
    while (i.hasNext()) {
        i.next();
        qxtLog->debug("Initialising Plugin " + i.key());
        if(!i.value()->InitialisePlugin()) {
            qxtLog->warning("Initialisation of plugin " + i.key() + " failed");
        }
    }
}

bool PluginManager::IsPluginLoaded(QString id)
{
    return _plugins.contains(id);
}

GenericPlugin* PluginManager::GetPlugin(QString id)
{
    if(this->IsPluginLoaded(id)) {
        return _plugins.value(id);
    } else {
        return 0;
    }
}

bool PluginManager::UnloadPlugin(QString id)
{
    qxtLog->info("Trying to unload plugin " + id);
    if(this->IsPluginLoaded(id)) {
        GenericPlugin* plugin = _plugins.value(id);
        if(plugin->DeInitialisePlugin()) {
            _plugins.remove(id);
            plugin = NULL;

            if(_pluginLoaders.value(id)->unload()) {
                qxtLog->info("Plugin '" + id + "' unloaded");
                _pluginLoaders.remove(id);
            } else {
                qxtLog->error("Plugin '" + id + "' could not be unloaded");
            }

            return true;
        } else {
            qxtLog->error("Couldn't deinitialise plugin '" + id + "'. Not unloading.");
            return false;
        }
    } else {
        qxtLog->error("Plugin '" + id + "' is not loaded. Not unloading.");
        return true;
    }
}

MainWindow* PluginManager::GetMainWindow()
{
    MainWindow* window;
    QObject* item = (QObject*)this;
    do {
        item = item->parent();
        window = qobject_cast<MainWindow*>(item);
        if(window) {
            return window;
        }
    } while(item->parent() != 0);

    return 0;
}

InspireWebView* PluginManager::GetWebView()
{
    MainWindow* window = this->GetMainWindow();
    if(!window) {
        return 0;
    }

    return window->webView();
}

QDir PluginManager::GetPluginsDir()
{
    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release") {
        pluginsDir.cdUp();
    }
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif

    if(!pluginsDir.cd("plugins")) {
#if defined(Q_OS_UNIX)
        //if the local plugins dir doesn't exist try the global one
        QDir pluginsDir(PLUGINDIR);
        if(pluginsDir.exists()) {
            return pluginsDir;
        }
#endif
        qxtLog->error("Plugins directory does not exist");
    }

    return pluginsDir;
}

bool PluginManager::LoadPluginFromFile(QString fileName)
{
    qxtLog->info("Attempting to load " + fileName);

    if(!QLibrary::isLibrary(fileName)) {
        qxtLog->error(fileName + " is not library, not loading.");
        return false;
    }

    QPluginLoader* pluginLoader = new QPluginLoader(fileName);
    if(!pluginLoader->load()) {
        qxtLog->error("Failed to load plugin " + fileName + ": " + pluginLoader->errorString());
        return false;
    }

    QObject* plugin = pluginLoader->instance();
    if (plugin) {
        plugin->setParent(this);
        GenericPlugin* pluginInstance = qobject_cast<GenericPlugin*>(plugin);
        pluginInstance->setPluginManager(this);
        if (pluginInstance) {
            QString id = pluginInstance->GetId();
            _plugins[id] = pluginInstance;
            _pluginLoaders[id] = pluginLoader;
            return true;
        } else {
            qxtLog->error("Plugin not a GenericPlugin object");
            return false;
        }
    }

    qxtLog->error("Couldn't create instance of plugin");
    return false;
}
