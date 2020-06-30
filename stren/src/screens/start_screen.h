#ifndef STREN_START_SCREEN_H
#define STREN_START_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
///
/// class StartScreen
///
class StartScreen : public Screen
{
public:
    ///
    /// Constructor
    ///
    StartScreen();
    ///
    /// Destructor
    ///
    virtual ~StartScreen();
private:
    ///
    /// go to next screen
    ///
    void switchToNextScreen();
};
} // stren

#endif // STREN_START_SCREEN_H
