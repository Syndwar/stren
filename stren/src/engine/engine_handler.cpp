#include "engine_handler.h"

#include "engine.h"
#include "point.h"

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

void EngineHandler::consoleLog(const std::string & message)
{
    if (m_engine)
    {
        m_engine->consoleLog(message);
    }
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
} // stren