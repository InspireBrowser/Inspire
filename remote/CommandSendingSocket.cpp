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
 * Filename: CommandSendingSocket.cpp
 * Class: CommandSendingSocket
 * Description: Handles the of a remote command and handling of the
 *              response received
 */

#include "CommandSendingSocket.h"
#include "RemoteCommand.h"

/*! @brief Constructs a CommandSendingSocket
 *  @param parent The parent object
 */
CommandSendingSocket::CommandSendingSocket(RemoteCommand* command, QHostAddress clientAddress, int clientPort, QObject* parent) :
    QTcpSocket(parent),
    _command(command),
    _clientAddress(clientAddress),
    _clientPort(clientPort)
{
    connect(this, SIGNAL(connected()), this, SLOT(sendCommand()));
    connect(this, SIGNAL(disconnected()), this, SLOT(connectionClosedByClient()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readResponse()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorOccured(QAbstractSocket::SocketError)));
}

/*! @brief Creates the command data and sends it to the client
 *         Called once the socket manages to connect to the client
 */
void CommandSendingSocket::sendCommand()
{
    this->write(_command->generatePayload());
};

/*! @brief Handles the closing of the connection from the client
 *         Called when the server closes connection
 */
void CommandSendingSocket::connectionClosedByClient()
{
    this->close();
};

/*! @brief Reads the response from the client and displays it */
void CommandSendingSocket::readResponse()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_7);

    forever {
        if(_nextBlockSize == 0) {
            if(this->bytesAvailable() < sizeof(quint16)) {
                break;
            }

            in >> _nextBlockSize;
        }

        if(_nextBlockSize == 0xFFFF) {
            this->close();
            break;
        }

        if(this->bytesAvailable() < _nextBlockSize) {
            break;
        }

        bool success;
        QString response;

        //read in the response
        in >> success >> response;
        _nextBlockSize = 0;

        //close socket and call the signals
        this->close();
        if(success) {
            emit completed(_clientAddress, response);
        } else
            { emit failed(_clientAddress, response); }
    }
};

/*! @brief Called when an error occurs in the communication with the client
 *  @param The error that occured
 */
void CommandSendingSocket::errorOccured(QAbstractSocket::SocketError error)
{
    QString errorString = this->errorString();
    this->close();
    emit failed(_clientAddress, errorString);
};

/*! @brief Sends the command to the client */
void CommandSendingSocket::send()
{
    this->connectToHost(_clientAddress, _clientPort);
    _nextBlockSize = 0;
};
