/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * Copyright (C) 2010  mike
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
 * Filename: ISystemJSBinding.cpp
 * Class: ISystemJSBinding
 * Description: Handles JavaScript interactions with the system
 * Created: 14/11/2010
 * ChangeLog:
 *     14/11/2010 - mike - Initial Creation
 */

#include "ISystemJSBinding.h"

#include <QDate>
#include <QSettings>
#include <QNetworkInterface>
#include <QProcess>
#include <QxtLogger>

#include "OsUtils.h"
#include "Settings.h"

/*! @brief Constructor for creating the System Javascript Binding
 *  @param  parent  The parent object
 */
ISystemJSBinding::ISystemJSBinding(QObject *parent) :
        QObject(parent)
{
}

/*! @brief Returns the Operating system that Inspire Browser is running on
 *  @return The Operating system that Inspire Browser is running on
 */
QString ISystemJSBinding::operatingSystem() const
{
    qxtLog->trace(Q_FUNC_INFO);
    return OsUtils::operatingSystemName();
}

/*! @brief Returns the number of network adapters the system has
 *  @return The number of network adapters the system has
 */
int ISystemJSBinding::adapterCount() const
{
    qxtLog->trace(Q_FUNC_INFO);

    return QNetworkInterface::allInterfaces().count();
}

/*! @brief Sets the value of a configuration option
 *         Stores the value in the settings file and writes it to disk. Changes become active
 *         at different times depending on the option. The only way to guarantee that an item
 *         is active is to restart the browser
 *
 *  @param name The name of the configuration option to set
 *  @param value The value to set the configuration option to
 */
void ISystemJSBinding::SetConfig(const QString name, const QVariant value)
{
    qxtLog->trace(Q_FUNC_INFO);

    QSettings settings;

    if(value.type() == QVariant::Bool)
        settings.setValue(name, value.toBool());
    else if(value.type() == QVariant::Date)
        settings.setValue(name, value.toDate());
    else if(value.type() == QVariant::DateTime)
        settings.setValue(name, value.toDateTime());
    else if(value.type() == QVariant::Double)
        settings.setValue(name, value.toDouble());
    else if(value.type() == QVariant::Int)
        settings.setValue(name, value.toInt());
    else if(value.type() == QVariant::List)
        settings.setValue(name, value.toList());
    else if(value.type() == QVariant::Map)
        settings.setValue(name, value.toMap());
    else if(value.type() == QVariant::String)
        settings.setValue(name, value.toString());
    else
        settings.setValue(name, value);
}

/*! @brief Returns the value of a configuration option
 *  @param name The name of the configuration option to return
 *  @return The value of the configuration option
 */
QVariant ISystemJSBinding::GetConfig(const QString name) const
{
    qxtLog->trace(Q_FUNC_INFO);

    QVariant value = SETTING(name, QVariant());

    if(value.type() == QVariant::Bool)
        return value.toBool();
    else if(value.type() == QVariant::Date)
        return value.toDate();
    else if(value.type() == QVariant::DateTime)
        return value.toDateTime();
    else if(value.type() == QVariant::Double)
        return value.toDouble();
    else if(value.type() == QVariant::Int)
        return value.toInt();
    else if(value.type() == QVariant::List)
        return value.toList();
    else if(value.type() == QVariant::Map)
        return value.toMap();
    else if(value.type() == QVariant::String)
        return value.toString();
    else
        return value;
}

/*! @brief Gets an adapters name
 *  @param adapterNumber The index of the adapter to get the name for
 *  @return The name of the adapter
 */
QString ISystemJSBinding::GetAdapterName(const int adapterNumber)
{
    qxtLog->trace(Q_FUNC_INFO);

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    if(adapterNumber >= 0 && adapterNumber < interfaces.count()){
        return interfaces[adapterNumber].humanReadableName();
    }

    return "";
}

/*! @brief Gets an adapters IPv4 Address
 *  @param adapterNumber The index of the adapter to get the IPv4 Address of
 *  @return The IPv4 Address of the adapter
 */
QString ISystemJSBinding::GetIpV4Address(const int adapterNumber)
{
    qxtLog->trace(Q_FUNC_INFO);

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    if(adapterNumber >= 0 && adapterNumber < interfaces.count()){
        QList<QNetworkAddressEntry> addresses = interfaces[adapterNumber].addressEntries();
        for(int i=0; i<addresses.count(); i++)
        {
            if(addresses[i].ip().protocol() == QAbstractSocket::IPv4Protocol)
                return addresses[i].ip().toString();
        }
    }

    return "";
}

/*! @brief Gets an adapters IPv6 Address
 *  @param adapterNumber The index of the adapter to get the IPv6 Address of
 *  @return The IPv6 Address of the adapter
 */
QString ISystemJSBinding::GetIpV6Address(const int adapterNumber)
{
    qxtLog->trace(Q_FUNC_INFO);

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    if(adapterNumber >= 0 && adapterNumber < interfaces.count()){
        QList<QNetworkAddressEntry> addresses = interfaces[adapterNumber].addressEntries();
        for(int i=0; i<addresses.count(); i++)
        {
            if(addresses[i].ip().protocol() == QAbstractSocket::IPv6Protocol)
                return addresses[i].ip().toString();
        }
    }

    return "";
}

/*! @brief Gets an adapters Hardware Address
 *  @param adapterNumber The index of the adapter to get the Hardware Address of
 *  @return The Hardware Address of the adapter
 */
QString ISystemJSBinding::GetHardwareAddress(const int adapterNumber)
{
    qxtLog->trace(Q_FUNC_INFO);

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    if(adapterNumber >= 0 && adapterNumber < interfaces.count()){
        return interfaces[adapterNumber].hardwareAddress();
    }

    return "";
}

/*! @brief Closes Inspire Browser
 *  @param returnCode The value to return as the return code
 */
void ISystemJSBinding::Quit(int returnCode)
{
    qxtLog->trace(Q_FUNC_INFO);

    QCoreApplication::exit(returnCode);
}
