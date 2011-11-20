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
 * Filename: QVlcPlayer.cpp
 * Class: QVlcPlayer
 * Description: A Qt component for embedding VLC into an application
 */

#include "QVlcPlayer.h"

/*! @brief Constructor for creating a QVlcPlayer object
 *  @param  parent  The parent object
 */
QVlcPlayer::QVlcPlayer(QWidget* parent) :
    QWidget(parent),
    _isPlaying(false)
{
    //preparation of the vlc command
    const char* const vlc_args[] = {
        "-I", "dummy",
        "--ignore-config",
        "--plugin-path=vlc_plugins",
        "--no-osd"
    };

    //create a new libvlc instance
    _vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    if(!_vlcInstance) {
        throw QString(libvlc_errmsg());
    }

    // Create a media player playing environement
    _vlcMediaPlayer = libvlc_media_player_new (_vlcInstance);
    if(!_vlcMediaPlayer) {
        throw QString(libvlc_errmsg());
    }
}

/*! @brief Destructor for cleaning up libVlc after use */
QVlcPlayer::~QVlcPlayer()
{
    libvlc_media_player_stop (_vlcMediaPlayer);
    libvlc_media_player_release (_vlcMediaPlayer);
    libvlc_release (_vlcInstance);
}

/*! @brief Returns the current playback speed of the media
 *  @return the current playback speed of the media
 */
float QVlcPlayer::playBackSpeed() const
{
    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia == NULL) {
        return 0;
    }

    return libvlc_media_player_get_rate(_vlcMediaPlayer);
}

/*! @brief Sets the playback speed for the current media
 *  @param speed The speed to play content back at
 */
void QVlcPlayer::setPlayBackSpeed(const float speed)
{
    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia != NULL) {
        if(libvlc_media_player_set_rate(_vlcMediaPlayer, speed) == -1) {
            throw QString(libvlc_errmsg());
        }
    }
}

/*! @brief Returns the audio volume level of playback
 *  @return the audio volume level of playback
 */
int QVlcPlayer::volume() const
{
    return libvlc_audio_get_volume(_vlcMediaPlayer);
}

/*! @brief Sets the audio volume level for playback
 *  @param volume The audio volume level for playback
 */
void QVlcPlayer::setVolume(const int volume)
{
    //clamp volume to range MIN_VOLUME >= x <= MAX_VOLUME
    int clampedVolume = volume < MIN_VOLUME ? MIN_VOLUME : (volume > MAX_VOLUME ? MAX_VOLUME : volume);

    if(libvlc_audio_set_volume (_vlcMediaPlayer, clampedVolume) != 0) {
        throw QString(libvlc_errmsg());
    }
}

/*! @brief Returns whether audio output is currently muted or not
 *  @return Whether audio output is currently muted or not
 */
bool QVlcPlayer::muted() const
{
    return libvlc_audio_get_mute(_vlcMediaPlayer) ? true : false;
}

/*! @brief Sets whether audio output is muted or not
 *  @param muted Whether audio output is muted or not
 */
void QVlcPlayer::setMute(const bool muted)
{
    libvlc_audio_set_mute(_vlcMediaPlayer, muted);
}

/*! @brief Returns the current media length
 *  @return The current media length
 */
float QVlcPlayer::mediaLength() const
{
    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia == NULL) {
        return -1;
    }

    return libvlc_media_player_get_length(_vlcMediaPlayer);
}

/*! @brief Returns the current position in the media
 *  @return The current position in the media
 */
float QVlcPlayer::mediaPosition() const
{
    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia == NULL) {
        return -1;
    }

    float position = libvlc_media_player_get_position(_vlcMediaPlayer);
    if(position == -1) {
        throw QString(libvlc_errmsg());
    } else {
        return position * POSITION_RESOLUTION;
    }
}

/*! @brief Sets the current position in the media
 *  @param position The current position in the media
 */
void QVlcPlayer::setMediaPosition(const float position)
{
    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia == NULL) {
        return;
    }

    float pos = (float)(position) / (float)POSITION_RESOLUTION;
    libvlc_media_player_set_position (_vlcMediaPlayer, pos);
}

/*! @brief Returns information on the video streams in the current media
 *  @return A structure describing the video streams in the current media
 */
QVariantMap QVlcPlayer::getVideoStreamInformation() const
{
    QVariantMap information;

    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia == NULL) {
        return information;
    }

    //get the track information
    libvlc_track_description_t* description = libvlc_video_get_track_description(_vlcMediaPlayer);
    information.insert("tracks", processTrackInformation(description));
    libvlc_track_description_release(description);

    return information;
}

/*! @brief Returns information on the audio streams in the current media
 *  @return A structure describing the audio streams in the current media
 */
QVariantMap QVlcPlayer::getAudioStreamInformation() const
{
    QVariantMap information;

    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia == NULL) {
        return information;
    }

    //get the track information
    libvlc_track_description_t* description = libvlc_audio_get_track_description(_vlcMediaPlayer);
    information.insert("tracks", processTrackInformation(description));
    libvlc_track_description_release(description);

    return information;
}

/*! @brief Returns information on the subtitle streams in the current media
 *  @return A structure describing the subtitle streams in the current media
 */
QVariantMap QVlcPlayer::getSubtitleStreamInformation() const
{
    QVariantMap information;

    // It's possible that the vlc doesn't play anything, so check before
    libvlc_media_t* curMedia = libvlc_media_player_get_media (_vlcMediaPlayer);
    if (curMedia == NULL) {
        return information;
    }

    //get the track information
    libvlc_track_description_t* description = libvlc_video_get_spu_description(_vlcMediaPlayer);
    information.insert("tracks", processTrackInformation(description));
    libvlc_track_description_release(description);

    return information;
}

/*! @brief Processes track information returned by libvlc
 *         Takes the track information returned by libvlc and returns it in a QVariantList
 *         formatted for use by get*StreamInformation
 *  @param description The track information returned by libvlc
 *  @return A QVariantList containing information on the tracks
 */
QVariantList QVlcPlayer::processTrackInformation(libvlc_track_description_t* description) const
{
    QVariantList tracks;
    while(description) {
        QVariantMap track;
        track.insert("id", description->i_id);
        track.insert("name", description->psz_name);
        tracks.append(track);

        description = description->p_next;
    }
    return tracks;
}

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
void QVlcPlayer::play(QString mrl)
{
    libvlc_media_t* media = libvlc_media_new_location (_vlcInstance, mrl.toAscii());
    if(!media) {
        throw QString(libvlc_errmsg());
    }

    libvlc_media_player_set_media (_vlcMediaPlayer, media);
    libvlc_media_release(media);

#if defined(Q_OS_WIN)
    libvlc_media_player_set_hwnd(_vlcMediaPlayer, this->winId()); // for vlc 1.0
#elif defined(Q_OS_MAC)
    libvlc_media_player_set_agl (_vlcMediaPlayer, this->winId()); // for vlc 1.0
#else //Linux
    libvlc_media_player_set_xwindow (_vlcMediaPlayer, this->winId()); // for vlc 1.0
#endif

    /* Play */
    if(libvlc_media_player_play (_vlcMediaPlayer) != 0) {
        throw QString(libvlc_errmsg());
    }

    _isPlaying = true;
}

/*! @brief Stops any playback of the media */
void QVlcPlayer::stop()
{
    libvlc_media_player_stop(_vlcMediaPlayer);
    _isPlaying = false;
}
