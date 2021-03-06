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
 * Filename: GenericPlugin.h
 * Class: GenericPlugin
 * Description: The abstract class that javascript bindings should
 *              implement.
 */
#ifndef JAVASCRIPTBINDING_H
#define JAVASCRIPTBINDING_H

class MainWindow;

class JavascriptBinding
{
private:
    MainWindow* _mainWindow;

public:
    virtual ~JavascriptBinding() {}

    void Initialise() {}

    MainWindow* mainWindow() const {
        return this->_mainWindow;
    }
    void setMainWindow(MainWindow* mainWindow) {
        this->_mainWindow = mainWindow;
    }
};

#endif // JAVASCRIPTBINDING_H
