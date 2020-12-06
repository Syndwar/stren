#include "fader.h"

#include "common/point.h"
#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "render/texture.h"
#include "render/renderer.h"
#include "lua/lua_wrapper.h"

namespace stren
{

Fader::Fader(const std::string & id /* = String::kEmpty */)
    : Widget(id)
    , m_currentAlpha(0)
    , m_targetAlpha(0)
    , m_fadeSpeed(255)
    , m_updateInterval(100)
{
}

Fader::~Fader()
{
}

void Fader::setSprite(const std::string & id)
{
    m_spriteId = id;
    addUpdateState(UpdateState::Update);
}

void Fader::fadeIn()
{
    m_targetAlpha = 255;
    startTimer();
}

void Fader::fadeOut()
{
    m_targetAlpha = 0;
    startTimer();
}

void Fader::fadeTo(const int targetValue)
{
    m_targetAlpha = targetValue;
    startTimer();
}

void Fader::setFadeSpeed(const int speed)
{
    if (speed > 0)
    {
        m_fadeSpeed = speed;
        m_updateInterval = 1000 / speed;
    }
}

void Fader::fadeInstantTo(const int targetValue)
{
    m_targetAlpha = targetValue;
    m_currentAlpha = targetValue;
}

void Fader::startTimer()
{
    m_timer.restart(m_updateInterval);
}

void Fader::doUpdate(const size_t dt)
{
    m_timer.update(dt);

    if (m_currentAlpha != m_targetAlpha)
    {
        if (m_timer.isElapsed())
        {
            // check if timer elapsed earlier than update was called
            // and compensate it
            int increment = 1;
            if (dt > m_updateInterval)
            {
                increment = dt / m_updateInterval;
            }

            if (m_currentAlpha < m_targetAlpha)
            {
                m_currentAlpha += increment;
                if (m_currentAlpha > m_targetAlpha)
                {
                    m_currentAlpha = m_targetAlpha;
                }
                m_timer.restart(m_updateInterval);
            }
            else if (m_currentAlpha > m_targetAlpha)
            {
                m_currentAlpha -= increment;
                if (m_currentAlpha < m_targetAlpha)
                {
                    m_currentAlpha = m_targetAlpha;
                }
                m_timer.restart(m_updateInterval);
            }
        }
    }
}

void Fader::loadSprite()
{
    if (!m_spriteId.empty())
    {
        if (Sprite * sprite = EngineHandler::getSprite(m_spriteId))
        {
            m_sprite = *sprite;
        }
    }
}

void Fader::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        loadSprite();
        removeUpdateState(UpdateState::Update);
    }
    const int alpha = Renderer::getAlpha();
    Renderer::setAlpha(m_currentAlpha);
    m_sprite.render(getRect(), 0, Sprite::Flip::None, Point::getEmpty());
    Renderer::setAlpha(alpha);
}

namespace lua_fader
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new Fader(id));
    stack.push(handler);
    return 1;
}

int setSprite(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Fader * fader = EngineHandler::getMemoryObj<Fader *>(tbl);
    if (fader)
    {
        const std::string spr = stack.get(2).getString();
        fader->setSprite(spr);
    }
    stack.clear();
    return 0;
}

int setFadeSpeed(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Fader * fader = EngineHandler::getMemoryObj<Fader *>(tbl);
    if (fader)
    {
        const int speed = stack.get(2).getInt();
        fader->setFadeSpeed(speed);
    }
    stack.clear();
    return 0;
}

int getFadeSpeed(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Fader * fader = EngineHandler::getMemoryObj<Fader *>(tbl);
    int speed(0);
    if (fader)
    {
        speed  = fader->getFadeSpeed();
    }
    stack.clear();
    stack.push(speed);
    return stack.getSize();
}

int fadeIn(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Fader * fader = EngineHandler::getMemoryObj<Fader *>(tbl);
    if (fader)
    {
        fader->fadeIn();
    }
    return 0;
}

int fadeOut(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Fader * fader = EngineHandler::getMemoryObj<Fader *>(tbl);
    if (fader)
    {
        fader->fadeOut();
    }
    return 0;
}
} // lua_fader

void Fader::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_fader::create },
        { "setSprite", lua_fader::setSprite },
        { "setFadeSpeed", lua_fader::setFadeSpeed },
        { "getFadeSpeed", lua_fader::getFadeSpeed },
        { "fadeIn", lua_fader::fadeIn },
        { "fadeOut", lua_fader::fadeOut },
        { NULL, NULL }
    };
    stack.loadLibs("Fader", functions);
}
} // stren