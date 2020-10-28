#ifndef STREN_SOUND_H
#define STREN_SOUND_H

#include "common/string_ext.h"

struct Mix_Chunk;

namespace stren
{
///
/// class Sound holds information about sound track
///
class Sound
{
private:
    Mix_Chunk * m_chunk;           ///< pointer to the SDL sound object
    std::string m_id;              ///< sound sample id
    std::string m_filename;        ///< path to the sound file
public:
    ///
    /// Default Constructor
    ///
    Sound();
    ///
    /// Constructor
    ///
    Sound(const std::string & id, const std::string & filename);
    ///
    /// Copy Constructor
    ///
    Sound(const Sound & sound) = delete;
    ///
    /// Move Constructor
    ///
    Sound(Sound && sound);
    ///
    /// Destructor
    ///
    ~Sound();
    ///
    /// Copy Assign Operator
    ///
    Sound & operator=(const Sound & sound) = delete;
    ///
    /// Move Assign Operator
    ///
    Sound & operator=(Sound && sound);
    ///
    /// Loads SDL sound object into the memory
    ///
    void load();
    ///
    /// Destroys SDL sound object
    ///
    void release();
    ///
    /// Play sound sample
    ///
    bool play(const int loop, const int channel);
    ///
    /// Returns if sound sample is loaded and SDL sound object exists
    ///
    bool isLoaded() const;
};
} // stren

#endif // STREN_SOUND_H
