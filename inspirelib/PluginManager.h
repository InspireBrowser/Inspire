#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QObject>
#include <QHash>
#include <QDir>

class GenericPlugin;
class MainWindow;
class InspireWebView;

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

    QDir GetPluginsDir();
    bool LoadPluginFromFile(QString fileName);
};

#endif // PLUGIN_MANAGER_H
