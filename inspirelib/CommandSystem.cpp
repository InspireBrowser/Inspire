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
 * Filename: CommandSystem.cpp
 * Class: CommandSystem
 * Description: Handles the receiving of commands and passes them off to the
 *              recievers that have registered with the system
 */
#include "CommandSystem.h"

#include <QCoreApplication>
#include <QNetworkInterface>

#include "RemoteCommand.h"
#include "OsUtils.h"
#include "Settings.h"

CommandSystem::CommandSystem(QObject* parent) : QObject(parent)
{
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetVersionCommand(RemoteCommand*)));
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetMacAddressCommand(RemoteCommand*)));
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetConfigCommand(RemoteCommand*)));
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleSetConfigCommand(RemoteCommand*)));
    connect(this, SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleGetOsCommand(RemoteCommand*)));
}

/*! @brief Processes a RemoteCommand
 *  @param command The command to process
 */
void CommandSystem::processCommand(RemoteCommand* command)
{
    emit commandReceived(command);
}

/*! @brief Handles the GET_VERSION command
 *  @param command The command to handle
 */
void CommandSystem::handleGetVersionCommand(RemoteCommand* command)
{
    if(command->command() != "GET_VERSION") {
        return;
    }

    command->setResponse(true, QCoreApplication::applicationVersion());
}

/*! @brief Handles the GET_OS command
 *  @param command The command to handle
 */
void CommandSystem::handleGetOsCommand(RemoteCommand* command)
{
    if(command->command() != "GET_OS") {
        return;
    }

    QString os = OsUtils::operatingSystemName();
    command->setResponse(true, os);
}

/*! @brief Handles the GET_MAC_ADDRESS command
 *  @param command The command to handle
 */
void CommandSystem::handleGetMacAddressCommand(RemoteCommand* command)
{
    if(command->command() != "GET_MAC_ADDRESS") {
        return;
    }

    int adapterNumber = -1;
    if(command->parameterCount() == 0) {
        adapterNumber = 0;
    } else if(command->parameterCount() == 1) {
        QString indexParam = command->parameter(0);
        bool isOk = false;
        adapterNumber = indexParam.toInt(&isOk);
        if(!isOk) {
            return command->setResponse(false, "index parameter is not an integer");
        }
    } else {
        return command->setResponse(false, "Too many parameters");
    }

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    if(adapterNumber >= 0 && adapterNumber < interfaces.count()) {
        return command->setResponse(true, interfaces[adapterNumber].hardwareAddress());
    }

    QString s;
    return command->setResponse(false, s.sprintf("Adapter %d does not exist", adapterNumber));
}

/*! @brief Handles the GET_CONFIG command
 *  @param command The command to handle
 */
void CommandSystem::handleGetConfigCommand(RemoteCommand* command)
{
    if(command->command() != "GET_CONFIG") {
        return;
    }

    if(command->parameterCount() < 1) {
        return command->setResponse(false, "Config variable name not specified");
    } else if(command->parameterCount() > 1) {
        return command->setResponse(false, "Too many parameters");
    }

    QString name = command->parameter(0);

    command->setResponse(true, SETTING(name, "").toString());
}

/*! @brief Handles the SET_CONFIG command
 *  @param command The command to handle
 */
void CommandSystem::handleSetConfigCommand(RemoteCommand* command)
{
    if(command->command() != "SET_CONFIG") {
        return;
    }

    if(command->parameterCount() < 1) {
        return command->setResponse(false, "Config variable name not specified");
    }
    if(command->parameterCount() < 2) {
        return command->setResponse(false, "Config variable value not specified");
    } else if(command->parameterCount() > 3) {
        return command->setResponse(false, "Too many parameters");
    }

    QString name = command->parameter(0);
    QString value = command->parameter(1);
    bool persist = command->parameter(2) == "true";

    bool completed = Settings::Get()->setValueFromUser(name, value, persist);
    command->setResponse(completed, completed ? "Done" : "Couldn't set config value");
}
