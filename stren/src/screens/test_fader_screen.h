#ifndef STREN_TEST_FADER_SCREEN_H
#define STREN_TEST_FADER_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
///
/// class TestFaderScreen
///
class TestFaderScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    TestFaderScreen();
    ///
    /// Destructor
    ///
    virtual ~TestFaderScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void onFadeSpeedUpBtnClick();
    ///
    /// @todo
    ///
    void onFadeSpeedDownBtnClick();
    ///
    /// @todo
    ///
    void onFadeInBtnClick();
    ///
    /// @todo
    ///
    void onFadeOutBtnClick();
};
} // stren

#endif // STREN_TEST_FADER_SCREEN_H
