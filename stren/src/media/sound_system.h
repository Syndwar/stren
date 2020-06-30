#ifndef STREN_SOUND_SYSTEM_H
#define STREN_SOUND_SYSTEM_H

#include "string_ext.h"
#include "sounds_repository.h"
#include "music_repository.h"

namespace stren
{
///
/// class SoundSystem
///
class SoundSystem
{
private:
    bool             m_isReady;    ///< flag if all repositories are loaded and ready
    SoundsRepository m_soundsRepo; ///< sound repository
    MusicRepository  m_musicRepo;  ///< music repository
public:
    ///
    /// Constructor
    ///
    SoundSystem();
    ///
    /// initialize sound system
    ///
    void initialize();
    ///
    /// Destroy SDL Mixer and release resources
    ///
    void release();
    ///
    /// play sound sample, using given channel and repeating it 'loop' number of times
    ///
    bool playSound(const std::string & id, const int loop = -1, const int channel = -1);
    ///
    /// play music track, repeating it 'loop' number of times
    ///
    bool playMusic(const std::string & id, const int loop = -1);
    ///
    /// stop all music playing
    ///
    void stopMusic();
    ///
    /// returns if music is paused
    ///
    bool isMusicPaused() const;
    ///
    /// returns if music is playing
    ///
    bool isMusicPlaying() const;
    ///
    /// resumes music playing
    ///
    void resumeMusic();
    ///
    /// pauses current music playing
    ///
    void pauseMusic();
};

} // stren

#endif // STREN_SOUND_SYSTEM_H