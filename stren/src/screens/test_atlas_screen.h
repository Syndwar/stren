#ifndef STREN_TEST_BATTLEFIELD_SCREEN_H
#define STREN_TEST_BATTLEFIELD_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
class TestAtlasScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    TestAtlasScreen();
    ///
    /// Destructor
    ///
    virtual ~TestAtlasScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
};
} // stren

#endif // STREN_TEST_BATTLEFIELD_SCREEN_H
