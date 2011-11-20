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
 * Filename: Settings.cpp
 * Class: Settings
 * Description: Handles the settings for inspire and it's plugin. Settings
 *              can be stored persistently to the file system or can be set
 *              just for this session by command line arguments, from
 *              JavaScript or from the Command System. This class handles
 *              all of this including the parsing of command line arguments.
 */
#include "Settings.h"

#include <QDebug>
#include <QVectorIterator>
#include <QxtCommandOptions>
#include <QxtLogger>
#include <QDir>

#include "Settings.h"

Settings::Settings(QObject* parent) :
    QObject(parent)
{
    this->addSetting("general", Settings::Title, "General Settings");
    this->addSetting("help", Settings::Boolean, "Display help information on the available options", QStringList("h"));

    this->addSetting("logging", Settings::Title, "Logging Settings");
    this->addSetting("log-level", Settings::Integer, "The level to verbosity in logging, 1-7 [default 2]");
    this->addSetting("log-file", Settings::String, "The file location to log information to");

    this->addSetting("application", Settings::Title, "Application Settings");
    this->addSetting("application-show-fullscreen", Settings::Boolean, "Show the application fullscreen");
    this->addSetting("application-width", Settings::Integer, "The width of the application window (if not fullscreen)");
    this->addSetting("application-height", Settings::Integer, "The height of the application window (if not fullscreen)");

    this->addSetting("browser", Settings::Title, "Browser Settings");
    this->addSetting("browser-homepage", Settings::String, "The browser homepage");
    this->addSetting("browser-developer-mode", Settings::Boolean, "Whether to enable developer mode in the browser or not");
    this->addSetting("browser-restrict-js-api", Settings::Boolean, "Whether to only enable the extended JavaScript API for certain websites");
    this->addSetting("browser-allowed-api-urls", Settings::StringList, "A list of URL patterns that if matched enable the extended JavaScript API");

    this->addSetting("plugins", Settings::Title, "Plugin Settings");
    this->addSetting("plugins-disable", Settings::Boolean, "Disables the loading of plugins");
}

bool Settings::setValueFromUser(const QString& key, const QString& value, const bool persistSetting)
{
    QVectorIterator<SettingInfo> i(_settingInfo);
    while (i.hasNext()) {
        SettingInfo info = i.next();
        if(info.name == key) {
            return this->setValueOfType(key, info.type, value, persistSetting);
        }
    }

    qxtLog->error("Setting with name " + key + " not known");
    return false;
}

bool Settings::setValueOfType(const QString& key, SettingType type, const QString& value, const bool persistSetting)
{
    QString stringValue;
    int intValue;
    bool isOk = false;

    switch(type) {
        case Settings::Boolean:
            stringValue = value.toLower();
            if(stringValue == "1" || stringValue == "true") {
                this->setValue(key, true, persistSetting);
                return true;
            }
            if(stringValue == "0" || stringValue == "false") {
                this->setValue(key, false, persistSetting);
                return true;
            }
            qxtLog->error("Invalid value '" + value + "' for Setting type Boolean");
            return false;

        case Settings::Integer:
            intValue = value.toInt(&isOk);

            if(isOk) {
                this->setValue(key, intValue, persistSetting);
            }

            return isOk;

        case Settings::String:
            this->setValue(key, value, persistSetting);
            return true;

        case Settings::StringList:
            this->setValue(key, value.split(",", QString::SkipEmptyParts), persistSetting);
            return true;

        case Settings::Title:
            qxtLog->error("Cannot set value of type 'Title'");
            return false;

        default:
            qxtLog->error("Unknown type: " + type);
            return false;
    }
}

void Settings::setValue(const QString& key, const QVariant& value, const bool persistSetting)
{
    this->_settings.insert(key, value);
    if(persistSetting) {
        this->_savedSettings.setValue(key, value);
    }
}

QVariant Settings::value(const QString& key, const QVariant& defaultValue) const
{
    if(this->_settings.contains(key)) {
        return this->_settings.value(key);
    } else {
        return this->_savedSettings.value(key, defaultValue);
    }
}

bool Settings::isSet(const QString& key)
{
    if(this->_settings.contains(key)) {
        return true;
    }

    return this->_savedSettings.contains(key);
}

/*! @brief Adds a setting to the list of settings
 *  @param settingName the name of the setting
 *  @param type The type of the setting
 *  @param description Description of the setting
 */
void Settings::addSetting(QString name, SettingType type, QString description, QStringList aliases)
{
    SettingInfo info;

    info.name = name;
    info.type = type;
    info.description = description;
    info.aliases = aliases;

    this->_settingInfo.append(info);
}

/*! @brief Removes a setting from the list of plugin settings
 *  @param settingName the name of the setting
 */
void Settings::removeSetting(QString name)
{
    for(int i=0; i < _settingInfo.size(); i++) {
        if(_settingInfo.at(i).name == name) {
            _settingInfo.remove(i);
            return;
        }
    }
}

QxtCommandOptions* Settings::getSettingInformation()
{
    QxtCommandOptions* options = new QxtCommandOptions();

    QVectorIterator<SettingInfo> i(_settingInfo);
    while (i.hasNext()) {
        SettingInfo info = i.next();

        switch(info.type) {
            case Settings::Title:
                options->addSection(info.description);
                break;
            case Settings::Boolean:
                if(info.aliases.count() > 0) {
                    options->add(info.name, info.description, QxtCommandOptions::NoValue);
                } else {
                    options->add(info.name, info.description, QxtCommandOptions::ValueOptional);
                }
                break;
            case Settings::Integer:
            case Settings::String:
            case Settings::StringList:
                options->add(info.name, info.description, QxtCommandOptions::ValueRequired);
                break;
        }

        QStringListIterator j(info.aliases);
        while(j.hasNext()) {
            options->alias(info.name, j.next());
        }
    }

    return options;
}

/*! @brief Parse the command line arguments needed by lib inspire
 *  @param argc The number of command line arguments
 *  @param argv The command line arguments to parse
 *  @return Whether an error occured parsing the arguments
 */
QString Settings::parseArguments()
{
    QxtCommandOptions* options = this->getSettingInformation();
    options->parse(QCoreApplication::arguments());

    QVectorIterator<SettingInfo> i(_settingInfo);
    while (i.hasNext()) {
        SettingInfo info = i.next();

        if(info.type == Settings::Title || !options->count(info.name)) {
            continue;
        }

        QString value = options->value(info.name).toString();

        if(info.type == Settings::Boolean && value == "") {
            value = "true";
        }

        if(!this->setValueFromUser(info.name, value)) {
            QString name = QDir(QCoreApplication::applicationFilePath()).dirName();
            return name + ": Invalid value for Option '" + info.name + "'";
        }
    }

    return options->getUnrecognizedWarning();
}

Settings* Settings::_instance = 0;

Settings* Settings::Get()
{
    if(_instance == 0) {
        _instance = new Settings();
    }

    return _instance;
}
