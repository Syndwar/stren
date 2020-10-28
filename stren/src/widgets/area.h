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
    std::unique_ptr<IAction> m_action;             ///< @todo
    EventType                m_actionEvent;        ///< @todo

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
    /// sets an action to this widget, takes ownership of the action
    ///
    void setAction(EventType eventType, IAction * action);
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
    ///
    /// @todo
    ///
    static void bind();
private:
    ///
    /// @todo
    ///
    void callAction(const bool isEnabled);
};
}

#endif // STREN_AREA_H