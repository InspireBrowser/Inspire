#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

#define SETTING(key, defaultValue) Settings::Get()->value(key, defaultValue)

class Settings : public QObject
{
    Q_OBJECT
private:
    static Settings* _instance;

    QSettings _savedSettings;
    QHash<QString, QVariant> _settings;
    QHash<QString, QString> _settingInfo;

public:
    explicit Settings(QObject *parent = 0);

    void setValue(const QString &key, const QVariant &value, const bool persistSetting = false);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

    static Settings* Get();
signals:

public slots:

};

#endif // SETTINGS_H
