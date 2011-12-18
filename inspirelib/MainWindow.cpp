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
 * Filename: MainWindow.cpp
 * Class: MainWindow
 * Description: The main InspireBrowser window
 */

#include <QtGui>
#include <QWebView>
#include <QWebFrame>
#include <QWebHistory>
#include <QUrl>

#include "GenericLayout.h"
#include "MainWindow.h"
#include "PluginManager.h"
#include "CommandSystem.h"
#include "Settings.h"

/*! @brief Constructs the main window for the Inspire Browser
 *  @param parent The parent widget
 */
MainWindow::MainWindow(PluginManager* manager, QWidget* parent) :
    QMainWindow(parent), _pluginManager(manager)
{
    //initialise the command system
    _commandSystem = new CommandSystem(this);

    //take control of the plugin manager
    this->_pluginManager->setParent(this);

    _webView = new InspireWebView(this);
    _webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(_webView, SIGNAL(linkClicked(QUrl)), this, SLOT(loadPage(QUrl)));
    connect(_webView, SIGNAL(loadFinished(bool)), this, SLOT(loadingComplete(bool)));
    connect(_webView, SIGNAL(titleChanged(QString)), this, SLOT(setWindowTitle(QString)));
    connect(_webView, SIGNAL(urlChanged(QUrl)), this, SLOT(updateAddressBar(QUrl)));

    QWidget* centralWidget = new QWidget();
    _mainLayout = new GenericLayout(centralWidget);
    _mainLayout->addWidget(_webView);

    this->setCentralWidget(centralWidget);

    createActions();
    createContextMenu();
    createToolBars();

    loadHomePage();
    setWindowIcon(QIcon(":/images/mainIcon.png"));

    //now we've created everything, initialise all the plugins
    _pluginManager->InitialisePlugins();
}

/*! @brief Creates the actions that are used by the menus, toolbars and context menus
 */
void MainWindow::createActions()
{
    _backAction = new QAction(tr("Back"), this);
    _backAction->setIcon(QIcon(":/images/back.png"));
    _backAction->setShortcut(QKeySequence::Back);
    _backAction->setStatusTip(tr("Go back one page"));
    connect(_backAction, SIGNAL(triggered()), _webView, SLOT(back()));

    _forwardAction = new QAction(tr("Forward"), this);
    _forwardAction->setIcon(QIcon(":/images/forward.png"));
    _forwardAction->setShortcut(QKeySequence::Forward);
    _forwardAction->setStatusTip(tr("Go forward one page"));
    connect(_forwardAction, SIGNAL(triggered()), _webView, SLOT(forward()));

    _reloadAction = new QAction(tr("Reload"), this);
    _reloadAction->setIcon(QIcon(":/images/reload.png"));
    _reloadAction->setShortcut(QKeySequence::Refresh);
    _reloadAction->setStatusTip(tr("Reload current page"));
    connect(_reloadAction, SIGNAL(triggered()), _webView, SLOT(reload()));

    _homeAction = new QAction(tr("Home"), this);
    _homeAction->setIcon(QIcon(":/images/home.png"));
    _homeAction->setStatusTip(tr("Go to your homepage"));
    connect(_homeAction, SIGNAL(triggered()), this, SLOT(loadHomePage()));

    _stopAction = new QAction(tr("Stop"), this);
    _stopAction->setIcon(QIcon(":/images/stop.png"));
    _stopAction->setStatusTip(tr("Stop loading this page"));
    connect(_stopAction, SIGNAL(triggered()), _webView, SLOT(stop()));

    _goAction = new QAction(tr("Go"), this);
    _goAction->setIcon(QIcon(":/images/go.png"));
    _goAction->setStatusTip(tr("Load the typed page"));
    connect(_goAction, SIGNAL(triggered()), this, SLOT(loadPageInAddressBar()));

#warning TODO: Finish creating all actions
}

/*! @brief Creates the context menu for the UI
 */
void MainWindow::createContextMenu()
{
#warning TODO: Properly implement context menu for WebView
    _webView->addAction(_backAction);
    _webView->addAction(_forwardAction);
}

/*! @brief Creates the toolbar for the UI
 */
void MainWindow::createToolBars()
{
    _navigationToolBar = addToolBar(tr("&File"));
    _navigationToolBar->setFloatable(false);
    _navigationToolBar->setMovable(false);

    _navigationToolBar->addAction(_backAction);
    _navigationToolBar->addAction(_forwardAction);
    _navigationToolBar->addAction(_reloadAction);
    _navigationToolBar->addAction(_stopAction);
    _navigationToolBar->addAction(_homeAction);

    _addressBar = new QLineEdit();
    connect(_addressBar, SIGNAL(returnPressed()), this, SLOT(loadPageInAddressBar()));
    _navigationToolBar->addWidget(_addressBar);

    _navigationToolBar->addAction(_goAction);
}

/*! @brief Resizes the window to the values stored in the settings
 */
void MainWindow::resizeWindow()
{
    if(!SETTING("application-show-fullscreen", false).toBool()) {
        int width = SETTING("application-width", 1280).toInt();
        int height = SETTING("application-height", 720).toInt();

        this->resize(width, height);
    }
}

/*! @brief Updates the state of actions depending on the state of the UI
 *  @param isLoading Whether the browser is currently loading something
 */
void MainWindow::updateActions(bool isLoading)
{
    _backAction->setEnabled(_webView->history()->canGoBack());
    _forwardAction->setEnabled(_webView->history()->canGoForward());
    _stopAction->setEnabled(isLoading);
}

/*! @brief Informs the browser that the loading of the page has completed
 *  @brief Whether loading is complete or not
 */
void MainWindow::loadingComplete(bool complete)
{
    updateActions(false);
}

/*! @brief Updates the address bar with the specified URL
 *  @param url The URL to put in the address bar
 */
void MainWindow::updateAddressBar(QUrl url)
{
    _addressBar->setText(url.toString());
}

/*! @brief Loads the homepage from the settings into the browser
 */
void MainWindow::loadHomePage()
{
    loadPage(QUrl(SETTING("browser-homepage", "about:blank").toString()));
}

/*! @brief Loads the URL in the address bar into the current web view
 */
void MainWindow::loadPageInAddressBar()
{
    loadPage(QUrl::fromUserInput(_addressBar->text()));
}

/*! @brief Loads a URL into the current web view
 *  @param url The URL to load
 */
void MainWindow::loadPage(const QUrl url)
{
    _webView->load(url);
    updateAddressBar(url);
}
