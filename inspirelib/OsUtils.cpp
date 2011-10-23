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
 * Filename: OsUtils.cpp
 * Class: OsUtils
 * Description: Provides utility functions related to the OS
 * Created: 13/07/2011
 * ChangeLog:
 *     13/07/2011 - mike - Initial Creation
 */

#include "OsUtils.h"

#include <QProcess>
#include <QxtLogger>

/*! @brief Returns the Operating system that Inspire Browser is running on
 *  @return The Operating system that Inspire Browser is running on
 */
QString OsUtils::operatingSystemName()
{
#if defined(Q_OS_WIN)
    switch(QSysInfo::WindowsVersion){
        case QSysInfo::WV_NT:
            return "Windows NT 4.0";
        case QSysInfo::WV_2000:
            return "Windows 2000";
        case QSysInfo::WV_XP:
            return "Windows XP";
        case QSysInfo::WV_2003:
            return "Windows XP Professional x64 Edition";
        case QSysInfo::WV_VISTA:
            return "Windows Vista";
        case QSysInfo::WV_WINDOWS7:
            return "Windows 7";
        default:
            return "Unknown Windows OS";
    }
#elif defined(Q_OS_MAC)
    switch(QSysInfo::MacintoshVersion){
        case QSysInfo::MV_10_3:
            return "Mac OS X 10.3 Panther";
        case QSysInfo::MV_10_4:
            return "Mac OS X 10.4 Tiger";
        case QSysInfo::MV_10_5:
            return "Mac OS X 10.5 Leopard";
        case QSysInfo::MV_10_6:
            return "Mac OS X 10.6 Snow Leopard";
#if QT_VERSION > 0x040800
        case QSysInfo::MV_10_7:
            return "Mac OS X 10.7 Lion";
#endif
        default:
            return "Unknown Mac OS";
    }
#elif defined(Q_OS_LINUX)
    QProcess process;
    process.start("lsb_release", QStringList("-cirs"), QIODevice::ReadOnly);
    qxtLog->error(process.error());

    QByteArray output;
    while (process.waitForReadyRead()) {
        output += process.readAll();
    }

    QString contents(output);
    QStringList lines = contents.split("\n", QString::SkipEmptyParts);

    QString distro = "";
    if(lines.length() > 0) {
        distro = lines.at(0);
    }
    else {
        qxtLog->error("No output from command lsb_release");
        return "Unknown Linux OS";
    }

    if(lines.length() > 1)
        distro += " " + lines.at(1);

    if(lines.length() > 2)
        distro += " (" + lines.at(2) + ")";

    return distro;
#else
    #warning TODO: Implement ISystemJSBinding::operatingSystem does not support this OS
    return "Unknown OS";
#endif
}
