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
 * Filename: BrowserJSPlugin.h
 * Class: BrowserJSPlugin
 * Description: The plugin class that when initialised provides a JavaScript
 *              Binding for interactions with the browser.
 */
#ifndef BROWSER_JS_PLUGIN
#define BROWSER_JS_PLUGIN

#include <QObject>
#include "GenericPlugin.h"

class BrowserJSPlugin : public QObject, public GenericPlugin
{
    Q_OBJECT
    Q_INTERFACES(GenericPlugin)

public:
    explicit BrowserJSPlugin(QObject* parent = 0);

    bool InitialisePlugin();
    bool DeInitialisePlugin();

    QString GetId();
    QString GetName();
    QString GetDescription();
};

#endif //BROWSER_JS_PLUGIN
