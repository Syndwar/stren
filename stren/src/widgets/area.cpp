#include "area.h"

#include "action.h"

namespace stren
{
Area::Area(const std::string & id)
    : Widget(id)
    , actionEvent_(EventType::None)
    , mouseState_(MouseState::Outside)
{
}

Area::~Area()
{
}

void Area::processEvent(const Event & event, bool & isEventCaptured)
{
    const bool hasMouse = !isEventCaptured && getRect().hasCommon(event.pos);
    if (event.type == actionEvent_)
    {
        if (hasMouse)
        {
            if (MouseState::Outside == mouseState_)
            {
                callAction(true);
                mouseState_ = MouseState::Over;
            }
            isEventCaptured = true;
        }
        else
        {
            if (MouseState::Over == mouseState_)
            {
                callAction(false);
                mouseState_ = MouseState::Outside;
            }
        }
    }
}

void Area::setAction(EventType eventType, IAction * action)
{
    action_.reset(action);
    actionEvent_ = eventType;
}

void Area::callAction(const bool isEnabled)
{
    if (action_)
    {
        if (isEnabled)
        {
            action_->exec();
        }
        else
        {
            action_->cancel();
        }
    }
}

} // stren