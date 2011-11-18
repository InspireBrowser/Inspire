#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QVector>

#define SETTING(key, defaultValue) Settings::Get()->value(key, defaultValue)

enum SettingType { SETTING_INT, SETTING_STRING, SETTING_BOOL, SETTING_STRINGLIST, SETTING_TITLE };

struct SettingInfo {
    QString name;
    SettingType type;
    QString description;
};

class Settings : public QObject
{
    Q_OBJECT
private:
    static Settings* _instance;

    QSettings _savedSettings;
    QHash<QString, QVariant> _settings;
    QHash<QString, QString> _settingInfo;

    QVector<SettingInfo> _definedSettings;
    QVector<SettingInfo> _definedPluginSettings;

public:
    explicit Settings(QObject *parent = 0);

    void setValueFromUser(const QString &key, const QString &value, const bool persistSetting = false);
    void setValue(const QString &key, const QVariant &value, const bool persistSetting = false);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

    static Settings* Get();

    /*! @brief Parse the command line arguments needed by lib inspire
     *  @param argc The number of command line arguments
     *  @param argv The command line arguments to parse
     *  @return Whether an error occured parsing the arguments
     */
    bool parseInspireArguments(int argc, char* argv[]);

    /*! @brief Parses the command line argument needed by plugins
     *  @param argc The number of command line arguments
     *  @param argv The command line arguments to parse
     *  @return Whether an error occured parsing the arguments
     */
    bool parsePluginArguments(int argc, char* argv[]);

    /*! @brief Adds a setting to the list of plugin settings
     *  @param settingName the name of the setting
     *  @param type The type of the setting
     *  @param description Description of the setting
     */
    void addPluginSetting(QString name, SettingType type, QString description);

    /*! @brief Removes a setting from the list of plugin settings
     *  @param settingName the name of the setting
     */
    void removePluginSetting(QString name);

    QVector<SettingInfo> settingInfo() { return this->_definedSettings; }
    QVector<SettingInfo> pluginSettingInfo() { return this->_definedPluginSettings; }

private:
    /*! @brief Adds a setting to the list of settings
     *  @param settingName the name of the setting
     *  @param type The type of the setting
     *  @param description Description of the setting
     */
    void addSetting(QString settingName, SettingType type, QString description);

signals:

public slots:

};

#endif // SETTINGS_H
