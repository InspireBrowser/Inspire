#include "Settings.h"

#include <QDebug>
#include <getopt.h>
#include <QVectorIterator>

#include "Settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    this->addSetting("general", SETTING_TITLE, "General Settings");
    this->addSetting("help", SETTING_BOOL, "Display help information on the available options");

    this->addSetting("logging", SETTING_TITLE, "Logging Settings");
    this->addSetting("log-level", SETTING_INT, "The level to verbosity in logging, 1-7 [default 2]");
    this->addSetting("log-file", SETTING_STRING, "The file location to log information to");

    this->addSetting("application", SETTING_TITLE, "Application Settings");
    this->addSetting("application-show-fullscreen", SETTING_BOOL, "Show the application fullscreen");
    this->addSetting("application-width", SETTING_INT, "The width of the application window (if not fullscreen)");
    this->addSetting("application-height", SETTING_INT, "The height of the application window (if not fullscreen)");

    this->addSetting("browser", SETTING_TITLE, "Browser Settings");
    this->addSetting("browser-homepage", SETTING_STRING, "The browser homepage");
    this->addSetting("browser-developer-mode", SETTING_BOOL, "Whether to enable developer mode in the browser or not");
    this->addSetting("browser-restrict-js-api", SETTING_BOOL, "Whether to only enable the extended JavaScript API for certain websites");
    this->addSetting("browser-allowed-api-urls", SETTING_STRINGLIST, "A list of URL patterns that if matched enable the extended JavaScript API");
}

void Settings::setValueFromUser(const QString &key, const QString &value, const bool persistSetting)
{
    #warning TODO: Implement setValueFromUser
}

void Settings::setValue(const QString &key, const QVariant &value, const bool persistSetting)
{
    this->_settings.insert(key, value);
    if(persistSetting)
        this->_savedSettings.setValue(key, value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue) const
{
    if(this->_settings.contains(key))
        return this->_settings.value(key);
    else
        return this->_savedSettings.value(key, defaultValue);
}

/*! @brief Adds a setting to the list of settings
 *  @param settingName the name of the setting
 *  @param type The type of the setting
 *  @param description Description of the setting
 */
void Settings::addSetting(QString name, SettingType type, QString description)
{
    SettingInfo info;

    info.name = name;
    info.type = type;
    info.description = description;

    this->_definedSettings.append(info);
}

/*! @brief Adds a setting to the list of plugin settings
 *  @param settingName the name of the setting
 *  @param type The type of the setting
 *  @param description Description of the setting
 */
void Settings::addPluginSetting(QString name, SettingType type, QString description)
{
    SettingInfo info;

    info.name = name;
    info.type = type;
    info.description = description;

    this->_definedPluginSettings.append(info);
}

/*! @brief Removes a setting from the list of plugin settings
 *  @param settingName the name of the setting
 */
void Settings::removePluginSetting(QString name)
{
    //this->_definedPluginSettings.remove(name);
}

/*! @brief Parse the command line arguments needed by lib inspire
 *  @param argc The number of command line arguments
 *  @param argv The command line arguments to parse
 *  @return Whether an error occured parsing the arguments
 */
bool Settings::parseInspireArguments(int argc, char *argv[])
{
	return false;
}

Settings* Settings::_instance = 0;

Settings* Settings::Get()
{
    if(_instance == 0)
        _instance = new Settings();

    return _instance;
}
