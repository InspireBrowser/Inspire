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
 * Filename: SystemJSPlugin.h
 * Class: SystemJSPlugin
 * Description: The plugin class that when initialised provides a JavaScript
 *              Binding for interactions with the system
 */
#ifndef SYSTEM_JS_PLUGIN
#define SYSTEM_JS_PLUGIN

#include <QObject>
#include "GenericPlugin.h"

class SystemJSPlugin : public QObject, public GenericPlugin
{
    Q_OBJECT
    Q_INTERFACES(GenericPlugin)

public:
    explicit SystemJSPlugin(QObject* parent = 0);

    bool InitialisePlugin();
    bool DeInitialisePlugin();

    QString GetId();
    QString GetName();
    QString GetDescription();
};

#endif //SYSTEM_JS_PLUGIN
