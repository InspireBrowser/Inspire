#include "Settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent)
{
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

Settings* Settings::_instance = 0;

Settings* Settings::Get()
{
    if(_instance == 0)
        _instance = new Settings();

    return _instance;
}
