#ifndef STREN_MUSIC_H
#define STREN_MUSIC_H

#include "string_ext.h"

typedef struct _Mix_Music Mix_Music;

namespace stren
{
///
/// class Music
///
class Music
{
private:
    Mix_Music * m_track;             ///< loaded track
    std::string m_id;                ///< music identification string
    std::string m_filename;          ///< file where music track is stored
public:
    ///
    /// Default Constructor
    ///
    Music();
    ///
    /// Constructor
    ///
    Music(const std::string & id, const std::string & filename);
    ///
    /// Copy Constructor
    ///
    Music(const Music & music) = delete;
    ///
    /// Move Constructor
    ///
    Music(Music && music);
    ///
    /// Copy Assign Operator
    ///
    Music & operator=(const Music & sound) = delete;
    ///
    /// Move Assign Operator
    ///
    Music & operator=(Music && sound);
    ///
    /// Destructor
    ///
    ~Music();
    ///
    /// @todo
    ///
    void load();
    ///
    /// @todo
    ///
    bool play(const int loop = -1);
    ///
    /// @todo
    ///
    bool isValid() const;
    ///
    /// @todo
    ///
    void stop();
    ///
    /// @todo
    ///
    bool isPlaying() const;
    ///
    /// @todo
    ///
    void release();
};
} // stren

#endif // STREN_MUSIC_H