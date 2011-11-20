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
