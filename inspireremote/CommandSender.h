/*
 * InspireRemote is an open source application for remote controlling 
 * the Inspire Browser
 *
 * Copyright (C) 2011  mike
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
 * Filename: CommandSender.h
 * Class: CommandSender
 * Description: Handles the sending of a remote command to a single or multiple
 *              clients
 * Created: 23/01/2011
 * ChangeLog:
 *     23/01/2011 - mike - Initial Creation
 */

#ifndef COMMANDSENDER_H
#define COMMANDSENDER_H

#include <QObject>
#include <QHostAddress>

class RemoteCommand;
class CommandSendingSocket;

/*! @brief Handles the sending of a command to multiple clients */
class CommandSender : public QObject
{
    Q_OBJECT
private:
    RemoteCommand* _command;
    /*! @brief The addresses of the clients to connect to */
    QList<QHostAddress> _clientAddresses;

    /*! @brief The port to connect to */
    int _clientPort;

    /*!	@brief Stores the sockets we are using to connect to the clients */
    QList<CommandSendingSocket*> _clientSockets;

public:
    /*! @brief Constructs a CommandSender with the command to send
     *  @param parent The parent object
     */
    explicit CommandSender(RemoteCommand* command, QObject* parent = 0);

    /*! @brief Adds a client to the list of clients to send to
     *  @param client The client address to send the command to
     */
    void addClient(const QHostAddress client) { _clientAddresses.append(client); }
    /*! @brief Returns a client from the list of clients
     *  @param index The index of the client to return
     *  @return The client at that index
     */
    QHostAddress client(const int index) { return _clientAddresses.at(index); }
    /*! @brief Returns the number of clients we're sending to
     *  @return The number of clients we're sending to
     */
    int clientCount() const { return _clientAddresses.count(); }

    /*! @brief Returns the port to connect to
     *  @return The port to connect to
     */
    int clientPort() const { return _clientPort; }
    /*! @brief Sets the port to connect to
     *  @param port The port to connect to
     */
    void setClientPort(const int port) { _clientPort = port; }

private:
    void checkForCompletion();

signals:

public slots:
    /*! @brief Initiates the sending of the command to all the clients */
    void send();

private slots:    
    void clientCompleted(QHostAddress client, QString response);
    void clientFailed(QHostAddress client, QString error);

};

#endif // COMMANDSENDER_H
