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
 * Filename: RemoteCommand.cpp
 * Class: RemoteCommand
 * Description: Models a command that can be sent to Inspire and handled
 *              by the CommandSystem
 */
#include "RemoteCommand.h"
#include <QDebug>
#include <QCoreApplication>

RemoteCommand::RemoteCommand(QObject* parent) :
    QObject(parent),
    _hasResponse(false),
    _responseSuccess(false)
{
}

/*! @brief Sets the response to be sent to the server
 *  @param success Whether the command was a success or not
 *  @param responseText The text to return with the response
 */
void RemoteCommand::setResponse(const bool success, const QString responseText)
{
    _hasResponse = true;
    _responseSuccess = success;
    _responseText = responseText;
}

/*! @brief Generates and returns the key to include in the command
 *  @return The generated key
 */
QString RemoteCommand::generateKey() const
{
#warning TODO: Add generation of key if configured to encrypt commands
    return "";
};

/*! @brief Generate the data payload to send to the client
 *  @return The ByteArray containing the payload
 */
QByteArray RemoteCommand::generatePayload()
{
    _organisationName = QCoreApplication::organizationName();
    _version = QCoreApplication::applicationVersion();
    _key = this->generateKey();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);

    out << quint16(0) << this->organisationName() << this->version() << this->command() << this->key()
        << this->parameterCount();

    for(int i = 0; i < parameterCount(); i++) {
        out << parameter(i);
    }

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    return block;
}

/*! @brief Returns whether the command is valid for this system to run
 *  @return Whether the command is valid for this system to run
 */
bool RemoteCommand::verifyCommand()
{
    if(this->organisationName() != QCoreApplication::organizationName()) {
#warning TODO: Add logging that the command comes from a different organisation
        return false;
    }

    if(this->key() != this->generateKey()) {
#warning TODO: Add logging that the commands key was incorrect
        return false;
    }

    return true;
}

/*! @brief Parses the payload and fills out the command object
 *  @param payload The data to parse
 */
void RemoteCommand::parsePayload(QDataStream& payload)
{
    //prepare the variables to store the command components
    QString command;
    QString organisationName;
    QString version;
    QString key;
    int paramCount;

    //read in the command, key and param count
    payload >> organisationName >> version >> command >> key >> paramCount;

    this->setCommand(command);
    this->setOrganisationName(organisationName);
    this->setVersion(version);
    this->setKey(key);

    //now read in paramCount's worth of string parameters
    for(int i = 0; i < paramCount; i++) {
        QString parameter;
        payload >> parameter;
        this->addParameter(parameter);
    }
}
