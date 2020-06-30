#ifndef STREN_TEST_SCREEN_H
#define STREN_TEST_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
class TestScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    TestScreen();
    ///
    /// Destructor
    ///
    virtual ~TestScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void toTestPrimitiveScreen();
    ///
    /// @todo
    ///
    void toTestFaderScreen();
    ///
    /// @todo
    ///
    void toTestSoundScreen();
    ///
    /// @todo
    ///
    void toTestWidgetsScreen();
    ///
    /// @todo
    ///
    void toTestScrollScreen();
    ///
    /// @todo
    ///
    void toTestFontScreen();
    ///
    /// @todo
    ///
    void toBattlefieldScreen();
};
} // stren

#endif // STREN_TEST_SCREEN_H
