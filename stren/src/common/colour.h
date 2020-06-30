#ifndef STREN_COLOUR_H
#define STREN_COLOUR_H

#include "string_ext.h"

namespace stren
{
///
/// class Colour represents RGB colour data with A as alpha transparency
///
class Colour
{
public:
    enum Type
    {
        Black,
        White,
        Red,
        Green,
        Blue,
        Yellow,
        Grey,
    };         ///< colour types
private:
    size_t m_r; ///< red
    size_t m_g; ///< green
    size_t m_b; ///< blue
    size_t m_a; ///< alpha
public:
    ///
    /// Default Constructor
    ///
    Colour();
    ///
    /// create colour based on rgba values
    ///
    Colour(const size_t r, const size_t g, const size_t b, const size_t a);
    ///
    /// create colour based on colour type value
    ///
    Colour(const Type colour);
    ///
    /// create colour based on string value
    ///
    Colour(const std::string & colour);
    ///
    /// change colour using rgba values
    ///
    inline void set(const size_t r, const size_t g, const size_t b, const size_t a) { m_r = r, m_g = g, m_b = b, m_a = a; }
    ///
    /// get red value 
    ///
    inline size_t r() const { return m_r; }
    ///
    /// get green value 
    ///
    inline size_t g() const { return m_g; }
    ///
    /// get blue value
    ///
    inline size_t b() const { return m_b; }
    ///
    /// get alpha value 
    ///
    inline size_t a() const { return m_a; }
    ///
    /// set red value
    ///
    inline void setR(const size_t r) { m_r = r; }
    ///
    /// set green value
    ///
    inline void setG(const size_t g) { m_g = g; }
    ///
    /// set blue value
    ///
    inline void setB(const size_t b) { m_b = b; }
    ///
    /// set alpha value
    ///
    inline void setA(const size_t a) { m_a = a; }
    ///
    /// change colour using colour type value
    ///
    void set(const Type colourType);
    ///
    /// change colour using string value
    ///
    void set(const std::string & colour);
    ///
    /// get color type value from string
    ///
    static Type stringToType(const std::string & colour);
};

} // stren

#endif
