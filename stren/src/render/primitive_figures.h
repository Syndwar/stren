#ifndef STREN_PRIMITIVE_FIGURES
#define STREN_PRIMITIVE_FIGURES

#include <vector>

#include "common/point.h"
#include "common/rect.h"

struct SDL_Point;

namespace stren
{
class Colour;
///
/// class PrimitiveFigure represents some primitive geometry for rendering
///
class PrimitiveFigure
{
public:
    ///
    /// Destructor
    ///
    virtual ~PrimitiveFigure() {}
    ///
    /// render primitive figure
    ///
    virtual void render(const Colour & colour) = 0;
    ///
    /// move primitive to the point
    ///
    virtual void moveTo(const int x, const int y) = 0;
    ///
    /// move primitive using offset dx, dy
    ///
    virtual void moveBy(const int dx, const int dy) = 0;
    ///
    /// resize primitive using new size w, h
    ///
    virtual void resize(const int w, const int h) = 0;
    ///
    /// reset primitive geometry
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill) = 0;
};
///
/// class PrimitiveRect
///
class PrimitiveRect : public PrimitiveFigure
{
private:
    Rect m_rect; ///< @todo
    bool m_fill; ///< @todo

public:
    ///
    /// Constructor
    ///
    PrimitiveRect(const Rect & rect, const bool fill);
    ///
    /// Destructor
    ///
    virtual ~PrimitiveRect();
    ///
    /// render primitive figure
    ///
    virtual void render(const Colour & colour) override;
    ///
    /// move primitive to the point
    ///
    virtual void moveTo(const int x, const int y) override;
    ///
    /// move primitive using offset dx, dy
    ///
    virtual void moveBy(const int dx, const int dy) override;
    ///
    /// returns primitive rectangle
    ///
    const Rect & getRect() const { return m_rect; }
    ///
    /// change primitive rect
    ///
    virtual void resize(const int w, const int h) override;
    ///
    /// reset primitive geometry
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill) override {}
};
///
/// class PrimitiveRects
///
class PrimitiveRects : public PrimitiveFigure
{
private:
    bool                m_fill;  ///< @todo
    std::vector<Rect>   m_rects; ///< @todo
public:
    ///
    /// Constructor
    ///
    PrimitiveRects(const std::vector<Rect> & rects, const bool fill);
    ///
    /// Destructor
    ///
    virtual ~PrimitiveRects();
    ///
    /// render primitive figure
    ///
    virtual void render(const Colour & colour) override;
    ///
    /// move primitive to the point
    ///
    virtual void moveTo(const int x, const int y) override;
    ///
    /// move primitive using offset dx, dy
    ///
    virtual void moveBy(const int dx, const int dy) override;
    ///
    /// change primitive rect
    ///
    virtual void resize(const int w, const int h) override {}
    ///
    /// change rects and fill mode
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill);
};
///
/// class PrimitiveLines
///
class PrimitiveLines : public PrimitiveFigure
{
private:
    std::vector<Point>  points_;        ///< @todo
    SDL_Point *         sdlPoints_;     ///< @todo
public:
    ///
    /// Constructor
    ///
    PrimitiveLines(const std::vector<Point> & points);
    ///
    /// Destructor
    ///
    virtual ~PrimitiveLines();
    ///
    /// render primitive figure
    ///
    virtual void render(const Colour & colour) override;
    ///
    /// move primitive to the point
    ///
    virtual void moveTo(const int x, const int y) override;
    ///
    /// move primitive using offset dx, dy
    ///
    virtual void moveBy(const int dx, const int dy) override;
    ///
    /// change primitive rect
    ///
    virtual void resize(const int w, const int h) override {}
    ///
    /// reset primitive geometry
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill) override {}
};
///
/// class PrimitivePoint
///
class PrimitivePoint : public PrimitiveFigure
{
private:
    Point point_;   ///< @todo
public:
    ///
    /// Constructor
    ///
    PrimitivePoint(const Point & point);
    ///
    /// Destructor
    ///
    virtual ~PrimitivePoint();
    ///
    /// render primitive figure
    ///
    virtual void render(const Colour & colour) override;
    ///
    /// move primitive to the point
    ///
    virtual void moveTo(const int x, const int y) override;
    ///
    /// move primitive using offset dx, dy
    ///
    virtual void moveBy(const int dx, const int dy) override;
    ///
    /// change primitive rect
    ///
    virtual void resize(const int w, const int h) override {}
    ///
    /// reset primitive geometry
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill) override {}
};
///
/// class PrimitivePoints
///
class PrimitivePoints : public PrimitiveFigure
{
private:
    std::vector<Point> points_; ///< @todo
public:
    ///
    /// Constructor
    ///
    PrimitivePoints(const std::vector<Point> & points);
    ///
    /// Destructor
    ///
    virtual ~PrimitivePoints();
    ///
    /// render primitive figure
    ///
    virtual void render(const Colour & colour) override;
    ///
    /// move primitive to the point
    ///
    virtual void moveTo(const int x, const int y) override;
    ///
    /// move primitive using offset dx, dy
    ///
    virtual void moveBy(const int dx, const int dy) override;
    ///
    /// change primitive rect
    ///
    virtual void resize(const int w, const int h) override {}
    ///
    /// reset primitive geometry
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill) override {}
};
///
/// class PrimitiveCircle
///
class PrimitiveCircle : public PrimitiveFigure
{
private:
    int x_;         ///< @todo
    int y_;         ///< @todo
    int radius_;    ///< @todo
public:
    ///
    /// Constructor
    ///
    PrimitiveCircle(const int x, const int y, const int radius);
    ///
    /// Destructor
    ///
    virtual ~PrimitiveCircle();
    ///
    /// render primitive figure
    ///
    virtual void render(const Colour & colour) override;
    ///
    /// move primitive to the point
    ///
    virtual void moveTo(const int x, const int y) override;
    ///
    /// move primitive using offset dx, dy
    ///
    virtual void moveBy(const int dx, const int dy) override;
    ///
    /// change primitive rect
    ///
    virtual void resize(const int w, const int h) override {}
    ///
    /// reset primitive geometry
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill) override {}
};
} // stren
#endif // STREN_PRIMITIVE_FIGURES
