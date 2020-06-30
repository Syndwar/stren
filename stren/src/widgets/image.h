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
    std::string     spriteId_;      ///< @todo
    Point           center_;        ///< @todo
    double          angle_;         ///< @todo
    int             flip_;          ///< @todo
    Sprite          sprite_;        ///< @todo
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
    inline void setAngle(const double angle) { angle_ = angle; }
    ///
    /// @todo
    ///
    inline void setFlip(const int flip) { flip_ = flip; }
    ///
    /// @todo
    ///
    void setFlip(const bool flipv, const bool fliph);

    /// WRITEME
    void setSprite(const std::string & spriteId);
    ///
    /// @todo
    ///
    void setCenter(const int x, const int y);
    ///
    /// process incoming system events, returns true if the event was processed, otherwise - returns false to let other widget to process it
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