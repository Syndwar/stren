#ifndef STREN_IMAGE_H
#define STREN_IMAGE_H

#include "widget.h"
#include "point.h"
#include "sprite.h"

namespace stren
{
///
/// class Image
///
class Image : public Widget
{
private:
    std::string     m_spriteId;      ///< @todo
    Point           m_center;        ///< @todo
    double          m_angle;         ///< @todo
    int             m_flip;          ///< @todo
    Sprite          m_sprite;        ///< @todo
public:
    ///
    /// Constructor
    ///
    Image(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Image();
    ///
    /// @todo
    ///
    inline void setAngle(const double angle) { m_angle = angle; }
    ///
    /// @todo
    ///
    inline void setFlip(const int flip) { m_flip = flip; }
    ///
    /// @todo
    ///
    void setFlip(const bool flipv, const bool fliph);
    ///
    /// @todo
    ///
    void setSprite(const std::string & spriteId);
    ///
    /// @todo
    ///
    void setCenter(const int x, const int y);
    ///
    /// process incoming system events, returns true if the event was processed, otherwise - returns false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
    ///
    /// @todo
    ///
    static void bind();
private:
    ///
    /// @todo
    ///
    void loadSprite();
    ///
    /// @todo
    ///
    virtual void doRender() override;
};
}

#endif // STREN_IMAGE_H