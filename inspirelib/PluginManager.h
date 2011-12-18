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
 * Filename: PluginManager.h
 * Class: PluginManager
 * Description: Responsible for the loading and initialisation of plugins
 */
#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QObject>
#include <QHash>
#include <QDir>

class GenericPlugin;
class MainWindow;
class InspireWebView;
class QPluginLoader;

class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject* parent = 0);

    void LoadPlugins();
    void InitialisePlugins();

    bool IsPluginLoaded(QString id);
    GenericPlugin* GetPlugin(QString id);

    bool UnloadPlugin(QString id);

    MainWindow* GetMainWindow();
    InspireWebView* GetWebView();
private:
    QHash<QString, GenericPlugin*> _plugins;
    QHash<QString, QPluginLoader*> _pluginLoaders;

    QDir GetPluginsDir();
    bool LoadPluginFromFile(QString fileName);
};

#endif // PLUGIN_MANAGER_H
