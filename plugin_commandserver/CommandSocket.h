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
 * Filename: CommandSocket.h
 * Class: CommandSocket
 * Description: CommandSocket handles the receiving of commands from the
 *              network, processes them and passes them off to the server
 * Created: 26/01/2011
 * ChangeLog:
 *     26/01/2011 - mike - Initial Creation
 */

#ifndef COMMANDSOCKET_H
#define COMMANDSOCKET_H

#include <QTcpSocket>

class RemoteCommand;

class CommandSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CommandSocket(QObject *parent = 0);

private slots:
    void readCommand();

private:
    quint16 _nextBlockSize;

    void processCommand(RemoteCommand* command);
    void sendResponse(bool success, QString response);

signals:

public slots:

};

#endif // COMMANDSOCKET_H
