#ifndef STREN_CAMERA_H
#define STREN_CAMERA_H

#include "common/rect.h"
#include "common/point.h"

namespace stren
{
class Widget;
///
/// class Camera
///
class Camera
{
private:
    Rect  m_clippingRect;    ///< old clipping rect
    Rect  m_rect;            ///< @todo
    Point m_target;          ///< @todo
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
    const Rect & getRect() const { return m_rect; }
    ///
    /// @todo
    ///
    void setRect(const Rect & rect) { m_rect = rect; }
    ///
    /// @todo
    ///
    inline void setTarget(const int x, const int y) { m_target.set(x, y); }
    ///
    /// @todo
    ///
    inline const Point & getTarget() const { return m_target; }
    ///
    /// @todo
    ///
    inline const Point& getOffset() const { return m_target; }
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