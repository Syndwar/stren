#ifndef STREN_POINT_H
#define STREN_POINT_H

namespace stren
{
///
/// class Point represents geometrical point
///
class Point
{
private:
    static Point kEmpty; ///< empty point instance

    int m_x;              ///< point x coordinate
    int m_y;              ///< point y coordinate

public:
    ///
    /// Returns static empty point
    ///
    static const Point & getEmpty() { return Point::kEmpty; }
    ///
    /// Constructor
    ///
    Point(const int x = 0, const int y = 0);
    ///
    /// returns x coordinate
    ///
    inline int getX() const { return m_x; }
    ///
    /// changes x, y coordinates
    ///
    inline void set(const int x, const int y) { m_x = x, m_y = y; }
    ///
    /// changes x coordinate
    ///
    inline void setX(const int x) { m_x = x; }
    ///
    /// changes y coordinate
    ///
    inline void setY(const int y) { m_y = y; }
    ///
    /// returns y coordinate
    ///
    inline int getY() const { return m_y; }
    ///
    /// changes x, y coordinates
    ///
    inline void moveTo(const int x, const int y) { m_x = x, m_y = y; }
    ///
    /// changes x, y coordinates using offset dx, dy
    ///
    inline void moveBy(const int dx, const int dy) { m_x += dx, m_y += dy; }
    ///
    /// plus
    ///
    Point operator+(const Point & point) const;
    ///
    /// minus
    ///
    Point operator-(const Point & point) const;
    ///
    /// multiplier
    ///
    Point & operator*(const int multiplier);
    ///
    /// compare if equal
    ///
    inline bool operator==(const Point & point) const { return m_x == point.m_x && m_y == point.m_y; }
    ///
    /// compare if not equal
    ///
    inline bool operator!=(const Point & point) const { return m_x != point.m_x || m_y != point.m_y; }
};

} // stren

#endif // STREN_POINT_H