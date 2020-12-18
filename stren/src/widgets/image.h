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
    bool            m_ignoreMouse;   ///< @todo
    int             m_flip;          ///< @todo
    double          m_angle;         ///< @todo
    std::string     m_spriteId;      ///< @todo
    Point           m_center;        ///< @todo
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
    /// sets image rotation angle
    ///
    inline void setAngle(const double angle) { m_angle = angle; }
    ///
    /// returns image rotation angle
    ///
    inline double getAngle() const { return m_angle; }
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
    const Point & getCenter() const { return m_center; }
    ///
    /// @todo
    ///
    void ignoreMouse(const bool value) { m_ignoreMouse = value; }
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
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