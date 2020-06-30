#ifndef STREN_SCREEN_SELECTOR_H
#define STREN_SCREEN_SELECTOR_H

#include "string_ext.h"
#include "screen_ids.h"

namespace stren
{
class Screen;
///
/// class ScreenSelector
///
class ScreenSelector
{
private:
    Screen * m_currentScreen; ///< current screen
    Screen * m_nextScreen;    ///< next screen
public:
    ///
    /// Constructor
    ///
    ScreenSelector();
    ///
    /// switch current screen to the specific screen
    ///
    void switchToScreen(const ScreenId & id);
    ///
    /// update screens
    ///
    void update();
    ///
    /// returns current screen
    ///
    Screen * getCurrentScreen() { return m_currentScreen; }
    ///
    /// frees current and next screens resources
    ///
    void release();
};

} // stren

#endif // STREN_SCREEN_SELECTOR_H
