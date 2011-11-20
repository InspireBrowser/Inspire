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
#include "CommandSender.h"

#include <QCoreApplication>
#include <QDebug>

#include "RemoteCommand.h"
#include "CommandSendingSocket.h"

/*! @brief Constructs a CommandSender with the command to send
 *  @param parent The parent object
 */
CommandSender::CommandSender(RemoteCommand* command, QObject* parent) :
    QObject(parent),
    _command(command)
{
}

void CommandSender::send()
{
    foreach(QHostAddress client, _clientAddresses) {
        CommandSendingSocket* socket = new CommandSendingSocket(_command, client, this->clientPort(), this);
        connect(socket, SIGNAL(completed(QHostAddress, QString)), this, SLOT(clientCompleted(QHostAddress, QString)));
        connect(socket, SIGNAL(failed(QHostAddress, QString)), this, SLOT(clientFailed(QHostAddress, QString)));
        socket->send();
        _clientSockets.append(socket);
    }
}

void CommandSender::clientCompleted(QHostAddress client, QString response)
{
    qDebug() << client.toString() << ":" << "true" << ":" << response;
    this->checkForCompletion();
}

void CommandSender::clientFailed(QHostAddress client, QString error)
{
    qDebug() << client.toString() << ":" << "false" << ":" << error;
    this->checkForCompletion();
}

void CommandSender::checkForCompletion()
{
    foreach(CommandSendingSocket * socket, _clientSockets) {
        if(socket->isOpen()) {
            return;
        }
    }

    QCoreApplication::exit(0);
}
