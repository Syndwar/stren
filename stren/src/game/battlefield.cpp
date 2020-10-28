#include "battlefield.h"

#include "engine/event.h"

namespace stren
{
Battlefield::Battlefield(const std::string & id)
    : ScrollContainer(id)
{
}

Battlefield::~Battlefield()
{
}

void Battlefield::processEvent(const Event & event, bool & isEventCaptured)
{
    if (!isEventCaptured && isOpened())
    {
        switch (event.type)
        {
            case EventType::KeyDown:
            {
                if ("D" == event.key)
                {
                    scrollTo(ScrollDirection::Right, true);
                    isEventCaptured = true;
                }
                else if ("A" == event.key)
                {
                    scrollTo(ScrollDirection::Left, true);
                    isEventCaptured = true;
                }
                else if ("W" == event.key)
                {
                    scrollTo(ScrollDirection::Up, true);
                    isEventCaptured = true;
                }
                else if ("S" == event.key)
                {
                    scrollTo(ScrollDirection::Down, true);
                    isEventCaptured = true;
                }
            }
            break;

            case EventType::KeyUp:
            {
                if ("D" == event.key)
                {
                    scrollTo(ScrollDirection::Right, false);
                    isEventCaptured = true;
                }
                else if ("A" == event.key)
                {
                    scrollTo(ScrollDirection::Left, false);
                    isEventCaptured = true;
                }
                else if ("W" == event.key)
               {
                    scrollTo(ScrollDirection::Up, false);
                    isEventCaptured = true;
                }
                else if ("S" == event.key)
                {
                    scrollTo(ScrollDirection::Down, false);
                    isEventCaptured = true;
                }
            }
            break;
        }
    }
   
    ScrollContainer::processEvent(event, isEventCaptured);
}

} // stren