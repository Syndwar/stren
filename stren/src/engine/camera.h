#ifndef STREN_CAMERA_H
#define STREN_CAMERA_H

#include "rect.h"
#include "point.h"

namespace stren
{
class Widget;
///
/// class Camera
///
class Camera
{
private:
    Rect  clippingRect_;    ///< old clipping rect
    Rect  rect_;            ///< @todo
    Point target_;          ///< @todo
public:
    ///
    /// Constructor
    ///
    Camera();
    ///
    /// Constructor
    ///
    Camera(const Rect & rect);
    ///
    /// Constructor
    ///
    Camera(const int x, const int y, const int w, const int h);
    ///
    /// Destructor
    ///
    virtual ~Camera();
    ///
    /// @todo
    ///
    void render(Widget * widget);
    ///
    /// @todo
    ///
    void moveTo(const int x, const int y);
    ///
    /// @todo
    ///
    void resize(const int w, const int h);
    ///
    /// @todo
    ///
    const Rect & getRect() const { return rect_; }
    ///
    /// @todo
    ///
    void setRect(const Rect & rect) { rect_ = rect; }
    ///
    /// @todo
    ///
    inline void setTarget(const int x, const int y) { target_.set(x, y); }
    ///
    /// @todo
    ///
    inline const Point & getTarget() const { return target_; }
    ///
    /// @todo
    ///
    inline const Point& getOffset() const { return target_; }
    ///
    /// @todo
    ///
    void place();
    ///
    /// @todo
    ///
    void restore();
};
} // stren

#endif // STREN_CAMERA_H