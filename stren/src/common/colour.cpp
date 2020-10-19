#include "colour.h"

namespace stren
{
Colour::Colour()
    : m_r(0)
    , m_g(0)
    , m_b(0)
    , m_a(0)
{
}

Colour::Colour(const size_t r, const size_t g, const size_t b, const size_t a)
    : m_r(r)
    , m_g(g)
    , m_b(b)
    , m_a(a)
{
}

Colour::Colour(const Type colour)
{
    set(colour);
}

Colour::Colour(const std::string & colour)
{
    set(colour);
}

void Colour::set(const Colour::Type colourType)
{
    switch (colourType)
    {
        case Black:  set(0, 0, 0, 0);        break;
        case White:  set(255, 255, 255, 0);  break;
        case Red:    set(255, 0, 0, 0);      break;
        case Green:  set(0, 255, 0, 0);      break;
        case Blue:   set(0, 0, 255, 0);      break;
        case Yellow: set(240, 255, 0, 0);    break;
        case Grey:   set(69, 69, 69, 0);     break;
    }
}

void Colour::set(const std::string & colour)
{
    set(stringToType(colour));
}

Colour::Type Colour::stringToType(const std::string & colour)
{
    if ("white" == colour)          { return White; }
    else if ("black" == colour)     { return Black; }
    else if ("red" == colour)       { return Red; }
    else if ("green" == colour)     { return Green; }
    else if ("blue" == colour)      { return Blue; }
    else if ("yellow" == colour)    { return Yellow; }
    else if ("grey" == colour)      { return Grey; }
    return Black;
}

} // stren