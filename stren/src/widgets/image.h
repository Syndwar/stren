#ifndef STREN_IMAGE_H
#define STREN_IMAGE_H

#include "widgets/widget.h"
#include "common/point.h"
#include "render/sprite.h"

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
    /// @todo
    ///
    static void bind();
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
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