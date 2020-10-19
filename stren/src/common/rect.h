#ifndef STREN_RECT_H
#define STREN_RECT_H

namespace stren
{
class Point;
///
/// class Rect, represents geometrical rectangle
///
class Rect
{
private:
    static Rect kEmpty; ///< empty rectangle instance

    int m_x;             ///< left corner coordinate
    int m_y;             ///< up corner coordinate
    int m_w;             ///< rectangle width
    int m_h;             ///< rectangle height
public:
    ///
    /// Returns static empty rect
    ///
    static const Rect & getEmpty() { return Rect::kEmpty; }
    ///
    /// Constructor
    ///
    Rect(const int x = 0, const int y = 0, const int w = 0, const int h = 0);
    ///
    /// returns left corner coordinate
    ///
    inline int getX() const { return m_x; }
    ///
    /// returns upper corner coordinate
    ///
    inline int getY() const { return m_y; }
    ///
    /// returns rectangle width
    ///
    inline int getWidth() const { return m_w; }
    ///
    /// returns rectangle height
    ///
    inline int getHeight() const { return m_h; }
    ///
    /// returns right corner coordinate
    ///
    inline int getRight() const { return m_x + m_w; }
    ///
    /// returns bottom corner coordinate
    ///
    inline int getBottom() const { return m_y + m_h; }
    ///
    /// change left corner coordinate
    ///
    inline void setLeft(const int x) { m_x = x; }
    ///
    /// change up corner coordinate
    ///
    inline void setTop(const int y) { m_y = y; }
    ///
    /// change rectangle width
    ///
    inline void setWidth(const int w) { m_w = w; }
    ///
    /// change rectangle height
    ///
    inline void setHeight(const int h) { m_h = h; }
    ///
    /// returns if rectangle has no width or height
    ///
    inline bool isEmpty() const { return m_w <= 0 || m_h <= 0; }
    ///
    /// change rectangle position
    ///
    inline void moveTo(const int x, const int y) { m_x = x, m_y = y; }
    ///
    /// change rectangle size
    ///
    inline void setSize(const int w, const int h) { m_w = w, m_h = h; }
    ///
    /// change rectangle position using offset dx, dy
    ///
    inline void moveBy(const int dx, const int dy) { m_x += dx, m_y += dy; }
    ///
    /// change rectangle position and size
    ///
    inline void set(const int x, const int y, const int w, const int h) { m_x = x, m_y = y, m_w = w, m_h = h; }
    ///
    /// change rectangle position setting it's new center x coordinate
    ///
    inline void setCenterX(const int centerx) { m_x = centerx - m_w / 2; }
    ///
    /// change rectangle position setting it's new center y coordinate
    ///
    inline void setCenterY(const int centery) { m_y = centery - m_h / 2; }
    ///
    /// change rectangle position setting it's new center
    ///
    inline void setCenter(const int centerx, const int centery) { m_x = centerx - m_w / 2, m_y = centery - m_h / 2; }
    ///
    /// returns rectangle center x position
    ///
    inline int getCenterX() const { return m_x + m_w / 2; }
    ///
    /// returns rectangle center y position
    ///
    inline int getCenterY() const { return m_y + m_h / 2; }
    ///
    /// check if (x, y) point is inside the rectangle
    ///
    bool hasCommon(const int x, const int y) const;
    ///
    /// check if Rect(x, y, w, h) has common parts with the rectangle
    ///
    bool hasCommon(const int x, const int y, const int w, const int h) const;
    ///
    /// check if point is inside the rectangle
    ///
    bool hasCommon(const Point & point) const;
    ///
    /// check if Rect has common parts with the rectangle
    ///
    bool hasCommon(const Rect & rect) const;
    ///
    /// aligns given rect on itself using selected method of alignment
    ///
    void align(Rect & rect, const int alignment) const;
    ///
    /// compare if equal
    ///
    bool operator==(const Rect & rect) const { return m_x == rect.m_x && m_y == rect.m_y && m_w == rect.m_w && m_h == rect.m_h; }
    ///
    /// compare if not equal
    ///
    bool operator!=(const Rect & rect) const { return m_x != rect.m_x || m_y != rect.m_y || m_w != rect.m_w || m_h != rect.m_h; }
};

} // stren

#endif // STREN_RECT_H
