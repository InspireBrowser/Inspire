/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * Copyright (C) 2010  Mike
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
 * Filename: IVideoJSBinding.h
 * Class: IVideoJSBinding
 * Description: Handles javascript interactions with video
 * Created: 05/12/2010
 * ChangeLog:
 *     05/12/2010 - Mike - Initial Creation
 */

#ifndef IVIDEOJSBINDING_H
#define IVIDEOJSBINDING_H

#include "JavascriptBinding.h"
#include <QxtLogger>

class VideoWindow;

#define MAX_VIDEO_WINDOWS 6

/*! @brief  Provides the JavaScript Binding for interfacing with Video
 *          Class that manages the video windows that are available to be used.
 */
class IVideoJSBinding : public QObject, public JavascriptBinding
{
    Q_OBJECT
private:
    /*! @brief Contains the available video window */
    VideoWindow* windows[MAX_VIDEO_WINDOWS];

public:
    /*! @brief Constructor for creating the Video Javascript Binding
     *  @param  parent  The parent object
     */
    explicit IVideoJSBinding(QObject* parent = 0);

    /*! @brief Returns the maximum number of video windows the system is capable of showing at once
     *  @return the maximum number of video windows available
     */
    int maxVideoWindows() const {
        qxtLog->trace(Q_FUNC_INFO);
        return MAX_VIDEO_WINDOWS;
    }
    /*! @brief Property for retrieving the maximum number of video window */
    Q_PROPERTY(int maxVideoWindows READ maxVideoWindows CONSTANT);

signals:

public slots:
    /*! @brief Returns a video window object for manipulating videos
     *  @param index The index of the video window to retrieve
     *  @return The VideoWindow object at that index
     */
    QVariant GetVideoWindow(int index);

    /*! @brief Sets all video windows back to their default set */
    void ResetAll();
};

#endif // IVIDEOJSBINDING_H
