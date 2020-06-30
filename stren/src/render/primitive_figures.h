#ifndef STREN_PRIMITIVE_FIGURES
#define STREN_PRIMITIVE_FIGURES

#include <vector>

#include "point.h"
#include "rect.h"

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
};
///
/// class PrimitiveRect
///
class PrimitiveRect : public PrimitiveFigure
{
private:
    Rect rect_; ///< @todo
    bool fill_; ///< @todo

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

};
///
/// class PrimitiveRects
///
class PrimitiveRects : public PrimitiveFigure
{
private:
    bool                fill_;  ///< @todo
    std::vector<Rect>   rects_; ///< @todo
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
};
} // stren
#endif // STREN_PRIMITIVE_FIGURES
