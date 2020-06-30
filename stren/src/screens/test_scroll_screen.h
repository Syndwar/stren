#ifndef STREN_TEST_SCROLL_SCREEN_H
#define STREN_TEST_SCROLL_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
///
/// class OptionsScreen
///
class TestScrollScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    TestScrollScreen();
    ///
    /// Destructor
    ///
    virtual ~TestScrollScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void onJumpBtnClick();
    ///
    /// @todo
    ///
    void onScrollBtnClick();
};
} // stren

#endif // STREN_TEST_SCROLL_SCREEN_H
