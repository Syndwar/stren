#ifndef STREN_AREA_H
#define STREN_AREA_H

#include "engine/event.h"
#include "widgets/widget.h"

namespace stren
{
class IAction;
class Connector;
class Area;
///
/// class Area
///
class Area : public Widget
{
private:
    enum class MouseState
    {
        Outside,
        Over,
    };

    MouseState               m_mouseState;         ///< @todo

public:
    ///
    /// Constructor
    ///
    Area(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Area();
    ///
    /// @todo
    ///
    static void bind();
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
};
}

#endif // STREN_AREA_H