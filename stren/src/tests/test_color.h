#ifndef STREN_TEST_COLOUR_H
#define STREN_TEST_COLOUR_H

#include "common/colour.h"

namespace test
{
///
/// class StrenColour
///
class StrenColour
{
public:
    ///
    /// Constructor
    ///
    StrenColour()
    {
        Colour colour;
        Colour colour2(Colour::Black);
        stren::assertMessage(isEqual(colour, colour2), "Error");
        colour.set("red");
        colour2.set(Colour::Red);
        stren::assertMessage(isEqual(colour, colour2), "Error");
        stren::assertMessage(colour2.r() == 255, "Error");
    }
    ///
    /// check if the colours are equal
    ///
    bool isEqual(const Colour & colour1, const Colour & colour2)
    {
        return colour1.r() == colour2.r() &&
            colour1.g() == colour2.g() &&
            colour1.b() == colour2.b() &&
            colour1.a() == colour2.a();
    }
};
} // test

#endif // STREN_TEST_COLOUR_H
