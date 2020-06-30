/*
Loading
Mix_GetNumMusicDecoders     Number of music format types that can be decoded
Mix_GetMusicDecoder         Name of enumerated music format type decoder
Mix_LoadMUS	  	            Load a music file into a Mix_Music
Free
Mix_FreeMusic	  	        Free a Mix_Music
Playing
Mix_PlayMusic               Play music, with looping
Mix_FadeInMusic             Play music, with looping, and fade in
Mix_FadeInMusicPos          Play music from a start point, with looping, and fade in
Mix_HookMusic               Hook for a custom music player
Settings
Mix_VolumeMusic	  	        Set music volume
Mix_PauseMusic	  	        Pause music
Mix_ResumeMusic	  	        Resume paused music
Mix_RewindMusic	  	        Rewind music to beginning
Mix_SetMusicPosition        Set position of playback in stream
Mix_SetMusicCMD	  	        Use external program for music playback
Stopping
Mix_HaltMusic	  	        Stop music playback
Mix_FadeOutMusic	  	    Stop music, with fade out
Mix_HookMusicFinished       Set a callback for when music stops
Info
Mix_GetMusicType	  	    Get the music encoding type
Mix_PlayingMusic	  	    Test whether music is playing
Mix_PausedMusic	  	        Test whether music is paused
Mix_FadingMusic	  	        Get status of current music fade activity
Mix_GetMusicHookData        Retrieve the Mix_HookMusic arguments
*/
#include "sound_system.h"

#include "SDL_mixer.h"

#include "logger.h"
#include "lua_wrapper.h"

namespace stren
{
SoundSystem::SoundSystem()
    : m_isReady(false)
{
}

void SoundSystem::initialize()
{
    if (!m_isReady)
    {
        Logger("green") << "[Engine] Initialize sound system";
        if (-1 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096))
        {
            const int flags = MIX_INIT_OGG | MIX_INIT_MP3;
            const int initted = Mix_Init(flags);
            if ((initted & flags) == flags)
            {
                Logger("green") << "[Engine] Initialize sounds repository";
                m_soundsRepo.initialize(lua::Table("Sounds"));
                Logger("green") << "[Engine] Initialize music repository";
                m_musicRepo.initialize(lua::Table("Music"));
            }
            m_isReady = true;
        }
    }
}

void SoundSystem::release()
{
    if (m_isReady)
    {
        m_musicRepo.release();
        m_soundsRepo.release();

        Logger("green") << "[Engine] Destroy SDL Mixer";
        while (Mix_Init(0))
        {
            Mix_Quit();
        }
        Mix_CloseAudio();
        m_isReady = false;
    }
}


bool SoundSystem::playSound(const std::string & id, const int loop, const int channel)
{
    Sound & sound = m_soundsRepo.getSound(id);
    if (!sound.isLoaded())
    {
        sound.load();
    }
    if (sound.isLoaded())
    {
        return sound.play(loop, channel);
    }
    return false;
}

bool SoundSystem::playMusic(const std::string & id, const int loop)
{
    Music & music = m_musicRepo.getMusic(id);
    if (!music.isValid())
    {
        music.load();
    }
    if (music.isValid())
    {
        return music.play(loop);
    }
    return false;
}

void SoundSystem::stopMusic()
{
    if (m_isReady)
    {
        Music().stop();
    }
}

bool SoundSystem::isMusicPaused() const
{
    return m_isReady && 1 == Mix_PausedMusic();
}

bool SoundSystem::isMusicPlaying() const
{
    return m_isReady && 1 == Mix_PlayingMusic();
}

void SoundSystem::pauseMusic()
{
    if (m_isReady)
    {
        Mix_PauseMusic();
    }
}

void SoundSystem::resumeMusic()
{
    if (m_isReady)
    {
        Mix_ResumeMusic();
    }
}
} // stren