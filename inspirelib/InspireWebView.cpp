/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
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
 */

#include "InspireWebView.h"

#include <QWebFrame>
#include <QDesktopServices>
#include <QxtLogger>

#include "Settings.h"

/*! @brief Creates an InspireWebView widget
 *  @param parent The parent widget
 */
InspireWebView::InspireWebView(QWidget* parent) :
    QWebView(parent)
{
    this->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    this->settings()->setAttribute(QWebSettings::PluginsEnabled, false);
    this->settings()->setAttribute(QWebSettings::SpatialNavigationEnabled, false);
    this->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    this->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    this->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

    this->settings()->setLocalStoragePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));

    if(SETTING("browser-developer-mode", false).toBool()) {
        this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    }

    connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJavascriptObjectsToFrame()));
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

/*! @brief Adds a Javascript Binding Object to list of binding objects that
*         the web view can add.
*  @param name The name of the binding to add
*  @param binding The binding object to add to the web view
*/
void InspireWebView::addJavascriptBinding(QString name, QObject* binding)
{
    _bindings[name] = binding;
}

/*! @brief Removes a Javascript binding object from the list of objects to add
*  @param name The name of the binding
*  @return Whether the binding existed or not and was thus removed
*/
bool InspireWebView::removeJavascriptBinding(QString name)
{
    if(this->hasJavascriptBinding(name)) {
        _bindings.remove(name);
        return true;
    } else {
        return false;
    }
}

/*! @brief Returns whether the Javascript binding exists or not
*  @param name The name of the binding
*  @return Whether the Javascript binding exists or not
*/
bool InspireWebView::hasJavascriptBinding(QString name)
{
    return _bindings.contains(name);
}

/*! @brief Returns a Javascript binding object that has been registered with
*         the web view
*  @param name The name of the binding
*  @return The Javascript Binding object or a null point if it doesn't exist
*/
QObject* InspireWebView::getJavascriptBinding(QString name)
{
    if(this->hasJavascriptBinding(name)) {
        return _bindings.value(name);
    } else {
        return 0;
    }
}

/*! @brief Adds the javascript binding objects to the current webview */
void InspireWebView::addJavascriptObjectsToFrame()
{
    QWebFrame* frame = (QWebFrame*)sender();

    if(SETTING("browser-restrict-js-api", false).toBool()) {
        qxtLog->debug("Restrict Javascript API is enabled to check the URL");

        /* If we're restricting the javascript API to a list of allowed URL's then compare
           the URL using Wildcard RegExp and if it doesn't match leave the function */

        bool match = false;

        qxtLog->debug("Looking for " + frame->url().toString() + " in list of allowed API URLs");
        QStringList allowedUrls = SETTING("browser-allowed-api-urls", QVariant()).toStringList();
        for(int i = 0; i < allowedUrls.count(); i++) {
            qxtLog->debug("Comparing to " + allowedUrls[i]);
            QRegExp exp(allowedUrls[i], Qt::CaseInsensitive, QRegExp::Wildcard);
            if(exp.exactMatch(frame->url().toString())) {
                qxtLog->debug("URL matches, allowing JS API");
                match = true;
                break;
            }
        }

        if(!match) {
            qxtLog->debug("No URLs matched. Not allowing JS API");
            return;
        }
    }

    QHashIterator<QString, QObject*> i(_bindings);
    while (i.hasNext()) {
        i.next();
        qxtLog->debug("Adding JS Binding " + i.key() + " to frame");
        frame->addToJavaScriptWindowObject(i.key(), i.value());
    }
}
