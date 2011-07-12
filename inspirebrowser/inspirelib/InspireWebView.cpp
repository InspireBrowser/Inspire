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
 * Filename: InspireWebView.cpp
 * Class: InspireWebView
 * Description: The main web view in the InspireBrowser, handles the addition
 *              of extra javascript bindings.
 * Created: 13/11/2010
 * ChangeLog:
 *     13/11/2010 - mike - Initial Creation
 */

#include "InspireWebView.h"

#include <QSettings>
#include <QWebFrame>
#include <QDesktopServices>

/*! @brief Creates an InspireWebView widget
 *  @param parent The parent widget
 */
InspireWebView::InspireWebView(QWidget *parent) :
        QWebView(parent)
{
    QSettings settings;

    this->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    this->settings()->setAttribute(QWebSettings::PluginsEnabled, false);
    this->settings()->setAttribute(QWebSettings::SpatialNavigationEnabled, false);
    this->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    this->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    this->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

    this->settings()->setLocalStoragePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));

    if(settings.value("browser/developerModeEnabled", false).toBool())
        this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJavascriptObjectsToFrame()));

    #warning TODO: Add functions for registering JavaScript plugins
}

/*! @brief Returns whether the background of the web view is transparent or not
 *  @return Whether the background of the web view is transparent or not
 */
bool InspireWebView::backgroundIsTransparent()
{
    return this->_transparentBackground;
}

/*! @brief Sets whether the background of the web view is transparent or not
 *  @param value whether the background of the web view is transparent or not
 */
void InspireWebView::setBackgroundIsTransparent(bool value)
{
    #warning TODO: Implement InspireWebView::setBackgroundIsTransparent
    this->_transparentBackground = value;
}

/*! @brief Adds the javascript binding objects to the current webview */
void InspireWebView::addJavascriptObjectsToFrame()
{
    QWebFrame *frame = (QWebFrame*)sender();

    QSettings settings;

    if(settings.value("browser/restrictJavascriptApi", false).toBool()){
        /* If we're restricting the javascript API to a list of allowed URL's then compare
           the URL using Wildcard RegExp and if it doesn't match leave the function */

        bool match = false;

        QStringList allowedUrls = settings.value("browser/allowedApiUrls").toStringList();
        for(int i=0; i<allowedUrls.count(); i++){
            QRegExp exp(allowedUrls[i], Qt::CaseInsensitive, QRegExp::Wildcard);
            if(exp.exactMatch(frame->url().toString())){
                match = true;
                break;
            }
        }

        if(!match)
            return;

	#warning TODO: Add registered javascript plugins
    }
}
