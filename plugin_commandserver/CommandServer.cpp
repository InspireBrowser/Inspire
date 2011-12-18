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
 * Filename: CommandServer.cpp
 * Class: CommandServer
 * Description: Command Server listens for commands sent by InspireRemote
 *              and then emits signals when they arrive so listeners can
 *              handle them
 */

#include "CommandServer.h"

#include "CommandSocket.h"
#include "RemoteCommand.h"
#include "CommandSystem.h"
#include "GenericPlugin.h"
#include "MainWindow.h"
#include "PluginManager.h"
#include "Settings.h"

/*! @brief Creates the CommandServer
 *  @param parent The parent object
 */
CommandServer::CommandServer(QObject* parent) :
    QTcpServer(parent)
{
}

/*! @brief Instructs the CommandServer to start listening
 *  @returns Whether the command server could start listening or not
 */
bool CommandServer::startListening()
{
    int portNumber = SETTING("commandserver-port", 4774).toInt();

    if(SETTING_SET("commandserver-bind-address")) {
        QHostAddress address(SETTING("commandserver-bind-address", "0.0.0.0").toString());
        return this->listen(address, portNumber);
    } else {
        return this->listen(QHostAddress::Any, portNumber);
    }
}

/*! @brief Instructs the CommandServer to stop listening */
void CommandServer::stopListening()
{
    this->close();
}

/*! @brief Processes a RemoteCommand
 *  @param command The command to process
 */
void CommandServer::processCommand(RemoteCommand* command)
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
