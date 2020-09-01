#ifndef STREN_TEST_BATTLE_FIELDSCREEN_H
#define STREN_TEST_BATTLE_FIELDSCREEN_H

#include "widgets/screen.h"

namespace stren
{
///
/// class TestBattleFieldScreen
///
class TestBattleFieldScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    TestBattleFieldScreen();
    ///
    /// Destructor
    ///
    ~TestBattleFieldScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
};

} // stren

#endif // STREN_TEST_BATTLE_FIELDSCREEN_H