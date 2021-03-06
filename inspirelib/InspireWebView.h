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
 * Filename: InspireWebView.h
 * Class: InspireWebView
 * Description: The main web view in the InspireBrowser, handles the addition
 *              of extra javascript bindings.
 */

#ifndef INSPIREWEBVIEW_H
#define INSPIREWEBVIEW_H

#include <QWebView>
#include <QHash>

/*! @brief WebView widget for the Inspire Browser
 *         Contains some enhancements to the default WebView for use by Inspire
 */
class InspireWebView : public QWebView
{
    Q_OBJECT
public:
    /*! @brief Creates an InspireWebView widget
     *  @param parent The parent widget
     */
    explicit InspireWebView(QWidget* parent = 0);

    /*! @brief Returns whether the background of the web view is transparent or not
     *  @return Whether the background of the web view is transparent or not
     */
    bool backgroundIsTransparent();
    /*! @brief Sets whether the background of the web view is transparent or not
     *  @param value whether the background of the web view is transparent or not
     */
    void setBackgroundIsTransparent(bool value);

    /*! @brief Adds a Javascript Binding Object to list of binding objects that
     *         the web view can add.
     *  @param name The name of the binding to add
     *  @param binding The binding object to add to the web view
     */
    void addJavascriptBinding(QString name, QObject* binding);

    /*! @brief Removes a Javascript binding object from the list of objects to add
     *  @param name The name of the binding
     *  @return Whether the binding existed or not and was thus removed
     */
    bool removeJavascriptBinding(QString name);

    /*! @brief Returns whether the Javascript binding exists or not
     *  @param name The name of the binding
     *  @return Whether the Javascript binding exists or not
     */
    bool hasJavascriptBinding(QString name);

    /*! @brief Returns a Javascript binding object that has been registered with
     *         the web view
     *  @param name The name of the binding
     *  @return The Javascript Binding object or a null point if it doesn't exist
     */
    QObject* getJavascriptBinding(QString name);

signals:

public slots:

private:
    /*! @brief Whether the background of the webview is transparent or not */
    bool _transparentBackground;

    /*! @brief stores the javascript bindings registered with the web view */
    QHash<QString, QObject*> _bindings;

private slots:
    /*! @brief Adds the javascript binding objects to the current webview */
    void addJavascriptObjectsToFrame();

};

#endif // INSPIREWEBVIEW_H
