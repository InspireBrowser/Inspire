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
 * Filename: IBrowserJSBinding.cpp
 * Class: IBrowserJSBinding
 * Description: Handles JavaScript interactions with the browser window
 * Created: 14/11/2010
 * ChangeLog:
 *     14/11/2010 - mike - Initial Creation
 */

#include "IBrowserJSBinding.h"

#include <QWebView>
#include <QxtLogger>
#include <QToolBar>

#include "MainWindow.h"
#include "CommandSystem.h"
#include "RemoteCommand.h"

/*! @brief  Constructor for creating the Browser Javascript Binding
 *  @param  parent  The parent object
 */
IBrowserJSBinding::IBrowserJSBinding(QObject *parent) :
		QObject(parent)
{

}

void IBrowserJSBinding::Initialise()
{
	connect(this->mainWindow()->commandSystem(), SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleDataCommand(RemoteCommand*)));
	connect(this->mainWindow()->commandSystem(), SIGNAL(commandReceived(RemoteCommand*)), this, SLOT(handleChangePageCommand(RemoteCommand*)));
}

/*! @brief  Returns whether the browser has spatial navigation enabled or not
 *  @return Whether spatial navigation is enabled or not
 */
bool IBrowserJSBinding::spatialNavigationEnabled() const
{
    qxtLog->trace(Q_FUNC_INFO);

	QWebView *parentView = this->mainWindow()->webView();
    return parentView->settings()->SpatialNavigationEnabled;
}

/*! @brief  Sets whether the browser should enable spatial navigation or noy
 *  @param enabled  Whether spatial navigation is enabled or not
 */
void IBrowserJSBinding::setSpatialNavigationEnabled(const bool enabled)
{
    qxtLog->trace(Q_FUNC_INFO);

	QWebView *parentView = this->mainWindow()->webView();
    parentView->settings()->setAttribute(QWebSettings::SpatialNavigationEnabled, enabled);
}

/*! @brief  Returns how much the browser should zoom the page by
 *  @return How much the browser should zoom the page by
 */
int IBrowserJSBinding::zoomPercentage() const
{
    qxtLog->trace(Q_FUNC_INFO);

	QWebView *parentView = this->mainWindow()->webView();
    if(parentView)
       return (int)(parentView->zoomFactor() * 100);
    else
        return 100;
}
/*! @brief  Sets how much the browser should zoom the page by
 *  @param  percentage The zoom percentage that the page should be zoomed by
 */
void IBrowserJSBinding::setZoomPercentage(const int percentage)
{
    qxtLog->trace(Q_FUNC_INFO);

	QWebView *parentView = this->mainWindow()->webView();
    if(parentView) {
        float factor = (float)percentage / 100;
        parentView->setZoomFactor(factor);
    }
}

/*! @brief  Returns the width of the browser window
 *  @return The width in pixels of the browser window
 */
int IBrowserJSBinding::windowWidth() const 
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::windowWidth() Couldn't get Main Window");
        return -1;
    }

    return window->width();
}

/*! @brief Sets the width of the browser window
 *  @param width The width of the browser window in pixels
 */
void IBrowserJSBinding::setWindowWidth(const int width)
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::windowHeight() Couldn't get Main Window");
        return;
    }

    window->resize(width, window->height());
}

/*! @brief  Returns the height of the browser window
 *  @return The height in pixels of the browser window
 */
int IBrowserJSBinding::windowHeight() const 
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::windowHeight() Couldn't get Main Window");
        return -1;
    }

    return window->height();
}

/*! @brief Sets the height of the browser window
 *  @param height The height of the browser window in pixels
 */
void IBrowserJSBinding::setWindowHeight(const int height)
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::setWindowHeight() Couldn't get Main Window");
        return;
    }

    window->resize(window->width(), height);
}

/*! @brief  Returns whether the browser window is running fullscreen or not
 *  @return Whether the browser window is running fullscreen or not
 */
void IBrowserJSBinding::setFullscreen(const bool isFullscreen)
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::setFullscreen() Couldn't get Main Window");
        return;
    }

    if(isFullscreen)
        window->showFullScreen();
    else
        window->showNormal();
}

/*! @brief Sets whether the browser window is running fullscreen or not
 *  @param isFullscreen Whether the browser window should be running fullscreen or not
 */
bool IBrowserJSBinding::fullscreen() const 
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::fullscreen() Couldn't get Main Window");
        return false;
    }

    return window->isFullScreen();
}

/*! @brief  Returns whether the browser window is running maximized or not
 *  @return Whether the browser window is running maximized or not
 */
bool IBrowserJSBinding::maximized() const 
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::maximized() Couldn't get Main Window");
        return false;
    }

    return window->isMaximized();
}

/*! @brief Sets whether the browser window is running maximized or not
 *  @param isMaximized Whether the browser window should be running maximized or not
 */
void IBrowserJSBinding::setMaximized(const bool isMaximized)
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::setMaximized() Couldn't get Main Window");
        return;
    }

    if(isMaximized)
        window->showMaximized();
    else
        window->showNormal();
}

/*! @brief  Returns whether the browser window is running minimized or not
 *  @return Whether the browser window is running minimized or not
 */
bool IBrowserJSBinding::minimized() const 
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::minimized() Couldn't get Main Window");
        return false;
    }

    return window->isMinimized();
}

/*! @brief Sets whether the browser window is running minimized or not
 *  @param isMinimized Whether the browser window should be running minimized or not
 */
void IBrowserJSBinding::setMinimized(const bool isMinimized)
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(!window) {
        qxtLog->fatal("IBrowserJSBinding::setMinimized() Couldn't get Main Window");
        return;
    }

    if(isMinimized)
        window->showMinimized();
    else
        window->showNormal();
}

/*! @brief  Returns whether the browser's tool bar is showing or not
 *  @return Whether the browser's tool bar is showing or not
 */
bool IBrowserJSBinding::toolBarShowing() const
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(window)
        return window->navigationBar()->isVisible();
    else {
        qxtLog->fatal("IBrowserJSBinding::toolBarShowing() Couldn't get Main Window");
        return true;
    }
}

/*! @brief Sets whether the browser's tool bar is showing or not
 *  @param isShowing Whether the browser's tool bar is showing or not
 */
void IBrowserJSBinding::setToolBarShowing(const bool isShowing)
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(window)
        window->navigationBar()->setVisible(isShowing);
    else {
        qxtLog->fatal("IBrowserJSBinding::toolBarShowing() Couldn't get Main Window");
        return;
    }
}

/*! @brief Sets the size of the window
 *  @param width The width of the window
 *  @param height The height of the window
 */
void IBrowserJSBinding::SetWindowSize(const int width, const int height)
{
    qxtLog->trace(Q_FUNC_INFO);

	MainWindow* window = this->mainWindow();
    if(window)
        window->resize(width, height);
    else {
        qxtLog->fatal("IBrowserJSBinding::SetWindowSize() Couldn't get Main Window");
        return;
    }
}

/*! @brief Handles the DATA command from inspireremote
 *  @param command The command to handle
 */
void IBrowserJSBinding::handleDataCommand(RemoteCommand *command)
{
    if(command->command() != "DATA")
        return;

    if(command->parameterCount() < 1)
        return command->setResponse(false, "Data not specified");
    else if(command->parameterCount() > 1)
        return command->setResponse(false, "Too many parameters");

    emit onReceivedData(command->parameter(0));
    command->setResponse(true, "Sent");
}

/*! @brief Handles the CHANGE_PAGE command from inspireremote
 *  @param command The command to handle
 */
void IBrowserJSBinding::handleChangePageCommand(RemoteCommand *command)
{
    if(command->command() != "CHANGE_PAGE")
        return;

    if(command->parameterCount() < 1)
        return command->setResponse(false, "URL not specified");
    else if(command->parameterCount() > 1)
        return command->setResponse(false, "Too many parameters");

    QUrl url(command->parameter(0));

	this->mainWindow()->loadPage(url);
    return command->setResponse(true, "Done");
}
