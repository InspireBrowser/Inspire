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
 * Filename: VideoWindow.cpp
 * Class: VideoWindow
 * Description: Provides the JS bindings for controlling a video window
 * Created: 17/12/2010
 * ChangeLog:
 *     17/12/2010 - Mike - Initial Creation
 */

#include <QLayout>
#include "VideoWindow.h"
#include "MainWindow.h"
#include "VLC/QVlcPlayer.h"

/*! @brief Constructs a video window javascript object
 *  @param parent The parent object
 */
VideoWindow::VideoWindow(QObject* parent) :
		QObject(parent)
{
}

/*! @brief Destructor for tidying up the video window */
VideoWindow::~VideoWindow()
{
    delete _player;
}

void VideoWindow::Initialise()
{
	MainWindow* window = this->mainWindow();
	_player = new QVlcPlayer();
	window->layout()->addWidget(_player);
}

/*! @brief Returns whether any media is currently being played
 *  @return Whether any media is currently being played
 */
bool VideoWindow::isPlaying() const
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::isPlaying()
    return false;
}

/*! @brief Returns the volume the media is being played at
 *  @return The volume the media is being played at
 */
int VideoWindow::volume() const
{
    qxtLog->trace(Q_FUNC_INFO);

    return _player->volume();
}

/*! @brief Sets the volume to playback media at
 *  @param volume The volume between 0 and 200
 */
void VideoWindow::setVolume(const int volume)
{
    qxtLog->trace(Q_FUNC_INFO);

    _player->setVolume(volume);
}

/*! @brief Returns whether the video playback is muted or not
 *  @return Whether the video playback is muted or not
 */
bool VideoWindow::muted() const
{
    qxtLog->trace(Q_FUNC_INFO);

    return _player->muted();
}

/*! @brief Sets whether the media's audio is muted or not
 *  @param muted Whether the media's audio is muted or not
 */
void VideoWindow::setMute(const bool muted)
{
    qxtLog->trace(Q_FUNC_INFO);

    _player->setMute(muted);
}

/*! @brief Returns the speed that media plays at
 *  @return the speed to play media back at
 */
int VideoWindow::playBackSpeed() const
{
    qxtLog->trace(Q_FUNC_INFO);

    return (int)_player->playBackSpeed();
}

/*! @brief Sets the speed to play media back at
 *  @param speed the speed to play media back at
 */
void VideoWindow::setPlayBackSpeed(const int speed)
{
    qxtLog->trace(Q_FUNC_INFO);

    _player->setPlayBackSpeed((float)speed);
}

/*! @brief Returns the length of the media
 *  @return the length of the media or -1 if the media has indeterminate length
 */
float VideoWindow::mediaLength() const
{
    qxtLog->trace(Q_FUNC_INFO);

    return _player->mediaLength();
}

/*! @brief Returns the current position in the media
 *  @return The current position in the media
 */
float VideoWindow::position() const
{
    qxtLog->trace(Q_FUNC_INFO);

    return _player->mediaPosition();
}

/*! @brief Sets the current position in the media
 *  @param position The position in the media
 */
void VideoWindow::setPosition(const float position)
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::setPosition
}

/*! @brief Returns the audio track currently being played
 *  @return The audio track currently being played
 */
int VideoWindow::audioTrack() const
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::audioTrack()
    return 0;
}

/*! @brief Sets the audio track to play
 *  @param track The audio track to play
 */
void VideoWindow::setAudioTrack(const int track)
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::setAudioTrack
}

/*! @brief Returns the subtitle track currently being used
 *  @return The subtitle track currently being used
 */
int VideoWindow::subtitleTrack() const
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::subtitleTrack()
    return 0;
}

/*! @brief Sets the subtitle track to use
 *  @param track The subtitle track to use
 */
void VideoWindow::setSubtitleTrack(const int track)
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::setSubtitleTrack
}

/*! @brief Returns whether subtitles are being shown or not
 *  @return Whether subtitles are being shown or not
 */
bool VideoWindow::subtitlesShown() const
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::subtitlesShown()
    return false;
}

/*! @brief Sets whether subtitles are being shown or not
 *  @param show whether subtitles are being shown or not
 */
void VideoWindow::setSubtitlesShown(const bool show)
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::setSubtitlesShown
}

/*! @brief Returns whether video is shown or not
 *  @return Whether video is shown or not
 */
bool VideoWindow::videoShown() const
{
    qxtLog->trace(Q_FUNC_INFO);

    return _player->isVisible();
}

/*! @brief Sets whether video is shown or not
 *  @param shown Whether video is shown or not
 */
void VideoWindow::setVideoShown(const bool shown)
{
    qxtLog->trace(Q_FUNC_INFO);

    _player->setVisible(shown);
}

/*! @brief Returns whether the video is being shown fullscreen or not
 *  @return Whether the video is being shown fullscreen or not
 */
bool VideoWindow::fullscreen() const
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::fullscreen()
    return false;
}

/*! @brief Sets whether the video is being shown fullscreen or not
 *  @param fullscreen Whether the video is being shown fullscreen or not
 */
void VideoWindow::setFullscreen(const bool fullscreen)
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::setFullscreen
}

/*! @brief Returns the z-index of the video window
 *  @return The z-index of the video window
 */
unsigned int VideoWindow::zIndex() const
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::zIndex()
    return 110;
}

/*! @brief Sets the z-index of the video window
 *  @param zIndex the z-index of the video window
 */
void VideoWindow::setZIndex(const unsigned int zIndex)
{
    qxtLog->trace(Q_FUNC_INFO);

    #warning TODO: Implement VideoWindow::setZIndex
}

/*! @brief  Resets the video window back to the default state
 *
 *  The default state is:
 *      - media stopped
 *      - volume at 50
 *      - audio not muted
 *      - video shown
 *      - video not fullscreen
 *      - subtitle not shown
 */
void VideoWindow::Reset()
{
    qxtLog->trace(Q_FUNC_INFO);

    this->Stop();
    this->setVolume(50);
    this->setMute(false);
    this->setFullscreen(false);
    this->setVideoShown(true);
    this->setSubtitlesShown(false);
}

/*! @brief  Plays a media URL in the video window
 *
 *  The media URL can be any that VLC supports, examples are:
 *      - c:\\filename.avi - For playback of files
 *      - dvd://d:\ - Playback the DVD in the d: drive
 *      - cdda://D:\ - The audio cd in the d: drive
 *      - vcd://D:\ - The vcd in the d: drive
 *      - http://www.example.com/stream.avi - A HTTP Stream
 *      - rtp://@:1234 - An RDP stream sent to port 1234 on this machine
 *      - udp://@:1234 - A UDP stream sent to port 1234 on this machine
 *      - mms://mms.example.com/stream.asx - An MMS Stream
 *      - rtsp://server.example.com:8080/Video_Name - A video from an RTSP server
 *      - http://www.youtube.com/watch?v=gg64x - A youtube video
 *
 *  @param url The URL to play
 */
void VideoWindow::Play(const QString url)
{
    qxtLog->trace(Q_FUNC_INFO);

    _currentUrl.setUrl(url);
    _player->play(url);
}

/*! @brief Stops playback of the media currently playing */
void VideoWindow::Stop()
{
    qxtLog->trace(Q_FUNC_INFO);

    _currentUrl.setUrl("");
    _player->stop();
}

/*! @brief Pauses playback of media if possible */
void VideoWindow::Pause()
{
    qxtLog->trace(Q_FUNC_INFO);
    #warning: TODO Implement VideoWindow::Pause()
}

/*! @brief Resumes playback of media when paused */
void VideoWindow::Resume()
{
    qxtLog->trace(Q_FUNC_INFO);
    #warning: TODO Implement VideoWindow::Resume()
}

/*! @brief A structure containing information about the streams in the media
 *
 *  You can control the areas of information that are returned using the parameters.
 *  The structure of the object returns is the following:
 *      - audio
 *          - tracks - An array of audio tracks
 *              - id - The track ID
 *              - name - A textual name for the audio track
 *      - subtitle
 *          - tracks - An array of subtitle tracks
 *              - id - The track ID
 *              - name - A textual name for the subtitle track
 *      - video
 *          - tracks - An array of video tracks
 *              - id - The track ID
 *              - name - A textual name for the video track
 *
 *  @param audioStreams Whether to return information on audio streams
 *  @param subtitleStreams Whether to return information on subtitle streams
 *  @param videoStreams Whether to return information on the video streams
 *  @return A structure containing the stream information
 */
QVariantMap VideoWindow::GetStreamInformation(const bool audioStreams, const bool subtitleStreams, const bool videoStreams) const
{
    qxtLog->trace(Q_FUNC_INFO);

    QVariantMap information;

    if(audioStreams)
        information.insert("audio", _player->getAudioStreamInformation());

    if(subtitleStreams)
        information.insert("subtitle", _player->getSubtitleStreamInformation());

    if(videoStreams)
        information.insert("video", _player->getVideoStreamInformation());

    return information;
}

/*! @brief Sets the size of the video window
 *  @param width The width of the video window
 *  @param height The height of the video window
 */
void VideoWindow::SetSize(int width, int height)
{
    qxtLog->trace(Q_FUNC_INFO);

    _player->resize(width, height);
}

/*! @brief Sets the position of the video window
 *  @param x The x coordinate of the video window
 *  @param y The y coordinate of the video window
 */
void VideoWindow::SetPosition(int x, int y)
{
    qxtLog->trace(Q_FUNC_INFO);

    _player->move(x, y);
}

/*! @brief Sets the position and dimensions of the video window
 *  @param x The x coordinate of the video window
 *  @param y The y coordinate of the video window
 *  @param width The width of the video window
 *  @param height The height of the video window
 */
void VideoWindow::SetGeometry(int x, int y, int width, int height)
{
    qxtLog->trace(Q_FUNC_INFO);

    _player->setGeometry(x, y, width, height);
}
