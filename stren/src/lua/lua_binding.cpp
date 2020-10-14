#include "lua_binding.h"

#include "lua_wrapper.h"

#include "engine_handler.h"
#include "sound_system.h"

#include "logger.h"

#include "widgets/screen.h"
#include "widgets/button.h"

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
    stack.clear();
    return 0;
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
    stack.clear();
    return 0;
}

int stopMusic(lua_State *L)
{
    if (SoundSystem * soundSystem = EngineHandler::getSoundSystem())
    {
        soundSystem->stopMusic();
    }
    return 0;
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
    EngineHandler::shutdown();
    return 0;
}

int restart(lua_State *L)
{
    EngineHandler::restart();
    return 0;
}

int log(lua_State *L)
{
    lua::Stack stack(1);
    const std::string value = stack.get(1).getString();
    stren::Logger("blue") << value;

    return 0;
}

int consoleLog(lua_State *L)
{
    lua::Stack stack(1);
    const std::string value = stack.get(1).getString();
    EngineHandler::consoleLog(value);
    return 0;
}

int deserialize(lua_State * L)
{
    EngineHandler::deserialize();
    return 0;
}

int serialize(lua_State * L)
{
    EngineHandler::serialize();
    return 0;
}

int createGame(lua_State * L)
{
    lua::Stack stack(0);
    void * game = EngineHandler::createGame();
    stack.push(game);
    return stack.getSize();
}
} // engine

namespace game
{
int changeScreen(lua_State * L)
{
    lua::Stack stack(2);
    void * game = stack.get(1).getUserData();
    void * screen = stack.get(2).getUserData();
    EngineHandler::switchScreen(game, screen);
    return 0;
}
} // game

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
            { "deserialize", engine::deserialize },
            { "serialize", engine::serialize },
            { "createGame", engine::createGame },
            { NULL, NULL }
        };
        stack.loadLibs("Engine", functions);
    }
    {
        const luaL_reg functions[] =
        {
            { "changeScreen", game::changeScreen},
            { NULL, NULL }
        };
        stack.loadLibs("Game", functions);
    }
    Widget::bind();
    Button::bind();
    Container::bind();
    Screen::bind();
}
} // lua