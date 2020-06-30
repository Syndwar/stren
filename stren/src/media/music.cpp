#include "music.h"

#include "SDL_mixer.h"

namespace stren
{
Music::Music()
    : m_track(nullptr)
{
}

Music::Music(const std::string & id, const std::string & filename)
    : m_id(id)
    , m_filename(filename)
    , m_track(nullptr)
{
}

Music::~Music()
{
    release();
}

Music::Music(Music && music)
    : m_id(std::move(music.m_id))
    , m_filename(std::move(music.m_filename))
    , m_track(music.m_track)
{
    music.m_track = nullptr;
}

Music & Music::operator=(Music && music)
{
    m_id = std::move(music.m_id);
    m_filename = std::move(music.m_filename);
    m_track = music.m_track;
    music.m_track = nullptr;
    return *this;
}


void Music::load()
{
    if (!m_track)
    {
        m_track = Mix_LoadMUS(m_filename.c_str());
    }
}

bool Music::play(const int loop)
{
    if (m_track)
    {
        return -1 != Mix_PlayMusic(m_track, loop);
    }
    return false;
}

void Music::stop()
{
    Mix_HaltMusic();
}

bool Music::isValid() const
{
    return nullptr != m_track;
}

void Music::release()
{
    if (m_track)
    {
        Mix_FreeMusic(m_track);
        m_track = nullptr;
    }
}

bool Music::isPlaying() const
{
    return 1 == Mix_PlayingMusic();
}

} // stren