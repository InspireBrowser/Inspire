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
#include <QxtLogger>
#include <QxtBasicFileLoggerEngine>
#include <QxtCommandOptions>

#include "MainWindow.h"
#include "PluginManager.h"
#include "Settings.h"

int usage(QString errorMessage = "")
{
    QTextStream stream(stdout);
    QStringList arguments = QCoreApplication::arguments();

    stream << "Usage: " << arguments.at(0) << " <options> <url>[ <url>]" << endl;
    if(errorMessage != "") {
        stream << endl;
        stream << "Error: " << errorMessage << endl;
    }

    Settings::Get()->getSettingInformation()->showUsage(true, stream);

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

    QCoreApplication::setOrganizationName(ORGANISATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANISATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(VERSION);

    // call parse the first time so we can get parse the libinspire
    // command line arguments and setup logging and so on before
    // loading plugins and parsing again
    Settings::Get()->parseArguments();

    //use QxtLog as the message handler
    qxtLog->installAsMessageHandler();

    //enable the log level we're reporting at and all below it
    qxtLog->disableAllLogLevels();
    switch(SETTING("log-level", 2).toInt()) {
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

    if(SETTING_SET("log-file"))
        qxtLog->addLoggerEngine("file", new QxtBasicFileLoggerEngine(SETTING("log-file", "/tmp/inspire.log").toString()));

    //create the plugin manager and load all plugins
    PluginManager* pluginManager = new PluginManager();
    pluginManager->LoadPlugins();

    // now parse the arguments again so all the plugin ones are parsed
    // as well
    QString errorMessage = Settings::Get()->parseArguments();

    if(errorMessage != "")
        return usage(errorMessage);

    if(SETTING("help", false).toBool())
        return usage();

    qxtLog->info("Starting Application");

    MainWindow w(pluginManager);

    if(SETTING("application-show-fullscreen", false).toBool()) {
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
