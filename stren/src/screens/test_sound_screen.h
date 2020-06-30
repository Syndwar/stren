#ifndef STREN_TEST_SOUND_SCREEN_H 
#define STREN_TEST_SOUND_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
///
/// class MainScreen
///
class TestSoundScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    TestSoundScreen();
    ///
    /// Destructor
    ///
    virtual ~TestSoundScreen();
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void onPlayMusicBtnClick();
    ///
    /// @todo
    ///
    void onStopMusicBtnClick();
    ///
    /// @todo
    ///
    void onPlaySoundBtnClick();
};
} // stren
#endif // STREN_TEST_SOUND_SCREEN_H
