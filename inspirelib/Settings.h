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

    explicit Settings(QObject *parent = 0);

    bool setValueFromUser(const QString &key, const QString &value, const bool persistSetting = false);
    void setValue(const QString &key, const QVariant &value, const bool persistSetting = false);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
    bool isSet(const QString &key);

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
    bool setValueOfType(const QString &key, SettingType type, const QString &value, const bool persistSetting = false);

signals:

public slots:

};

#endif // SETTINGS_H
