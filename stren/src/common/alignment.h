#ifndef STREN_ALIGNMENT_H
#define STREN_ALIGNMENT_H

#include "string_ext.h"

namespace stren
{
///
/// Class helper to align widgets and texts around each other or the screen.
///
class Alignment
{
public:
    enum
    {
        Left = 0x0001,
        Center = 0x0002,
        Right = 0x0004,
        
        Top = 0x0008,
        Middle = 0x0010,
        Bottom = 0x0020,
        
        LeftTop    = Left | Top,
        LeftMiddle = Left | Middle,
        LeftBottom = Left | Bottom,

        CenterTop    = Center | Top,
        CenterMiddle = Center | Middle,
        CenterBottom = Center | Bottom,

        RightTop    = Right | Top,
        RightMiddle = Right | Middle,
        RightBottom = Right | Bottom,
    };                                              ///< Possible alignment methods

    ///
    /// Convert alignment string to enum
    ///
    static int stringToAlignment(const std::string & alignment)
    {
        if ("LEFT|TOP" == alignment)
        {
            return Alignment::LeftTop;
        }
        else if ("LEFT|MIDDLE" == alignment)
        {
            return Alignment::LeftMiddle;
        }
        else if ("LEFT|BOTTOM" == alignment)
        {
            return Alignment::LeftBottom;
        }
        else if ("CENTER|TOP" == alignment)
        {
            return Alignment::CenterTop;
        }
        else if ("CENTER|MIDDLE" == alignment)
        {
            return Alignment::CenterMiddle;
        }
        else if ("CENTER|BOTTOM" == alignment)
        {
            return Alignment::CenterBottom;
        }
        else if ("RIGHT|TOP" == alignment)
        {
            return Alignment::RightTop;
        }
        else if ("RIGHT|MIDDLE" == alignment)
        {
            return Alignment::RightMiddle;
        }
        else if ("RIGHT|BOTTOM" == alignment)
        {
            return Alignment::RightBottom;
        }

        return LeftTop;
    }
};

} // stren

#endif // STREN_ALIGNMENT_H
