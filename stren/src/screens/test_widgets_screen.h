#ifndef STREN_TEST_WIDGETS_SCREEN_H
#define STREN_TEST_WIDGETS_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
///
/// class TestWidgetsScreen
///
class TestWidgetsScreen : public Screen
{
private:
    Widget * dialog_; ///< @todo
public:
    ///
    /// Constructor
    ///
    TestWidgetsScreen();
    ///
    /// Destructor
    ///
    ~TestWidgetsScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void onLockBtnClick();
    ///
    /// @todo
    ///
    void onWindBtnClicked();
    ///
    /// @todo
    ///
    void onMoveCntBtnClick();
    ///
    /// @todo
    ///
    void onButtonInContainerClick();
};
} // stren
#endif // STREN_TEST_WIDGETS_SCREEN_H
