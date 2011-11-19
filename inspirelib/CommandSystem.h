#ifndef COMMANDSYSTEM_H
#define COMMANDSYSTEM_H

#include <QObject>

class RemoteCommand;

class CommandSystem : public QObject
{
    Q_OBJECT

public:
    explicit CommandSystem(QObject *parent = 0);

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
