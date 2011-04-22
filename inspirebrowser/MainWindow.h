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
 * Filename: MainWindow.h
 * Class: MainWindow
 * Description: The main InspireBrowser window
 * Created: 13/11/2010
 * ChangeLog:
 *     13/11/2010 - mike - Initial Creation
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "InspireWebView.h"
#include <QMainWindow>
#include <QUrl>

class QAction;
class QLabel;
class QLineEdit;
class QToolBar;
class QWebView;
class GenericLayout;
class CommandServer;

/*! @brief The main window used by InspireBrowser
 *         Handles the toolbar, menubar, tab bar and status bar.
 */
class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
        /*! @brief Constructs the main window for the Inspire Browser
         *  @param parent The parent widget
         */
        explicit MainWindow(QWidget* parent = 0);

        /*! @brief Returns the layout manager for the MainWindow
         *  @return The layout manager for the MainWindow
         */
        QLayout* layout(){return this->_mainLayout;}

        /*! @brief Returns the command server used by the application
         *  @return The command server used by the application
         */
        CommandServer* commandServer() { return _commandServer; }

        /*! @brief Returns the Web View object used in the browser
         *  @return The Web View object used in the browser
         */
        InspireWebView* webView() { return _webView; }

        /*! @brief Returns the navigation bar used in the browser
         *  @return The navigation bar used in the browser
         */
        QToolBar* navigationBar() { return _navigationToolBar; }

private:
        /*! @brief Creates the actions that are used by the menus, toolbars and context menus */
        void createActions();
        /*! @brief Creates the context menu for the UI */
        void createContextMenu();
        /*! @brief Creates the toolbar for the UI */
        void createToolBars();
        /*! @brief Resizes the window to the values stored in the settings */
        void resizeWindow();

        /*! @brief Updates the state of actions depending on the state of the UI
         *  @param isLoading Whether the browser is currently loading something
         */
        void updateActions(bool isLoading);

        /*! @brief Handles the receiving of commands remotely */
        CommandServer* _commandServer;
        /*! @brief The web view for the main area */
        InspireWebView* _webView;
        /*! @brief The windows layout manager */
        QLayout* _mainLayout;

        /*! @brief An action that tells the browser to go back an entry in it's history */
        QAction* _backAction;
        /*! @brief An action that tells the browser to go forward an entry in it's history */
        QAction* _forwardAction;
        /*! @brief An action that tells the browser to go to it's homepage */
        QAction* _homeAction;
        /*! @brief An action that tells the browser to reload the current page */
        QAction* _reloadAction;
        /*! @brief An action that tells the browser to stop loading the current page */
        QAction* _stopAction;
        /*! @brief An action that tells the browser to load the current page in the address bar*/
        QAction* _goAction;

        /*! @brief The navigation tool bar */
        QToolBar* _navigationToolBar;
        /*! @brief The address bar in the navigation bar */
        QLineEdit* _addressBar;

private slots:

        /*! @brief Informs the browser that the loading of the page has completed
         *  @brief Whether loading is complete or not
         */
        void loadingComplete(bool complete);

        /*! @brief Updates the address bar with the specified URL
         *  @param url The URL to put in the address bar
         */
        void updateAddressBar(QUrl url);

        /*! @brief Loads the homepage from the settings into the browser */
        void loadHomePage();

        /*! @brief Loads the URL in the address bar into the current web view */
        void loadPageInAddressBar();

public slots:
        /*! @brief Loads a URL into the current web view
         *  @param url The URL to load
         */
        void loadPage(const QUrl url);
};

#endif
