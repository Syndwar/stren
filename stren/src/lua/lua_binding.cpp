#include "lua_binding.h"

#include "lua_wrapper.h"

#include "engine_handler.h"
#include "sound_system.h"

#include "action.h"
#include "event.h"
#include "utils.h"

#include "battlefield.h"
#include "listener.h"
#include "logger.h"
#include "transform.h"

#include "widgets/area.h"
#include "widgets/button.h"
#include "widgets/container.h"
#include "widgets/dialog.h"
#include "widgets/fader.h"
#include "widgets/image.h"
#include "widgets/label.h"
#include "widgets/primitive.h"
#include "widgets/progressbar.h"
#include "widgets/screen.h"
#include "widgets/scroll_container.h"
#include "widgets/timer.h"

using namespace stren;

namespace lua
{
namespace engine
{
int playSound(lua_State *L)
{
    lua::Stack stack(1);
    if (SoundSystem * soundSystem = EngineHandler::getSoundSystem())
    {
        const std::string soundId = stack.get(1).getString();
        int loop = 0;
        const int stackSize = stack.getSize();
        if (stackSize > 1)
        {
            loop = stack.get(2).getInt();
        }
        int channel = -1;
        if (stackSize > 2)
        {
            channel = stack.get(3).getInt();
        }

        stack.clear();
        soundSystem->playSound(soundId, loop, channel);
    }
    return stack.getSize();
}

int playMusic(lua_State *L)
{
    lua::Stack stack(1);
    if (SoundSystem * soundSystem = EngineHandler::getSoundSystem())
    {
        lua::Stack stack;
        const std::string trackId = stack.get(1).getString();
        int loop = -1;
        if (stack.getSize() > 1)
        {
            loop = stack.get(2).getInt();
        }
        stack.clear();
        soundSystem->playMusic(trackId, loop);
    }
    return stack.getSize();
}

int stopMusic(lua_State *L)
{
    lua::Stack stack(0);
    if (SoundSystem * soundSystem = EngineHandler::getSoundSystem())
    {
        soundSystem->stopMusic();
    }
    return stack.getSize();
}

int getScreenWidth(lua_State * L)
{
    lua::Stack stack(0);
    stack.push(EngineHandler::getScreenWidth());
    return stack.getSize();
}

int getScreenHeight(lua_State * L)
{
    lua::Stack stack(0);
    stack.push(EngineHandler::getScreenHeight());
    return stack.getSize();
}

int getMousePos(lua_State * L)
{
    lua::Stack stack(0);
    const Point mousePos = EngineHandler::getMousePos();
    stack.push(mousePos.getX());
    stack.push(mousePos.getY());
    return stack.getSize();
}

int shutdown(lua_State *L)
{
    lua::Stack stack(0);
    EngineHandler::shutdown();
    return stack.getSize();
}

int restart(lua_State *L)
{
    lua::Stack stack(0);
    EngineHandler::restart();
    return stack.getSize();
}

int log(lua_State *L)
{
    lua::Stack stack(1);
    const std::string value = stack.get(1).getString();
    stren::Logger("blue") << value;

    return stack.getSize();
}

int consoleLog(lua_State *L)
{
    lua::Stack stack(1);
    const std::string value = stack.get(1).getString();
    EngineHandler::consoleLog(value);

    return stack.getSize();
}
} // engine

void bindWithVM()
{
    lua::Stack stack;
    {
        const luaL_reg functions[] =
        {
            { "playSound", engine::playSound },
            { "playMusic", engine::playMusic },
            { "stopMusic", engine::stopMusic },
            { "getScreenWidth", engine::getScreenWidth },
            { "getScreenHeight", engine::getScreenHeight },
            { "getMousePos", engine::getMousePos },
            { "shutdown", engine::shutdown },
            { "restart", engine::restart },
            { "log", engine::log },
            { "consoleLog", engine::consoleLog },
            { NULL, NULL }
        };
        stack.loadLibs("Engine", functions);
    }
}
} // lua