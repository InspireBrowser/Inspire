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
 * Filename: CommandServer.h
 * Class: CommandServer
 * Description: Command Server listens for commands sent by InspireRemote
 *              and then emits signals when they arrive so listeners can
 *              handle them
 * Created: 26/01/2011
 * ChangeLog:
 *     26/01/2011 - mike - Initial Creation
 */

#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include <QTcpServer>

class RemoteCommand;

/*! @brief The CommandServer listens to commands coming from the network
 *         Once a command has been received, parsed and verified the
 *         commandReceived signal is emitted and the slots connected have
 *         a chance to handle the command
 */
class CommandServer : public QTcpServer
{
    Q_OBJECT
public:
    /*! @brief Creates the CommandServer
     *  @param parent The parent object
     */
    explicit CommandServer(QObject *parent = 0);

    /*! @brief Instructs the CommandServer to start listening
     *  @returns Whether the command server could start listening or not
     */
    bool startListening();

    /*! @brief Instructs the CommandServer to stop listening */
    void stopListening();

    /*! @brief Processes a RemoteCommand
     *  @param command The command to process
     */
    void processCommand(RemoteCommand* command);

private:
    /*! @brief Called when the server receives an incoming connection
     *  @param handle The connection handle to use
     */
    void incomingConnection(int handle);

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
};

#endif // COMMANDSERVER_H