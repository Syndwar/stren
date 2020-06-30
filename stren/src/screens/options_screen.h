#ifndef STREN_OPTIONS_SCREEN_H
#define STREN_OPTIONS_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
class Button;
///
/// class OptionsScreen
///
class OptionsScreen : public Screen
{
private:
    bool                      isVSync_;             ///< @todo
    bool                      isBorderless_;        ///< @todo
    bool                      isFullscreen_;        ///< @todo
    int                       resIndex_;            ///< @todo
    Button *                  vSyncBtn_;            ///< @todo
    Button *                  fullscreenBtn_;       ///< @todo
    Button *                  borderlessBtn_;       ///< @todo
    std::vector<Button *>     resBtns_;             ///< @todo
public:
    ///
    /// Constructor
    ///
    OptionsScreen();
    ///
    /// Destructor
    ///
    virtual ~OptionsScreen();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void onVsyncBtnClick();
    ///
    /// @todo
    ///
    void onBorderlessBtnClick();
    ///
    /// @todo
    ///
    void onFullscreenBtnClick();
    ///
    /// @todo
    ///
    void onApplyBtnClick();
    ///
    /// @todo
    ///
    void onResolutionBtnClick(Widget * sender);
};
} // stren

#endif // STREN_OPTIONS_SCREEN_H
