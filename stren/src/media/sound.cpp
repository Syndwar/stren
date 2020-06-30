#include "sound.h"

#include "SDL_mixer.h"

namespace stren
{
Sound::Sound()
    : m_chunk(nullptr)
{
}

Sound::Sound(const std::string & id, const std::string & filename)
    : m_chunk(nullptr)
    , m_id(id)
    , m_filename(filename)
{
}

Sound::~Sound()
{
    release();
}

Sound::Sound(Sound && sound)
    : m_chunk(sound.m_chunk)
    , m_id(std::move(sound.m_id))
    , m_filename(std::move(sound.m_filename))
{
    sound.m_chunk = nullptr;
}

Sound & Sound::operator=(Sound && sound)
{
    m_id = std::move(sound.m_id);
    m_filename = std::move(sound.m_filename);
    m_chunk = sound.m_chunk;
    sound.m_chunk = nullptr;
    return *this;
}

void Sound::load()
{
    if (!m_filename.empty() && !m_chunk)
    {
        m_chunk = Mix_LoadWAV(m_filename.c_str());
    }
}

void Sound::release()
{
    if (m_chunk)
    {
        Mix_FreeChunk(m_chunk);
        m_chunk = nullptr;
    }
}

bool Sound::play(const int loop, const int channel)
{
    if (m_chunk)
    {
        return -1 != Mix_PlayChannel(channel, m_chunk, loop);
    }
    return false;
}

bool Sound::isLoaded() const
{
    return nullptr != m_chunk;
}
} // stren