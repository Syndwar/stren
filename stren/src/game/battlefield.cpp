#include "battlefield.h"

#include "engine/event.h"
#include "lua/lua_wrapper.h"

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

namespace lua_battlefield
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Battlefield * cnt = new Battlefield(id);
    stack.clear();
    stack.push((void *)cnt);
    return stack.getSize();
}
}

void Battlefield::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_battlefield::create },
        { NULL, NULL }
    };
    stack.loadLibs("Battlefield", functions);
}

} // stren