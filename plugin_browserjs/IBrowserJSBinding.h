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
 * Filename: IBrowserJSBinding.h
 * Class: IBrowserJSBinding
 * Description: Handles JavaScript interactions with the browser window
 * Created: 14/11/2010
 * ChangeLog:
 *     14/11/2010 - mike - Initial Creation
 */

#ifndef IBROWSERJSBINDING_H
#define IBROWSERJSBINDING_H

#include "JavascriptBinding.h"
#include <QObject>

class RemoteCommand;

/*! @brief  Provides the JavaScript Binding for interfacing with the Browser
 *          Class that provides the JavaScript Binding for interfacing with the Browser window including
 *          functions for chaing the state of the window (minimizing, maximizing, going fullscreen) and
 *          controlling which widgets are displayed in the browser window.
 */
class IBrowserJSBinding : public QObject, public JavascriptBinding
{
    Q_OBJECT

public:
    /*! @brief  Constructor for creating the Browser Javascript Binding
     *  @param  parent  The parent object
     */
    explicit IBrowserJSBinding(QObject* parent = 0);

    /*! @brief Initialises the binding once everything has been set
     */
    void Initialise();

    /*! @brief  Returns whether the browser has spatial navigation enabled or not
     *  @return Whether spatial navigation is enabled or not
     */
    bool spatialNavigationEnabled() const;
    /*! @brief  Sets whether the browser should enable spatial navigation or noy
     *  @param enabled  Whether spatial navigation is enabled or not
     */
    void setSpatialNavigationEnabled(const bool enabled);
    /*! @brief  Property for setting or getting whether spatial navigation is enabled or not */
    Q_PROPERTY(bool spatialNavigationEnabled READ spatialNavigationEnabled WRITE setSpatialNavigationEnabled);

    /*! @brief  Returns how much the browser should zoom the page by
     *  @return How much the browser should zoom the page by
     */
    int zoomPercentage() const;
    /*! @brief  Sets how much the browser should zoom the page by
     *  @param  percentage The zoom percentage that the page should be zoomed by
     */
    void setZoomPercentage(const int percentage);
    /*! @brief Property for controlling the zoom percentage of the page */
    Q_PROPERTY(int zoomPercentage READ zoomPercentage WRITE setZoomPercentage STORED false);

    /*! @brief  Returns the width of the browser window
     *  @return The width in pixels of the browser window
     */
    int windowWidth() const;
    /*! @brief Sets the width of the browser window
     *  @param width The width of the browser window in pixels
     */
    void setWindowWidth(const int width);
    /*! @brief Property for controlling the width of the browser window */
    Q_PROPERTY(int windowWidth READ windowWidth WRITE setWindowWidth STORED false);

    /*! @brief  Returns the height of the browser window
     *  @return The height in pixels of the browser window
     */
    int windowHeight() const;
    /*! @brief Sets the height of the browser window
     *  @param height The height of the browser window in pixels
     */
    void setWindowHeight(const int height);
    /*! @brief Property for controlling the height of the browser window */
    Q_PROPERTY(int windowHeight READ windowHeight WRITE setWindowHeight STORED false);

    /*! @brief  Returns whether the browser window is running fullscreen or not
     *  @return Whether the browser window is running fullscreen or not
     */
    bool fullscreen() const;
    /*! @brief Sets whether the browser window is running fullscreen or not
     *  @param isFullscreen Whether the browser window should be running fullscreen or not
     */
    void setFullscreen(const bool isFullscreen);
    /*! @brief Property for controlling whether the browser window is fullscreen or not */
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen STORED false);

    /*! @brief  Returns whether the browser window is running maximized or not
     *  @return Whether the browser window is running maximized or not
     */
    bool maximized() const;
    /*! @brief Sets whether the browser window is running maximized or not
     *  @param isMaximized Whether the browser window should be running maximized or not
     */
    void setMaximized(const bool isMaximized);
    /*! @brief Property for controlling whether the browser window is maximized or not */
    Q_PROPERTY(bool maximized READ maximized WRITE setMaximized STORED false);

    /*! @brief  Returns whether the browser window is running minimized or not
     *  @return Whether the browser window is running minimized or not
     */
    bool minimized() const;
    /*! @brief Sets whether the browser window is running minimized or not
     *  @param isMinimized Whether the browser window should be running minimized or not
     */
    void setMinimized(const bool isMinimized);
    /*! @brief Property for controlling whether the browser window is minimized or not */
    Q_PROPERTY(bool minimized READ minimized WRITE setMinimized STORED false);

    /*! @brief  Returns whether the browser's tool bar is showing or not
     *  @return Whether the browser's tool bar is showing or not
     */
    bool toolBarShowing() const;
    /*! @brief Sets whether the browser's tool bar is showing or not
     *  @param isShowing Whether the browser's tool bar is showing or not
     */
    void setToolBarShowing(const bool isShowing);
    /*! @brief Property for controlling whether the browser's tool bar is showing or not */
    Q_PROPERTY(bool toolBarShowing READ toolBarShowing WRITE setToolBarShowing STORED false);

signals:
    /*! @brief Emitted when the browser receives data via the InspireRemote utility
     *  @param data The data received
     */
    void onReceivedData(QString data);

public slots:
    /*! @brief Sets the size of the window
     *  @param width The width of the window
     *  @param height The height of the window
     */
    void SetWindowSize(const int width, const int height);

private slots:
    /*! @brief Handles the DATA command from inspireremote
     *  @param command The command to handle
     */
    void handleDataCommand(RemoteCommand* command);

    /*! @brief Handles the CHANGE_PAGE command from inspireremote
     *  @param command The command to handle
     */
    void handleChangePageCommand(RemoteCommand* command);
};

#endif // IBROWSERJSBINDING_H
