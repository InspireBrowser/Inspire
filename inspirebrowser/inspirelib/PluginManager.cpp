#include "PluginManager.h"

#include <QApplication>
#include <QPluginLoader>
#include <QxtLogger>

#include "GenericPlugin.h"
#include "MainWindow.h"

PluginManager::PluginManager(QObject* parent) :
        QObject(parent)
{
}

void PluginManager::LoadPlugins()
{
	QDir pluginsDir = this->GetPluginsDir();

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
        if(!i.value()->InitialisePlugin())
            qxtLog->warning("Initialisation of plugin " + i.key() + "failed");
    }
}

bool PluginManager::IsPluginLoaded(QString id)
{
	return _plugins.contains(id);
}

GenericPlugin* PluginManager::GetPlugin(QString id)
{
	if(this->IsPluginLoaded(id))
		return _plugins.value(id);
	else
		return 0;
}

bool PluginManager::UnloadPlugin(QString id)
{
	qxtLog->info("Trying to unload plugin " + id);
	if(this->IsPluginLoaded(id)) {
		GenericPlugin* plugin = this->GetPlugin(id);
		if(plugin->DeInitialisePlugin()) {
			#warning TODO: Actually unload plugin
			return true;
		}
		else {
			qxtLog->error("Couldn't deinitialise plugin '" + id + "'. Not unloading.");
			return false;
		}
	}
	else {
		qxtLog->error("Plugin '" + id + "' is not loaded. Not unloading.");
		return true;
	}
}

MainWindow* PluginManager::GetMainWindow()
{
    MainWindow *window;
    QObject* item = (QObject*)this;
    do
    {
        item = item->parent();
        window = qobject_cast<MainWindow*>(item);
        if(window)
            return window;
    }
    while(item->parent() != 0);

    return 0;
}

QDir PluginManager::GetPluginsDir()
{
	QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
	if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
		pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
	if (pluginsDir.dirName() == "MacOS") {
		pluginsDir.cdUp();
		pluginsDir.cdUp();
		pluginsDir.cdUp();
	}
#endif

	if(!pluginsDir.cd("plugins")) {
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

	QPluginLoader pluginLoader(fileName);
	if(!pluginLoader.load()) {
		qxtLog->error("Failed to load plugin " + fileName + ": " + pluginLoader.errorString());
		return false;
	}

	QObject *plugin = pluginLoader.instance();
	if (plugin) {
		plugin->setParent(this);
		GenericPlugin* pluginInstance = qobject_cast<GenericPlugin*>(plugin);
                if (pluginInstance) {
			QString id = pluginInstance->GetId();
			_plugins[id] = pluginInstance;
			return true;
		} else {
			qxtLog->error("Plugin not a GenericPlugin object");
			return false;
		}
	}

	qxtLog->error("Couldn't create instance of plugin");
	return false;
}
