#include "point.h"

namespace stren
{
Point Point::kEmpty = Point();

Point::Point(const int x, const int y)
    : m_x(x)
    , m_y(y)
{
}

Point Point::operator+(const Point & point) const
{
    return Point(m_x + point.m_x, m_y + point.m_y);
}

Point Point::operator-(const Point & point) const
{
    return Point(m_x - point.m_x, m_y - point.m_y);
}

Point & Point::operator*(const int multiplier)
{
    m_x *= multiplier;
    m_y *= multiplier;
    return *this;
}
} // stren