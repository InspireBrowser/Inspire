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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QVector>
#include <QStringList>

#define SETTING(key, defaultValue) Settings::Get()->value(key, defaultValue)
#define SETTING_SET(key) Settings::Get()->isSet(key)

class QxtCommandOptions;

class Settings : public QObject
{
    Q_OBJECT

public:
    enum SettingType {
        Integer,
        String,
        Boolean,
        StringList,
        Title
    };

private:
    struct SettingInfo {
        QString name;
        SettingType type;
        QString description;
        QStringList aliases;
    };

    static Settings* _instance;

    QSettings _savedSettings;
    QHash<QString, QVariant> _settings;

    QVector<SettingInfo> _settingInfo;

public:

    explicit Settings(QObject* parent = 0);

    bool setValueFromUser(const QString& key, const QString& value, const bool persistSetting = false);
    void setValue(const QString& key, const QVariant& value, const bool persistSetting = false);
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
    bool isSet(const QString& key);

    static Settings* Get();

    /*! @brief Returns information on all the command line options
     *  @return The command line options
     */
    QxtCommandOptions* getSettingInformation();

    /*! @brief Parse the command line arguments
     *  @return Any errors generated whilst parsing the argument
     */
    QString parseArguments();

    /*! @brief Adds a setting to the list of settings
     *  @param settingName the name of the setting
     *  @param type The type of the setting
     *  @param aliases A list of aliases for the setting
     *  @param description Description of the setting
     */
    void addSetting(QString settingName, SettingType type, QString description, QStringList aliases = QStringList());

    /*! @brief Removes a setting from the list of plugin settings
     *  @param settingName the name of the setting
     */
    void removeSetting(QString name);

private:
    bool setValueOfType(const QString& key, SettingType type, const QString& value, const bool persistSetting = false);

signals:

public slots:

};

#endif // SETTINGS_H
