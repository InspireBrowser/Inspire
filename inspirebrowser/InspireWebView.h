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
 * Filename: InspireWebView.h
 * Class: InspireWebView
 * Description: The main web view in the InspireBrowser, handles the addition
 *              of extra javascript bindings.
 * Created: 13/11/2010
 * ChangeLog:
 *     13/11/2010 - mike - Initial Creation
 */

#ifndef INSPIREWEBVIEW_H
#define INSPIREWEBVIEW_H

#include <QWebView>

class ISystemJSBinding;
class IBrowserJSBinding;
class IVideoJSBinding;

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
    explicit InspireWebView(QWidget *parent = 0);

    /*! @brief Returns whether the background of the web view is transparent or not
     *  @return Whether the background of the web view is transparent or not
     */
    bool backgroundIsTransparent();
    /*! @brief Sets whether the background of the web view is transparent or not
     *  @param value whether the background of the web view is transparent or not
     */
    void setBackgroundIsTransparent(bool value);

    /*! @brief Returns the System JS Binding for this Web View
     *  @return The System JS Binding for this Web View
     */
    ISystemJSBinding* iSystem() { return _iSystem; }

    /*! @brief Returns the Browser JS Binding for this Web View
     *  @return The Browser JS Binding for this Web View
     */
    IBrowserJSBinding* iBrowser() { return _iBrowser; }

    /*! @brief Returns the Video JS Binding for this Web View
     *  @return The Video JS Binding for this Web View
     */
    IVideoJSBinding* iVideo() { return _iVideo; }

signals:

public slots:

private:
    /*! @brief Whether the background of the webview is transparent or not */
    bool _transparentBackground;
    /*! @brief The System Javascript Binding interface to be added to the web view */
    ISystemJSBinding *_iSystem;
    /*! @brief The Browser Javascript Binding interface to be added to the web view */
    IBrowserJSBinding *_iBrowser;
    /*! @brief The Video Javascript Binding interface to be added to the web view */
    IVideoJSBinding *_iVideo;

private slots:
    /*! @brief Adds the javascript binding objects to the current webview */
    void addJavascriptObjectsToFrame();

};

#endif // INSPIREWEBVIEW_H
