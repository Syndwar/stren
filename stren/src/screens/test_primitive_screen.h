#ifndef STREN_TEST_PRIMITIVE_SCREEN
#define STREN_TEST_PRIMITIVE_SCREEN

#include "widgets/screen.h"

namespace stren
{
///
/// class TestPrimitiveScreen
///
class TestPrimitiveScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    TestPrimitiveScreen();
    ///
    /// Destructor
    ///
    virtual ~TestPrimitiveScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
};
} // stren
#endif // STREN_TEST_PRIMITIVE_SCREEN
