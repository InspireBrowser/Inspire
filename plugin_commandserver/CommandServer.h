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
 * Filename: CommandServer.h
 * Class: CommandServer
 * Description: Command Server listens for commands sent by InspireRemote
 *              and then emits signals when they arrive so listeners can
 *              handle them
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
    explicit CommandServer(QObject* parent = 0);

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
};

#endif // COMMANDSERVER_H
