#ifndef STREN_PRIMITIVE_H
#define STREN_PRIMITIVE_H

#include <vector>

#include "common/colour.h"
#include "widgets/widget.h"

namespace stren
{
class Point;
class PrimitiveFigure;
class Rect;
///
/// class Primitive
///
class Primitive : public Widget
{
private:
    Colour              m_colour; ///< primitive colour
    PrimitiveFigure *   m_figure; ///< primitive figure with specific geometry
public:
    ///
    /// Constructor
    ///
    Primitive(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Primitive();
    ///
    /// set primitive draw colour using colour type
    ///
    inline void setColour(const Colour & colour) { m_colour = colour; }
    ///
    /// point
    ///
    void createPoint(const Point & point);
    ///
    /// points
    ///
    void createPoints(const std::vector<Point> & points);
    ///
    /// rect
    ///
    void createRect(const Rect & rect, const bool fill);
    ///
    /// rects
    ///
    void createRects(const std::vector<Rect> & rects, const bool fill);
    ///
    /// lines
    ///
    void createLines(const std::vector<Point> & points);
    ///
    /// circle
    ///
    void createCircle(const int x, const int y, const int radius);
    ///
    /// move widget to a new position
    ///
    virtual void moveTo(const int x, const int y) override;
    ///
    /// move widget to a new position using offset
    ///
    virtual void moveBy(const int dx, const int dy) override;
    ///
    /// move widget and resize if possible
    ///
    virtual void setRect(const int x, const int y, const int w, const int h) override;
    ///
    /// reset primitive geometry
    ///
    virtual void reset(const std::vector<Rect> & rects, const bool fill);
    ///
    /// render primitive figure
    ///
    virtual void doRender() override;
    ///
    /// @todo
    ///
    static void bind();
};
} // stren

#endif // STREN_PRIMITIVE_H
