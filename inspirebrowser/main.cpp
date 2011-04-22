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
 * Description: The entry point for InspireBrowser
 * Created: 13/11/2010
 * ChangeLog:
 *     13/11/2010 - mike - Initial Creation
 */
#include <QApplication>

#include <QDebug>
#include <QSettings>
#include <QxtLogger>
#include <QxtBasicFileLoggerEngine>
#include <getopt.h>

#include "MainWindow.h"

int usage(QString errorMessage = "")
{
    QStringList arguments = QCoreApplication::arguments();

    qDebug() << "Usage: " << arguments.at(0) << " <options> <url> <url>";
    qDebug() << "";
    if(errorMessage != "") {
        qDebug() << "Error: " << errorMessage;
        qDebug() << "";
    }
    qDebug() << "Options:";
    qDebug() << "\t --help              Show this help message";
    qDebug() << "\t --log-level <int>   Sets the log level from 0 to 7 (default 2)";
    qDebug() << "\t --log-file <path>   Sets the file name to log to";
    qDebug() << "";

    return errorMessage != "" ? 1 : 0;
}

/*! @brief The Inspire Browser's main execution loop
 *  @param argc The number of command line arguments
 *  @param argv The contents of the command line arguments
 *  @return The exit status of the application
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int logLevel = 2;

    while(1) {
        static struct option long_options[] =
        {
            {"help",        no_argument,        0,  'h'},
            {"log-level",   required_argument,  0,  'l'},
            {"log-file",    required_argument,  0,  'f'},
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
            case 'l':
                temp = QString(optarg).toInt(&isOk);
                if(isOk) logLevel = temp;
                break;
            case 'f':
                qxtLog->addLoggerEngine("file", new QxtBasicFileLoggerEngine(QString(optarg)));
                break;
            case 'h':
                return usage();
        }
    }

    QStringList arguments;
    while (optind < argc)
        arguments.append(QString(argv[optind++]));

    //use QxtLog as the message handler
    qxtLog->installAsMessageHandler();

    //enable the log level we're reporting at and all below it
    switch(logLevel) {
        case 7:
            qxtLog->enableLogLevels(QxtLogger::TraceLevel);
        case 6:
            qxtLog->enableLogLevels(QxtLogger::DebugLevel);
        case 5:
            qxtLog->enableLogLevels(QxtLogger::InfoLevel);
        case 4:
            qxtLog->enableLogLevels(QxtLogger::WarningLevel);
        case 3:
            qxtLog->enableLogLevels(QxtLogger::ErrorLevel);
        case 2:
            qxtLog->enableLogLevels(QxtLogger::CriticalLevel);
        case 1:
            qxtLog->enableLogLevels(QxtLogger::FatalLevel);
        default:
            break;
    }

    qxtLog->info("Starting Application");

    //configure the following settings so we can use the default constructor in QSettings
    qxtLog->debug("Setting Organisation Name to " + QString(ORGANISATION_NAME));
    QCoreApplication::setOrganizationName(ORGANISATION_NAME);
    qxtLog->debug("Setting Organisation Domain to " + QString(ORGANISATION_DOMAIN));
    QCoreApplication::setOrganizationDomain(ORGANISATION_DOMAIN);
    qxtLog->debug("Setting Application Name to " + QString(APPLICATION_NAME));
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    qxtLog->debug("Setting Version to " + QString(VERSION));
    QCoreApplication::setApplicationVersion(VERSION);

    QSettings settings;

    MainWindow w;

    if(settings.value("application/fullscreen", false).toBool()) {
        qxtLog->debug("Showing full screen");
        w.showFullScreen();
    }
    else {
        qxtLog->debug("Showing windowed");
        w.show();
    }

    int returnCode = app.exec();
    qxtLog->info("Exiting Application with return code: " + QString::number(returnCode));
    return returnCode;
}
