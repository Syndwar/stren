#ifndef STREN_EVENT_H
#define STREN_EVENT_H

#include <vector>

#include "common/string_ext.h"
#include "common/point.h"

namespace stren
{
enum EventType
{
    None = 0x0000,
    Unknown = 0x0001,
    KeyUp = 0x0002,
    KeyDown = 0x0004,
    MouseUp = 0x0008,
    MouseDown = 0x0010,
    MouseMove = 0x0020,
    MouseWheel = 0x0040,
    MouseClicked = 0x0080,
    WidgetOpened = 0x0100,
    WidgetClosed = 0x0200,
    WidgetDelete = 0x0400,
    WidgetOpening = 0x0800,
    WidgetClosing = 0x1000,
    TimerElapsed = 0x2000,
    SysQuit = 0x4000,
};                                                  ///< possible event types
///
/// class Event
///
class Event
{
public:

    enum class KeyMod
    {
        None = 0,
        Alt,
        Shift,
        Control,
    };                                              ///< possible key mods
    
    enum class MouseButton
    {
        None = 0,
        Left = 1,
        Middle = 2,
        Right = 3,
        X1 = 4,
        X2 = 5,
    };                                              ///< possible mouse button values

    EventType   type;                               ///< event type value
    KeyMod      mod;                                ///< key mod value
    MouseButton mouseButton;                        ///< mouse button value
    Point       pos;                                ///< key mod
    Point       wheel;                              ///< mouse wheel direction
    std::string key;                                ///< key value
public:
    ///
    /// Default Constructor
    ///
    Event();
    ///
    /// Constructor
    ///
    Event(EventType type);
    ///
    /// returns if event is valid
    ///
    inline bool isValid() const { return EventType::None != type; }
    ///
    /// returns if event is unknown
    ///
    inline bool isUnknown() const { return EventType::Unknown == type; }
    ///
    /// clears event, makes it invalid
    ///
    void clear();
    ///
    /// convert string event name to EventType
    ///
    static EventType strToType(const std::string & type);
};

} // stren

#endif // STREN_EVENT_H
