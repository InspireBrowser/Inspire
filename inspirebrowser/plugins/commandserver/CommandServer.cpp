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
 * Filename: CommandServer.cpp
 * Class: CommandServer
 * Description: Command Server listens for commands sent by InspireRemote
 *              and then emits signals when they arrive so listeners can
 *              handle them
 * Created: 26/01/2011
 * ChangeLog:
 *     26/01/2011 - mike - Initial Creation
 */

#include "CommandServer.h"

#include "CommandSocket.h"
#include "RemoteCommand.h"
#include "CommandSystem.h"
#include "GenericPlugin.h"
#include "MainWindow.h"
#include "PluginManager.h"

/*! @brief Creates the CommandServer
 *  @param parent The parent object
 */
CommandServer::CommandServer(QObject *parent) :
    QTcpServer(parent)
{
}

/*! @brief Instructs the CommandServer to start listening
 *  @returns Whether the command server could start listening or not
 */
bool CommandServer::startListening()
{
    return this->listen(QHostAddress::Any, 4774);
}

/*! @brief Instructs the CommandServer to stop listening */
void CommandServer::stopListening()
{
    this->close();
}

/*! @brief Processes a RemoteCommand
 *  @param command The command to process
 */
void CommandServer::processCommand(RemoteCommand *command)
{
    GenericPlugin* plugin = qobject_cast<GenericPlugin*>(this->parent());
	plugin->pluginManager()->GetMainWindow()->commandSystem()->processCommand(command);
}

/*! @brief Called when the server receives an incoming connection
 *  @param handle The connection handle to use
 */
void CommandServer::incomingConnection(int handle)
{
    CommandSocket* socket = new CommandSocket(this);
    socket->setSocketDescriptor(handle);
}
