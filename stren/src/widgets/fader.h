#ifndef STREN_FADER_H
#define STREN_FADER_H

#include "widget.h"

#include "sprite.h"
#include "timer.h"

namespace stren
{
///
/// class Fader
///
class Fader : public Widget
{
    std::string spriteId_;              ///< @todo
    int         currentAlpha_;          ///< @todo
    int         targetAlpha_;           ///< @todo
    int         fadeSpeed_;             ///< how many points of alpha will change in one second
    size_t      updateInterval_;        ///< update fader interval in milliseconds
    Timer       timer_;                 ///< update timer
    Sprite      sprite_;                ///< @todo
public:
    ///
    /// Constructor
    ///
    Fader(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    ~Fader();
    ///
    /// @todo
    ///
    inline bool isFading() const { return targetAlpha_ != currentAlpha_; }
    ///
    /// @todo
    ///
    inline int getFadeSpeed() const { return fadeSpeed_; }
    ///
    /// set fading speed in points of alpha change in one second
    ///
    void setFadeSpeed(const int speed);
    ///
    /// @todo
    ///
    void setSprite(const std::string & id);
    ///
    /// fade to desired fade value instantly
    ///
    void fadeInstantTo(const int targetValue);
    ///
    /// fade to desired fade value
    ///
    void fadeTo(const int targetValue);
    ///
    /// fully fade away from screen
    ///
    void fadeOut();
    ///
    /// fully hide the screen
    ///
    void fadeIn();
    ///
    /// @todo
    ///
    static void bind();
private:
    ///
    /// @todo
    ///
    void startTimer();
    ///
    /// @todo
    ///
    void loadSprite();
    ///
    /// update fader
    ///
    virtual void doUpdate(const size_t dt) override;
    ///
    /// render widget
    ///
    virtual void doRender() override;
};
}
#endif // STREN_FADER_H
