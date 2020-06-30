#ifndef STREN_EVENT_H
#define STREN_EVENT_H

#include <vector>

#include "string_ext.h"
#include "point.h"

namespace stren
{
enum class EventType
{
    None = 0,
    Unknown,
    KeyUp,
    KeyDown,
    MouseUp,
    MouseDown,
    MouseMove,
    MouseWheel,
    MouseClicked,
    WidgetOpened,
    WidgetClosed,
    WidgetDelete,
    WidgetOpening,
    WidgetClosing,
    TimerElapsed,
    SysQuit,
};                                                  ///< possible event types
///
/// class Event
///
class Event
{
public:

    static std::vector<std::string> kEventTypes;    ///< string values for the event types

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
};

} // stren

#endif // STREN_EVENT_H
