/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
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
 * Filename: CommandSystem.h
 * Class: CommandSystem
 * Description: Handles the receiving of commands and passes them off to the
 *              recievers that have registered with the system
 */
#ifndef COMMANDSYSTEM_H
#define COMMANDSYSTEM_H

#include <QObject>

class RemoteCommand;

class CommandSystem : public QObject
{
    Q_OBJECT

public:
    explicit CommandSystem(QObject* parent = 0);

    /*! @brief Processes a RemoteCommand
     *  @param command The command to process
     */
    void processCommand(RemoteCommand* command);

signals:
    /*! @brief Emitted to indicate that a command has been received
     *  @param command The command that has been received
     */
    void commandReceived(RemoteCommand* command);

private slots:
    /*! @brief Handles the GET_VERSION command
     *  @param command The command to handle
     */
    void handleGetVersionCommand(RemoteCommand* command);

    /*! @brief Handles the GET_OS command
     *  @param command The command to handle
     */
    void handleGetOsCommand(RemoteCommand* command);

    /*! @brief Handles the GET_MAC_ADDRESS command
     *  @param command The command to handle
     */
    void handleGetMacAddressCommand(RemoteCommand* command);

    /*! @brief Handles the GET_CONFIG command
     *  @param command The command to handle
     */
    void handleGetConfigCommand(RemoteCommand* command);

    /*! @brief Handles the SET_CONFIG command
     *  @param command The command to handle
     */
    void handleSetConfigCommand(RemoteCommand* command);
};

#endif // COMMANDSYSTEM_H
