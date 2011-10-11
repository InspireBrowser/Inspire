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
 * Filename: IVideoJSBinding.cpp
 * Class: IVideoJSBinding
 * Description: Handles javascript interactions with video
 * Created: 05/12/2010
 * ChangeLog:
 *     05/12/2010 - Mike - Initial Creation
 */

#include "IVideoJSBinding.h"
#include "VideoWindow.h"
#include <QWebView>
#include <QWebFrame>

/*! @brief Constructor for creating the Video Javascript Binding
 *  @param  parent  The parent object
 */
IVideoJSBinding::IVideoJSBinding(QObject *parent) :
		QObject(parent),
        windows()
{
}

/*! @brief Returns a video window object for manipulating videos
 *  @param index The index of the video window to retrieve
 *  @return The VideoWindow object at that index
 */
QVariant IVideoJSBinding::GetVideoWindow(int index)
{
    qxtLog->trace(Q_FUNC_INFO);

    if(index >= MAX_VIDEO_WINDOWS || index < 0)
        throw "Invalid video window index";

    if(!windows[index]) {
		windows[index] = new VideoWindow(this);
		windows[index]->setMainWindow(this->mainWindow());
		windows[index]->Initialise();
    }

    QVariant var(QMetaType::QObjectStar);
    var.setValue((QObject*)windows[index]);
    return var;
}

/*! @brief Sets all video windows back to their default set */
void IVideoJSBinding::ResetAll()
{
    qxtLog->trace(Q_FUNC_INFO);

    for(int i=0; i < MAX_VIDEO_WINDOWS; i++)
    {
        if(windows[i])
            windows[i]->Reset();
    }
}
