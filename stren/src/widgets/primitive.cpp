#include "primitive.h"

#include "primitive_figures.h"

namespace stren
{
Primitive::Primitive(const std::string & id)
    : Widget(id)
    , m_figure(nullptr)
{
}

Primitive::~Primitive()
{
    if (m_figure)
    {
        delete m_figure;
        m_figure = nullptr;
    }
}

void Primitive::createPoint(const Point & point)
{
    m_figure = new PrimitivePoint(point);
}

void Primitive::createPoints(const std::vector<Point> & points)
{
    m_figure = new PrimitivePoints(points);
}

void Primitive::createRect(const Rect & rect, const bool fill)
{
    m_figure = new PrimitiveRect(rect, fill);
}

void Primitive::createRects(const std::vector<Rect> & rects, const bool fill)
{
    m_figure = new PrimitiveRects(rects, fill);
}

void Primitive::createLines(const std::vector<Point> & points)
{
    m_figure = new PrimitiveLines(points);
}

void Primitive::createCircle(const int x, const int y, const int radius)
{
    m_figure = new PrimitiveCircle(x, y, radius);
}

void Primitive::doRender()
{
    if (m_figure)
    {
        m_figure->render(m_colour);
    }
}

void Primitive::moveTo(const int x, const int y)
{
    if (m_figure)
    {
        m_figure->moveTo(x, y);
    }
}

void Primitive::moveBy(const int dx, const int dy)
{
    if (m_figure)
    {
        m_figure->moveBy(dx, dy);
    }
}
} // stren
