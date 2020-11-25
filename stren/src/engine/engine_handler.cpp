#include "engine_handler.h"

#include "common/point.h"
#include "engine/engine.h"
#include "engine/logger.h"
#include "engine/event.h"

#include "lua/lua_wrapper.h"

namespace stren
{

Engine * EngineHandler::m_engine = nullptr;

bool EngineHandler::create()
{
    if (!m_engine)
    {
        m_engine = new Engine();
    }
    return nullptr != m_engine;
}

void EngineHandler::destroy()
{
    if (m_engine)
    {
        m_engine->clean();
        delete m_engine;
        m_engine = nullptr;
    }
}

bool EngineHandler::init()
{
    if (m_engine)
    {
        if (!m_engine->isRunning())
        {
            return m_engine->init();
        }
    }
    return false;
}

void EngineHandler::createGame()
{
    if (m_engine)
    {
        m_engine->createGame();
    }
}

void EngineHandler::stop()
{
    if (m_engine)
    {
        m_engine->stop();
    }
}

bool EngineHandler::isRestarting()
{
    return m_engine && m_engine->isRestarting();
}

bool EngineHandler::isRunning()
{
    return m_engine && m_engine->isRunning();
}

void EngineHandler::process()
{
    if (m_engine)
    {
        m_engine->process();
    }
}

int EngineHandler::getScreenWidth()
{
    return m_engine ? m_engine->getScreenWidth() :  0;
}

int EngineHandler::getScreenHeight()
{
    return m_engine ? m_engine->getScreenHeight() : 0;
}

const std::string & EngineHandler::getTextByAlias(const std::string & alias)
{
    return m_engine ? m_engine->getTextByAlias(alias) : String::kEmpty;
}

size_t EngineHandler::getFPS()
{
    return m_engine ? m_engine->getFPS() : 0;
}

SoundSystem * EngineHandler::getSoundSystem()
{
    return m_engine ? m_engine->getSoundsSystem() : nullptr;
}

Screen * EngineHandler::getCurrentScreen()
{
    return m_engine ? m_engine->getCurrentScreen() : nullptr;
}

void EngineHandler::shutdown()
{
    if (m_engine)
    {
        m_engine->stop();
    }
}

void EngineHandler::restart()
{
    if (m_engine)
    {
        m_engine->restart();
    }
}

const Point & EngineHandler::getMousePos()
{
    return m_engine ? m_engine->getMousePos() : Point::getEmpty();
}

Sprite * EngineHandler::getSprite(const std::string & spriteId)
{
    return m_engine ? m_engine->getSprite(spriteId) : nullptr;
}

ITexture * EngineHandler::getTexture(const std::string & textureId)
{
    return m_engine ? m_engine->getTexture(textureId) : nullptr;
}

void EngineHandler::switchScreen(void * screen)
{
    if (m_engine)
    {
        m_engine->switchScreen(screen);
    }
}

void EngineHandler::deserialize()
{
    if (m_engine)
    {
        m_engine->deserialize();
    }
}

void EngineHandler::serialize()
{
    if (m_engine)
    {
        m_engine->serialize();
    }
}

namespace lua_engine
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
    return 2;
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
    EngineHandler::createGame();
    return 0;
}

int getTextureSize(lua_State * L)
{
    lua::Stack stack(1);
    const std::string textureId = stack.get(1).getString();
    stack.clear();
    if (!textureId.empty())
    {
        if (ITexture * texture = EngineHandler::getTexture(textureId))
        {
            stack.push(texture->getWidth());
            stack.push(texture->getHeight());
        }
    }
    return stack.getSize();
}

int getFPS(lua_State * L)
{
    lua::Stack stack;
    const size_t fps = EngineHandler::getFPS();
    stack.push(fps);
    return 1;
}
} // lua_engine

namespace lua_game
{
int changeScreen(lua_State * L)
{
    lua::Stack stack(1);
    void * screen = stack.get(1).getUserData();
    if (screen)
    {
        EngineHandler::switchScreen(screen);
    }
    return 0;
}
} // lua_game

void EngineHandler::bind()
{
    lua::Stack stack;
    const luaL_reg engine_functions[] =
    {
        { "playSound", lua_engine::playSound },
        { "playMusic", lua_engine::playMusic },
        { "stopMusic", lua_engine::stopMusic },
        { "getScreenWidth", lua_engine::getScreenWidth },
        { "getScreenHeight", lua_engine::getScreenHeight },
        { "getMousePos", lua_engine::getMousePos },
        { "shutdown", lua_engine::shutdown },
        { "restart", lua_engine::restart },
        { "log", lua_engine::log },
        { "deserialize", lua_engine::deserialize },
        { "serialize", lua_engine::serialize },
        { "createGame", lua_engine::createGame },
        { "getTextureSize", lua_engine::getTextureSize },
        { "getFPS", lua_engine::getFPS },
        { NULL, NULL }
    };
    stack.loadLibs("Engine", engine_functions);

    const luaL_reg game_functions[] =
    {
        { "changeScreen", lua_game::changeScreen },
        { NULL, NULL }
    };
    stack.loadLibs("Game", game_functions);
}
} // stren