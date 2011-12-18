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
 * Filename: RemoteCommand.h
 * Class: RemoteCommand
 * Description: Models a command that can be sent to Inspire and handled
 *              by the CommandSystem
 */
#ifndef REMOTECOMMAND_H
#define REMOTECOMMAND_H

#include <QObject>
#include <QStringList>

class RemoteCommand : public QObject
{
    Q_OBJECT
private:
    /*! @brief The command to send */
    QString _command;

    /*! @brief The name of the organisation the Command is for */
    QString _organisationName;

    /*! @brief The version of the software the command was created from */
    QString _version;

    /*! @brief The key for verifying the data */
    QString _key;

    /*! @brief A list of parameters for the command */
    QStringList _parameters;

    /*! @brief Whether a handler has responded to the command */
    bool _hasResponse;

    /*! @brief Whether the response was successful */
    bool _responseSuccess;

    /*! @brief The response text to send */
    QString _responseText;

    /*! @brief Generates and returns the key to include in the command
     *  @return The generated key
     */
    QString generateKey() const;

    /*! @brief Sets the version of software the command was created for
     *  @param version The version of software the command was created for
     */
    void setVersion(const QString version) {
        _version = version;
    }

    /*! @brief Sets the organisation name for the command
     *  @param organisationName The organisation name for the command
     */
    void setOrganisationName(const QString organisationName) {
        _organisationName = organisationName;
    }

    /*! @brief Sets the key used to verify the command
     *  @param key The key used to verify the command
     */
    void setKey(const QString key) {
        _key = key;
    }

public:
    /*! @brief Constructs a RemoteCommand
     *  @param parent The parent object
     */
    explicit RemoteCommand(QObject* parent = 0);

    /*! @brief Returns the command to send
     *  @return The command to send
     */
    QString command() const {
        return _command;
    }
    /*! @brief Sets the command to send
     *  @param command The command to send
     */
    void setCommand(const QString command) {
        _command = command;
    }
    /*! @brief Property for setting and getting the command */
    Q_PROPERTY(QString command READ command WRITE setCommand);

    /*! @brief Returns the organisation name for the command
     *  @return The organisation name for the command
     */
    QString organisationName() const {
        return _organisationName;
    }
    /*! @brief Property for accessing the organisation name of the command */
    Q_PROPERTY(QString organisationName READ organisationName);

    /*! @brief Returns the version of software the command was created for
     *  @return The version of software the command was created for
     */
    QString version() const {
        return _version;
    }
    /*! @brief Property for accessing the version of software the command was created for */
    Q_PROPERTY(QString version READ version);

    /*! @brief Returns the key that is used to verify the command
     *  @return The key used to verify the command
     */
    QString key() const {
        return _key;
    }
    /*! @brief Property for accessing the key */
    Q_PROPERTY(QString key READ key);

    /*! @brief Returns the list of parameters to send
     *  @return The list of parameters to send
     */
    QStringList parameters() {
        return _parameters;
    }
    /*! @brief Returns a parameter from the list of parameters that's being sent
     *  @param index The index of the parameter
     *  @return The parameter requested
     */
    QString parameter(int index) const {
        return _parameters.at(index);
    }
    /*! @brief Adds a parameter to the list of parameters to send
     *  @param param The parameter to add to the list
     */
    void addParameter(const QString param) {
        _parameters.append(param);
    }
    /*! @brief Returns the count of the parameters to be sent
     *  @return The count of parameters to send
     */
    int parameterCount() const {
        return _parameters.count();
    }

    /*! @brief Sets the response to be sent to the server
     *  @param success Whether the command was a success or not
     *  @param responseText The text to return with the response
     */
    void setResponse(const bool success, const QString responseText);
    /*! @brief Returns whether there is a response for the command
     *  @return Whether there is a response for the command
     */
    bool hasResponse() const {
        return _hasResponse;
    }
    /*! @brief Returns whether the response to the command is successful or not
     *  @return Whether the response to the command is successful or not
     */
    bool responseSuccessfull() const {
        return _responseSuccess;
    }
    /*! @brief Returns the response text
     *  @return The response text
     */
    QString responseText() const {
        return _responseText;
    }

    /*! @brief Generate the data payload to send to the client
     *  @return The ByteArray containing the payload
     */
    QByteArray generatePayload();

    /*! @brief Parses the payload and fills out the command object
     *  @param payload The data to parse
     */
    void parsePayload(QDataStream& payload);

    /*! @brief Returns whether the command is valid for this system to run
     *  @return Whether the command is valid for this system to run
     */
    bool verifyCommand();

signals:

private:
};

#endif // REMOTECOMMAND_H
