#ifndef STREN_FADER_H
#define STREN_FADER_H

#include "widget.h"

#include "render/sprite.h"
#include "widgets/timer.h"

namespace stren
{
///
/// class Fader
///
class Fader : public Widget
{
    std::string m_spriteId;              ///< @todo
    int         m_currentAlpha;          ///< @todo
    int         m_targetAlpha;           ///< @todo
    int         m_fadeSpeed;             ///< how many points of alpha will change in one second
    size_t      m_updateInterval;        ///< update fader interval in milliseconds
    Timer       m_timer;                 ///< update timer
    Sprite      m_sprite;                ///< @todo
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
    inline bool isFading() const { return m_targetAlpha != m_currentAlpha; }
    ///
    /// @todo
    ///
    inline int getFadeSpeed() const { return m_fadeSpeed; }
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
