/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Filename: ISystemJSBinding.h
 * Class: ISystemJSBinding
 * Description: Handles JavaScript interactions with the system
 */

#ifndef ISYSTEMJSBINDING_H
#define ISYSTEMJSBINDING_H

#include "JavascriptBinding.h"
#include <QCoreApplication>
#include <QxtLogger>

/*! @brief  Provides the JavaScript Binding for interfacing with the System
 *          Class that provides the JavaScript Binding for interfacing with the System
 *          it provides methods for querying the network adapters in the computer
 */
class ISystemJSBinding : public QObject, public JavascriptBinding
{
    Q_OBJECT

public:
    /*! @brief Constructor for creating the System Javascript Binding
     *  @param  parent  The parent object
     */
    explicit ISystemJSBinding(QObject* parent = 0);

    /*! @brief Returns the version of Inspire Browser running
     *  @return the version of InspireBrowser running
     */
    QString version() const {
        qxtLog->trace(Q_FUNC_INFO);
        return QCoreApplication::applicationVersion();
    }
    /*! @brief Property for retrieving the version of Inspire Browser running */
    Q_PROPERTY(QString version READ version CONSTANT);

    /*! @brief Returns the Operating system that Inspire Browser is running on
     *  @return The Operating system that Inspire Browser is running on
     */
    QString operatingSystem() const;
    /*! @brief Property for retrieving the operating system that Inspire Browser is running on */
    Q_PROPERTY(QString operatingSystem READ operatingSystem CONSTANT);

    /*! @brief Returns the number of network adapters the system has
     *  @return The number of network adapters the system has
     */
    int adapterCount() const;
    /*! @brief Property for retrieving the number of network adapters the system has */
    Q_PROPERTY(int adapterCount READ adapterCount STORED false);

public slots:
    /*! @brief Sets the value of a configuration option
     *         Stores the value in the settings file and writes it to disk. Changes become active
     *         at different times depending on the option. The only way to guarantee that an item
     *         is active is to restart the browser
     *
     *  @param name The name of the configuration option to set
     *  @param value The value to set the configuration option to
     */
    void SetConfig(const QString name, const QVariant value);

    /*! @brief Returns the value of a configuration option
     *  @param name The name of the configuration option to return
     *  @return The value of the configuration option
     */
    QVariant GetConfig(const QString name) const;

    /*! @brief Gets an adapters name
     *  @param adapterNumber The index of the adapter to get the name for
     *  @return The name of the adapter
     */
    QString GetAdapterName(const int adapterNumber);

    /*! @brief Gets an adapters IPv4 Address
     *  @param adapterNumber The index of the adapter to get the IPv4 Address of
     *  @return The IPv4 Address of the adapter
     */
    QString GetIpV4Address(const int adapterNumber);

    /*! @brief Gets an adapters IPv6 Address
     *  @param adapterNumber The index of the adapter to get the IPv6 Address of
     *  @return The IPv6 Address of the adapter
     */
    QString GetIpV6Address(const int adapterNumber);

    /*! @brief Gets an adapters Hardware Address
     *  @param adapterNumber The index of the adapter to get the Hardware Address of
     *  @return The Hardware Address of the adapter
     */
    QString GetHardwareAddress(const int adapterNumber);

    /*! @brief Closes Inspire Browser
     *  @param returnCode The value to return as the return code
     */
    void Quit(int returnCode = 0);
};

#endif // ISYSTEMBINDING_H
