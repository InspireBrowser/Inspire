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
 * Filename: VideoWindow.h
 * Class: VideoWindow
 * Description: Provides the JS bindings for controlling a video window
 * Created: 17/12/2010
 * ChangeLog:
 *     17/12/2010 - Mike - Initial Creation
 */

#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QVariantMap>
#include <QUrl>
#include <QRect>
#include <QxtLogger>

#include "JavascriptBinding.h"

class QVlcPlayer;

/*! @brief  Provides the JavaScript Binding for interfacing with a Video window
 *          Class that interacts witha video window with functions for manipulating
 *          the window's position and size and the media that's playing.
 */
class VideoWindow : public QObject, public JavascriptBinding
{
    Q_OBJECT
private:
    /*! @brief The VLC Player widget to be inserted */
    QVlcPlayer* _player;
    /*! @brief The current URL that's playing */
    QUrl _currentUrl;

public:
    /*! @brief Constructs a video window javascript object
     *  @param parent The parent object
     */
    explicit VideoWindow(QObject* parent = 0);

    /*! @brief Destructor for tidying up the video window */
    ~VideoWindow();

    /*! @brief Returns the current URL being played, blank if nothing is playing
     *  @return The current URL being played
     */
    QUrl currentUrl() const {
        qxtLog->trace(Q_FUNC_INFO);
        return _currentUrl;
    }
    /*! @brief Property for retrieving the current URL */
    Q_PROPERTY(QUrl currentUrl READ currentUrl STORED false);

    /*! @brief Returns whether any media is currently being played
     *  @return Whether any media is currently being played
     */
    bool isPlaying() const;
    /*! Property for querying whether any media is being played */
    Q_PROPERTY(bool isPlaying READ isPlaying STORED false);

    /*! @brief Returns the volume the media is being played at
     *  @return The volume the media is being played at
     */
    int volume() const;
    /*! @brief Sets the volume to playback media at
     *  @param volume The volume between 0 and 200
     */
    void setVolume(const int volume);
    /*! @brief Property for getting and setting the volume */
    Q_PROPERTY(int volume READ volume WRITE setVolume STORED false);

    /*! @brief Returns whether the video playback is muted or not
     *  @return Whether the video playback is muted or not
     */
    bool muted() const;
    /*! @brief Sets whether the media's audio is muted or not
     *  @param muted Whether the media's audio is muted or not
     */
    void setMute(const bool muted);
    /*! @brief Property for getting and setting whether the media's audio is muted or not */
    Q_PROPERTY(bool mute READ muted WRITE setMute STORED false);

    /*! @brief Returns the speed that media plays at
     *  @return the speed to play media back at
     */
    int playBackSpeed() const;
    /*! @brief Sets the speed to play media back at
     *  @param speed the speed to play media back at
     */
    void setPlayBackSpeed(const int speed);
    /*! @brief Property for getting and setting the speed that media is played back at */
    Q_PROPERTY(int playBackSpeed READ playBackSpeed WRITE setPlayBackSpeed STORED false);

    /*! @brief Returns the length of the media
     *  @return the length of the media or -1 if the media has indeterminate length
     */
    float mediaLength() const;
    /*! @brief Property for retrieving the length of the media */
    Q_PROPERTY(float mediaLength READ mediaLength STORED false);

    /*! @brief Returns the current position in the media
     *  @return The current position in the media
     */
    float position() const;
    /*! @brief Sets the current position in the media
     *  @param position The position in the media
     */
    void setPosition(const float position);
    /*! @brief Property for setting and getting the position in the media */
    Q_PROPERTY(float position READ position WRITE setPosition STORED false);

    /*! @brief Returns the audio track currently being played
     *  @return The audio track currently being played
     */
    int audioTrack() const;
    /*! @brief Sets the audio track to play
     *  @param track The audio track to play
     */
    void setAudioTrack(const int track);
    /*! @brief Gets and sets the audio track playing */
    Q_PROPERTY(int audioTrack READ audioTrack WRITE setAudioTrack STORED false);

    /*! @brief Returns the subtitle track currently being used
     *  @return The subtitle track currently being used
     */
    int subtitleTrack() const;
    /*! @brief Sets the subtitle track to use
     *  @param track The subtitle track to use
     */
    void setSubtitleTrack(const int track);
    /*! @brief Gets and sets the subtitle track being used */
    Q_PROPERTY(int subtitleTrack READ subtitleTrack WRITE setSubtitleTrack STORED false);

    /*! @brief Returns whether subtitles are being shown or not
     *  @return Whether subtitles are being shown or not
     */
    bool subtitlesShown() const;
    /*! @brief Sets whether subtitles are being shown or not
     *  @param show whether subtitles are being shown or not
     */
    void setSubtitlesShown(const bool show);
    /*! @brief Property for getting and setting whether subtitles are being shown or not */
    Q_PROPERTY(bool subtitlesShown READ subtitlesShown WRITE setSubtitlesShown STORED false);

    /*! @brief Returns whether video is shown or not
     *  @return Whether video is shown or not
     */
    bool videoShown() const;
    /*! @brief Sets whether video is shown or not
     *  @param shown Whether video is shown or not
     */
    void setVideoShown(const bool shown);
    /*! @brief Gets and sets whether the video is shown or not */
    Q_PROPERTY(bool videoShown READ videoShown WRITE setVideoShown STORED false);

    /*! @brief Returns whether the video is being shown fullscreen or not
     *  @return Whether the video is being shown fullscreen or not
     */
    bool fullscreen() const;
    /*! @brief Sets whether the video is being shown fullscreen or not
     *  @param fullscreen Whether the video is being shown fullscreen or not
     */
    void setFullscreen(const bool fullscreen);
    /*! @brief Property for getting and setting whether the video is being shown fullscreen or not */
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen STORED false);

    /*! @brief Returns the z-index of the video window
     *  @return The z-index of the video window
     */
    unsigned int zIndex() const;
    /*! @brief Sets the z-index of the video window
     *  @param zIndex the z-index of the video window
     */
    void setZIndex(const unsigned int zIndex);
    /*! @brief Property for getting and setting the z-index of the video window */
    Q_PROPERTY(unsigned int zIndex READ zIndex WRITE setZIndex STORED false);

signals:
    #warning TODO: Implement event detection and emitting
    /*! @brief Emitted when an Igmp Stream starts */
    void onIgmpStreamStart();
    /*! @brief Emitted when an Igmp Stream stops */
    void onIgmpStreamStop();

public slots:
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
    void Reset();

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
    void Play(const QString url);

    /*! @brief Stops playback of the media currently playing */
    void Stop();

    /*! @brief Pauses playback of media if possible */
    void Pause();

    /*! @brief Resumes playback of media when paused */
    void Resume();

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
    QVariantMap GetStreamInformation(const bool audioStreams = true, const bool subtitleStreams = true, const bool videoStreams = false) const;

    /*! @brief Sets the size of the video window
     *  @param width The width of the video window
     *  @param height The height of the video window
     */
    void SetSize(int width, int height);

    /*! @brief Sets the position of the video window
     *  @param x The x coordinate of the video window
     *  @param y The y coordinate of the video window
     */
    void SetPosition(int x, int y);

    /*! @brief Sets the position and dimensions of the video window
     *  @param x The x coordinate of the video window
     *  @param y The y coordinate of the video window
     *  @param width The width of the video window
     *  @param height The height of the video window
     */
    void SetGeometry(int x, int y, int width, int height);
};

#endif // VIDEOWINDOW_H
