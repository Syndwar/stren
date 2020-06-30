#ifndef STREN_MAIN_SCREEN_H 
#define STREN_MAIN_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
///
/// class MainScreen
///
class MainScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    MainScreen();
    ///
    /// Destructor
    ///
    virtual ~MainScreen();
private:
    ///
    /// @todo
    ///
    void onTestBtnClicked();
    ///
    /// @todo
    ///
    void onNewGameBtnClicked();
    ///
    /// @todo
    ///
    void onLoadGameBtnClick();
    ///
    /// @todo
    ///
    void onOptionsBtnClick();
    ///
    /// @todo
    ///
    void onMapEditorBtnClick();
    ///
    /// @todo
    ///
    void onExitBtnClick();
};
} // stren
#endif // STREN_MAIN_SCREEN_H
