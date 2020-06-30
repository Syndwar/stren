#ifndef STREN_BUTTON_H
#define STREN_BUTTON_H

#include <map>

#include "colour.h"
#include "delegate.h"
#include "event.h"
#include "point.h"
#include "widget.h"
#include "clabel.h"

namespace stren
{
class Sprite;
///
/// class Button
///
class Button : public Widget
{
private:

    enum class ViewState
    {
        Up = 0,
        Over,
        Pressed,
    };                                                              ///< @todo

    static const size_t kSpritesCount = 3;                          ///< @todo

    int                                 textAlignment_;             ///< @todo
    int                                 flip_;                      ///< @todo
    double                              angle_;                     ///< @todo
    ViewState                           viewState_;                 ///< @todo
    CLabel                              label_;                     ///< @todo
    Point                               center_;                    ///< @todo
    std::vector<Sprite>                 sprites_;                   ///< @todo
    std::vector<std::string>            spriteIds_;                 ///< @todo

public:
    ///
    /// Constructor:
    ///
    Button(const std::string & id = String::kEmpty);
    ///
    /// Destructor:
    ///
    ~Button();
    ///
    /// @todo
    ///
    inline void setAngle(const double angle) { angle_ = angle; }
    ///
    /// @todo
    ///
    inline double angle() const { return angle_; }
    ///
    /// @todo
    ///
    inline void setFlip(const int flip) { flip_ = flip; }
    ///
    /// @todo
    ///
    inline int flip() const { return flip_; }
    ///
    /// @todo
    ///
    void setSprites(const std::string & upSpr, const std::string & downSpr, const std::string & overSpr, const std::string & disSpr = String::kEmpty);
    ///
    /// @todo
    ///
    void setColour(const Colour & colour);
    ///
    /// @todo
    ///
    void setFont(const std::string & fontId);
    ///
    /// @todo
    ///
    void setText(const std::string & text);
    ///
    /// @todo
    ///
    void setTextAlignment(const int alignment);
    ///
    /// @todo
    ///
    void setTextAlignment(const std::string & alignment);
    ///
    /// @todo
    ///
    virtual void doPostMove(const int dx, const int dy) override;
    ///
    /// process incoming system events
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
private:
    ///
    /// @todo
    ///
    virtual void doRender() override;
    ///
    /// @todo
    ///
    void loadSprites();
    ///
    /// @todo
    ///
    size_t getTextureIndex() const;
};
}// stren

#endif // STREN_BUTTON_H
