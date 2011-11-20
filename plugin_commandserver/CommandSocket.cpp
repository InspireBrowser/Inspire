/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
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
 * Filename: CommandSocket.cpp
 * Class: CommandSocket
 * Description: CommandSocket handles the receiving of commands from the
 *              network, processes them and passes them off to the server
 * Created: 26/01/2011
 * ChangeLog:
 *     26/01/2011 - mike - Initial Creation
 */

#include "CommandSocket.h"

#include <QStringList>
#include <QCoreApplication>

#include "CommandServer.h"
#include "RemoteCommand.h"

CommandSocket::CommandSocket(QObject* parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readCommand()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    _nextBlockSize = 0;
}

void CommandSocket::readCommand()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_7);

    //if this is the first time we've been ready to read
    if(_nextBlockSize == 0) {
        //check to see if we can read the int which tells us the size
        if(bytesAvailable() < sizeof(quint16)) {
            return;
        }
        //if so, read it in
        in >> _nextBlockSize;
    }

    //check to see if enough bytes are available to get the whole of the message
    if(bytesAvailable() < _nextBlockSize) {
        return;
    }

    RemoteCommand* command = new RemoteCommand(this);
    command->parsePayload(in);

    //check that the command is valid
    if(command->verifyCommand()) {
        //now we have the command send it off to be processed
        this->processCommand(command);
    } else {
        this->sendResponse(false, "Invalid Command");
    }
    this->close();
}

void CommandSocket::processCommand(RemoteCommand* command)
{
    CommandServer* server = qobject_cast<CommandServer*>(this->parent());
    server->processCommand(command);

    if(!command->hasResponse()) {
        command->setResponse(false, "Unknown command");
    }

    this->sendResponse(command->responseSuccessfull(), command->responseText());
}

void CommandSocket::sendResponse(bool success, QString response)
{
    //now send the response back
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    //add a 16 bit int and then the response
    out << quint16(0) << success << response;
    //calculate the size of the response and overwrite the first in in the response
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    this->write(block);
}
