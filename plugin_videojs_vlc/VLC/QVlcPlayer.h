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
 * Filename: QVlcPlayer.h
 * Class: QVlcPlayer
 * Description: A Qt component for embedding VLC into an application
 * Created: 27/11/2010
 * ChangeLog:
 *     13/11/2010 - mike - Initial Creation
 */

#ifndef QVLC_PLAYER_H
#define QVLC_PLAYER_H

#include <vlc/vlc.h>

#include <QWidget>
#include <QVariantMap>

#define POSITION_RESOLUTION 10000
#define MAX_VOLUME 200
#define MIN_VOLUME 0

/*! @brief A widget for playing back media via libvlc
 *         Encapsulates the setting up and interactions with libvlc and enables the
 *         rendering of the video in a Qt widget. Provides functions for querying and
 *         manipulating the stream being played.
 */
class QVlcPlayer : public QWidget
{
    Q_OBJECT

private:
    /*! @brief The instance of libvlc to use */
    libvlc_instance_t* _vlcInstance;
    /*! @brief The vlc media player for this widget */
    libvlc_media_player_t* _vlcMediaPlayer;
    /*! @brief whether something is currently being played or not */
    bool _isPlaying;

public:
    /*! @brief Constructor for creating a QVlcPlayer object
     *  @param  parent  The parent object
     */
    QVlcPlayer(QWidget* parent = 0);

    /*! @brief Destructor for cleaning up libVlc after use */
    ~QVlcPlayer();

    /*! @brief Returns whether anything is currently being played
     *  @return Whether anything is currently being played
     */
    bool isPlaying() const {
        return _isPlaying;
    }
    /*! @brief Property for querying whether anything is being played */
    Q_PROPERTY(bool isPlaying READ isPlaying STORED false);

    /*! @brief Returns the current playback speed of the media
     *  @return the current playback speed of the media
     */
    float playBackSpeed() const;
    /*! @brief Sets the playback speed for the current media
     *  @param speed The speed to play content back at
     */
    void setPlayBackSpeed(const float speed);
    /*! @brief Property for getting and setting the playback speed of the current media */
    Q_PROPERTY(float playBackSpeed READ playBackSpeed WRITE setPlayBackSpeed STORED false);

    /*! @brief Returns the audio volume level of playback
     *  @return the audio volume level of playback
     */
    int volume() const;
    /*! @brief Sets the audio volume level for playback
     *  @param volume The audio volume level for playback
     */
    void setVolume(const int volume);
    /*! @brief Property for getting and setting the audio volume level */
    Q_PROPERTY(int volume READ volume WRITE setVolume STORED false);

    /*! @brief Returns whether audio output is currently muted or not
     *  @return Whether audio output is currently muted or not
     */
    bool muted() const;
    /*! @brief Sets whether audio output is muted or not
     *  @param muted Whether audio output is muted or not
     */
    void setMute(const bool muted);
    /*! @brief Property for getting and setting whether audio output is muted or not */
    Q_PROPERTY(bool muted READ muted WRITE setMute STORED false);

    /*! @brief Returns the current media length
     *  @return The current media length
     */
    float mediaLength() const;
    /*! @brief Property for accessing the current media length */
    Q_PROPERTY(float mediaLength READ mediaLength STORED false);

    /*! @brief Returns the current position in the media
     *  @return The current position in the media
     */
    float mediaPosition() const;
    /*! @brief Sets the current position in the media
     *  @param position The current position in the media
     */
    void setMediaPosition(const float position);
    /*! @brief Property for getting and setting the current position in the media */
    Q_PROPERTY(float mediaPosition READ mediaPosition WRITE setMediaPosition STORED false);

    /*! @brief Returns information on the video streams in the current media
     *  @return A structure describing the video streams in the current media
     */
    QVariantMap getVideoStreamInformation() const;
    /*! @brief Returns information on the audio streams in the current media
     *  @return A structure describing the audio streams in the current media
     */
    QVariantMap getAudioStreamInformation() const;
    /*! @brief Returns information on the subtitle streams in the current media
     *  @return A structure describing the subtitle streams in the current media
     */
    QVariantMap getSubtitleStreamInformation() const;

private:
    /*! @brief Processes track information returned by libvlc
     *         Takes the track information returned by libvlc and returns it in a QVariantList
     *         formatted for use by get*StreamInformation
     *  @param description The track information returned by libvlc
     *  @return A QVariantList containing information on the tracks
     */
    QVariantList processTrackInformation(libvlc_track_description_t* description) const;

public slots:
    /*! @brief Instructs VLC to start playing a media URL
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
     *  @param mrl The URL to play
     */
    void play(QString mrl);

    /*! @brief Stops any playback of the media */
    void stop();
};
#endif
