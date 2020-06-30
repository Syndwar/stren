#include "rect.h"

#include "alignment.h"
#include "point.h"

namespace stren
{
Rect Rect::kEmpty = Rect();

Rect::Rect(const int x, const int y, const int w, const int h)
    : m_x(x)
    , m_y(y)
    , m_w(w)
    , m_h(h) 
{
}

bool Rect::hasCommon(const int x, const int y) const
{
    return !((x < m_x) || (y < m_y) || (x > getRight()) || (y > getBottom()));
}

bool Rect::hasCommon(const int x, const int y, const int w, const int h) const
{
    return !((x > getRight()) || (y > getBottom()) || (h + y < m_y) || (x + w < m_x));
}

bool Rect::hasCommon(const Point & point) const
{
    return !((point.getX() < m_x) || (point.getY() < m_y) || (point.getX() > getRight()) || (point.getY() > getBottom()));
}

bool Rect::hasCommon(const Rect & rect) const
{
    return !((rect.m_x > getRight()) || (rect.m_y > getBottom()) || (rect.getBottom() < m_y) || (rect.getRight() < m_x));
}

void Rect::align(Rect & rect, const int alignment) const
{
    if (alignment & Alignment::Left)
    {
        rect.setLeft(m_x);
    }
    else if (alignment & Alignment::Center)
    {
        rect.setCenterX(getCenterX());
    }
    else if (alignment & Alignment::Right)
    {
        rect.setLeft(getRight() - rect.getWidth());
    }

    if (alignment & Alignment::Top)
    {
        rect.setTop(m_y);
    }
    else if (alignment & Alignment::Middle)
    {
        rect.setCenterY(getCenterY());
    }
    else if (alignment & Alignment::Bottom)
    {
        rect.setTop(getBottom() - rect.getHeight());
    }
}

} // stren