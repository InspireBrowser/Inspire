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

#include <QCoreApplication>
#include <QSettings>
#include <QNetworkInterface>

#include "RemoteCommand.h"
#include "MainWindow.h"
#include "JSBinding/ISystemJSBinding.h"

/*! @brief Creates the CommandServer
 *  @param parent The parent object
 */
CommandServer::CommandServer(QObject *parent) :
    QTcpServer(parent)
{
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetVersionCommand(RemoteCommand*)));
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetMacAddressCommand(RemoteCommand*)));
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetConfigCommand(RemoteCommand*)));
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetOsCommand(RemoteCommand*)));
}

/*! @brief Instructs the CommandServer to start listening
 *  @returns Whether the command server could start listening or not
 */
bool CommandServer::startListening() {
    return this->listen(QHostAddress::Any, 4774);
}

/*! @brief Instructs the CommandServer to stop listening */
void CommandServer::stopListening() {
    this->close();
}

/*! @brief Processes a RemoteCommand
 *  @param command The command to process
 */
void CommandServer::processCommand(RemoteCommand *command)
{
    emit commandReceived(command);
}

/*! @brief Called when the server receives an incoming connection
 *  @param handle The connection handle to use
 */
void CommandServer::incomingConnection(int handle)
{
    CommandSocket* socket = new CommandSocket(this);
    socket->setSocketDescriptor(handle);
}

/*! @brief Handles the GET_VERSION command
 *  @param command The command to handle
 */
void CommandServer::handleGetVersionCommand(RemoteCommand *command)
{
    if(command->command() != "GET_VERSION")
        return;

    command->setResponse(true, QCoreApplication::applicationVersion());
}

/*! @brief Handles the GET_OS command
 *  @param command The command to handle
 */
void CommandServer::handleGetOsCommand(RemoteCommand *command)
{
    if(command->command() != "GET_OS")
        return;

    MainWindow* window = qobject_cast<MainWindow*>(this->parent());
    QString os = window->webView()->iSystem()->operatingSystem();
    command->setResponse(true, os);
}

/*! @brief Handles the GET_MAC_ADDRESS command
 *  @param command The command to handle
 */
void CommandServer::handleGetMacAddressCommand(RemoteCommand *command)
{
    if(command->command() != "GET_MAC_ADDRESS")
        return;

    int adapterNumber = -1;
    if(command->parameterCount() == 0)
        adapterNumber = 0;
    else if(command->parameterCount() == 1) {
        QString indexParam = command->parameter(0);
        bool isOk = false;
        adapterNumber = indexParam.toInt(&isOk);
        if(!isOk)
            return command->setResponse(false, "index parameter is not an integer");
    }
    else
        return command->setResponse(false, "Too many parameters");

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    if(adapterNumber >= 0 && adapterNumber < interfaces.count()){
        return command->setResponse(true, interfaces[adapterNumber].hardwareAddress());
    }

    QString s;
    return command->setResponse(false, s.sprintf("Adapter %d does not exist", adapterNumber));
}

/*! @brief Handles the GET_CONFIG command
 *  @param command The command to handle
 */
void CommandServer::handleGetConfigCommand(RemoteCommand *command)
{
    if(command->command() != "GET_CONFIG")
        return;

    if(command->parameterCount() < 1)
        return command->setResponse(false, "Config variable name not specified");
    else if(command->parameterCount() > 1)
        return command->setResponse(false, "Too many parameters");

    QString name = command->parameter(0);

    QSettings settings;

    command->setResponse(true, settings.value(name).toString());
}
