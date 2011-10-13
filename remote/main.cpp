/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * Copyright (C) 2010  mike
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
 * Filename: main.cpp
 * Description: The entry point for InspireRemote
 * Created: 21/11/2010
 * ChangeLog:
 *     21/11/2010 - mike - Initial Creation
 */
#include <QCoreApplication>
#include <getopt.h>

#include "CommandSender.h"
#include "RemoteCommand.h"

int usage(bool extraHelp = false, QString errorMessage = "")
{
    QStringList arguments = QCoreApplication::arguments();

    qDebug() << "Usage: " << arguments.at(0) << " <options> ipAddress command <parameter> <parameter>";
    qDebug() << "";
    if(errorMessage != "") {
        qDebug() << "Error: " << errorMessage;
        qDebug() << "";
    }
    qDebug() << "Options:";
    qDebug() << "\t --help       Show this help message";
    qDebug() << "\t --extrahelp  Display an in-depth help message";
    qDebug() << "\t --quiet      Keep the output to a minimum";
    qDebug() << "\t --port <int> Set the port number to connect to";
    qDebug() << "";
    qDebug() << "IP Address can be a single IPv4 address, a comma seperated list of addresses";
    qDebug() << "a range of IP addresses or a comma seperated list of address ranges.";
    qDebug() << "";

    if(extraHelp) {
        qDebug() << "Commands:";
        qDebug() << "\t Name: GET_VERSION";
        qDebug() << "\t Parameters: None";
        qDebug() << "\t Description: Returns the version of software the client is running";
        qDebug() << "";
        qDebug() << "\t Name: GET_OS";
        qDebug() << "\t Parameters: None";
        qDebug() << "\t Description: Returns the operating system the client is running";
        qDebug() << "";
        qDebug() << "\t Name: GET_MAC_ADDRESS";
        qDebug() << "\t Parameters: int index (optional)";
        qDebug() << "\t Description: Returns the mac address of the network adapter specified";
        qDebug() << "\t              or the first adapter if the index is not provided";
        qDebug() << "";
        qDebug() << "\t Name: GET_CONFIG";
        qDebug() << "\t Parameters: string name";
        qDebug() << "\t Description: Returns a configuration option from the client";
        qDebug() << "";
        qDebug() << "\t Name: CHANGE_PAGE";
        qDebug() << "\t Parameters: string url";
        qDebug() << "\t Description: Instructs the browser to change to that page";
        qDebug() << "";
        qDebug() << "\t Name: DATA";
        qDebug() << "\t Parameters: string data";
        qDebug() << "\t Description: Passes the specified data through to the browser to be";
        qDebug() << "\t              handled by a web app";
        qDebug() << "";
        qDebug() << "Examples:";
        qDebug() << "";
        qDebug() << arguments.at(0) << " 192.168.0.100 GET_VERSION";
        qDebug() << "\t" << "Sends the command GET_VERSION to a single client";
        qDebug() << "";
        qDebug() << arguments.at(0) << " 192.168.0.100,192.168.0.110 GET_VERSION";
        qDebug() << "\t" << "Sends the command GET_VERSION to two clients";
        qDebug() << "";
        qDebug() << arguments.at(0) << " 192.168.0.100-192.168.0.110 GET_VERSION";
        qDebug() << "\t" << "Sends the command GET_VERSION to all clients in the range specified";
        qDebug() << "";
    }

    return errorMessage != "" ? 1 : 0;
}

QList<QHostAddress> parseIpAddresses(QString ipAddresses)
{
    QList<QHostAddress> addresses;

    QStringList commaSeperated = ipAddresses.split(",", QString::SkipEmptyParts);
    foreach(QString item, commaSeperated){
        QStringList startAndEnd = item.split("-", QString::SkipEmptyParts);
        if(startAndEnd.count() != 1 && startAndEnd.count() != 2)
            continue;
        else if(startAndEnd.count() == 1)
            startAndEnd.append(startAndEnd.first());

        QHostAddress start;
        if(!start.setAddress(startAndEnd.at(0)))
            throw QString(startAndEnd.at(0) + " is not a valid IP Address");

        QHostAddress end;
        if(!end.setAddress(startAndEnd.at(1)))
            throw QString(startAndEnd.at(1) + " is not a valid IP Address");

        for(quint32 i = start.toIPv4Address(); i <= end.toIPv4Address(); i++)
            addresses.append(QHostAddress(i));
    }

    //convert it to a set and then to a list so we remove all duplicates
    return addresses.toSet().toList();
}

/*! @brief The Inspire Remote's main execution loop
 *  @param argc The number of command line arguments
 *  @param argv The contents of the command line arguments
 *  @return The exit status of the application
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    //configure the following settings so we can use the default constructor in QSettings
    QCoreApplication::setOrganizationName(ORGANISATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANISATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(VERSION);

    int help = 0;
    int extraHelp = 0;
    int quiet = 0;
    int port = 4774;

    while(1) {
        static struct option long_options[] =
        {
            /* These options set a flag */
            {"help",        no_argument,        &help,      1},
            {"extrahelp",   no_argument,        &extraHelp, 1},
            {"quiet",       no_argument,        &quiet,     1},
            /* These options don't set a flag and we distinguish them by their indices */
            {"port",        required_argument,  0,          'p'},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        int c = getopt_long (argc, argv, "", long_options, &option_index);
        if (c == -1)
            break;

        bool isOk = false;
        int temp = 0;
        switch (c)
        {
            case 0:
                break;
            case 'p':
                temp = QString(optarg).toInt(&isOk);
                if(isOk) port = temp;
                break;
        }
    }

    if(help || extraHelp)
        return usage(extraHelp);

    QStringList arguments;
    while (optind < argc)
        arguments.append(QString(argv[optind++]));

    if(arguments.length() < 2) {
        return usage(false, "Incorrect number of arguments");
    }

    try
    {
        QList<QHostAddress> addresses = parseIpAddresses(arguments.takeFirst());

        RemoteCommand* command = new RemoteCommand();
        command->setCommand(arguments.takeFirst());
        while(!arguments.empty())
            command->addParameter(arguments.takeFirst());

        CommandSender sender(command);
        sender.setClientPort(port);
        foreach(QHostAddress address, addresses){
            sender.addClient(address);
        }

        if(!quiet)
            qDebug() << "Sending Command: " << command->command() << command->parameters();

        sender.send();

        return app.exec();
    }
    catch(QString e)
    {
        return usage(false, e);
    }
}
