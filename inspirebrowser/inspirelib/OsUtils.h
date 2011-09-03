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
 * Filename: OsUtils.h
 * Class: OsUtils
 * Description: Provides utility functions related to the OS
 * Created: 13/07/2011
 * ChangeLog:
 *     13/07/2011 - mike - Initial Creation
 */

#ifndef OS_UTILS_H
#define OS_UTILS_H

#include <QObject>

class OsUtils : public QObject
{
    Q_OBJECT

public:
    static QString operatingSystemName();
};

#endif //OS_UTILS_H
