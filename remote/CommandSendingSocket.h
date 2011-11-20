/*
 * InspireRemote is an open source application for remote controlling
 * the Inspire Browser
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
 * Filename: CommandSendingSocket.h
 * Class: CommandSendingSocket
 * Description: Handles the sending of a remote command and handling of the
 *              response received
 */

#ifndef COMMANDSENDINGSOCKET_H
#define COMMANDSENDINGSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

class RemoteCommand;

/*! @brief Handles the sending of a command to a client */
class CommandSendingSocket : public QTcpSocket
{
    Q_OBJECT
private:
    /*! @brief The command to send */
    RemoteCommand* _command;

    /*! @brief The address of the client to connect to */
    QHostAddress _clientAddress;

    /*! @brief The port to connect to */
    int _clientPort;

    /*! @brief The size of the block to read */
    quint16 _nextBlockSize;

public:
    /*! @brief Constructs a CommandSendingSocket
     *  @param parent The parent object
     */
    explicit CommandSendingSocket(RemoteCommand* command, QHostAddress clientAddress, int clientPort, QObject* parent = 0);

    /*! @brief Returns the address of the inspire client to connect to
     *  @return The address of the inspire client to connect to
     */
    QHostAddress clientAddress() const {
        return _clientAddress;
    }
    /*! @brief Sets The address of the inspire client to connect to
     *  @param server The address of the inspire client to connect to
     */
    void setClientAddress(const QHostAddress server) {
        _clientAddress = server;
    }

    /*! @brief Returns the port to connect to
     *  @return The port to connect to
     */
    int clientPort() const {
        return _clientPort;
    }
    /*! @brief Sets the port to connect to
     *  @param port The port to connect to
     */
    void setClientPort(const int port) {
        _clientPort = port;
    }

signals:
    void completed(QHostAddress client, QString response);
    void failed(QHostAddress client, QString error);

private slots:
    /*! @brief Creates the command data and sends it to the client
     *         Called once the socket manages to connect to the client
     */
    void sendCommand();

    /*! @brief Handles the closing of the connection from the client
     *         Called when the server closes connection
     */
    void connectionClosedByClient();


    /*! @brief Reads the response from the client and displays it */
    void readResponse();

    /*! @brief Called when an error occurs in the communication with the client
     *  @param The error that occured
     */
    void errorOccured(QAbstractSocket::SocketError error);

public slots:
    /*! @brief Sends the command to the client */
    void send();
};

#endif // COMMANDSENDINGSOCKET_H
