#include "fader.h"

#include "texture.h"
#include "renderer.h"
#include "point.h"
#include "engine_handler.h"
#include "lua_stack.h"
#include "lua_value.h"

namespace stren
{

Fader::Fader(const std::string & id /* = String::kEmpty */)
    : Widget(id)
    , currentAlpha_(0)
    , targetAlpha_(0)
    , fadeSpeed_(255)
    , updateInterval_(100)
{
}

Fader::~Fader()
{
}

void Fader::setSprite(const std::string & id)
{
    spriteId_ = id;
    addUpdateState(UpdateState::Update);
}

void Fader::fadeIn()
{
    targetAlpha_ = 255;
    startTimer();
}

void Fader::fadeOut()
{
    targetAlpha_ = 0;
    startTimer();
}

void Fader::fadeTo(const int targetValue)
{
    targetAlpha_ = targetValue;
    startTimer();
}

void Fader::setFadeSpeed(const int speed)
{
    if (speed > 0)
    {
        fadeSpeed_ = speed;
        updateInterval_ = 1000 / speed;
    }
}

void Fader::fadeInstantTo(const int targetValue)
{
    targetAlpha_ = targetValue;
    currentAlpha_ = targetValue;
}

void Fader::startTimer()
{
    timer_.restart(updateInterval_);
}

void Fader::doUpdate(const size_t dt)
{
    timer_.update(dt);

    if (currentAlpha_ != targetAlpha_)
    {
        if (timer_.isElapsed())
        {
            // check if timer elapsed earlier than update was called
            // and compensate it
            int increment = 1;
            if (dt > updateInterval_)
            {
                increment = dt / updateInterval_;
            }

            if (currentAlpha_ < targetAlpha_)
            {
                currentAlpha_ += increment;
                if (currentAlpha_ > targetAlpha_)
                {
                    currentAlpha_ = targetAlpha_;
                }
                timer_.restart(updateInterval_);
            }
            else if (currentAlpha_ > targetAlpha_)
            {
                currentAlpha_ -= increment;
                if (currentAlpha_ < targetAlpha_)
                {
                    currentAlpha_ = targetAlpha_;
                }
                timer_.restart(updateInterval_);
            }
        }
    }
}

void Fader::loadSprite()
{
    if (!spriteId_.empty())
    {
        if (Sprite * sprite = EngineHandler::getSprite(spriteId_))
        {
            sprite_ = *sprite;
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
    Renderer::setAlpha(currentAlpha_);
    sprite_.render(getRect(), 0, Sprite::Flip::None, Point::getEmpty());
    Renderer::setAlpha(alpha);
}

namespace lua_fader
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Fader * fader = new Fader(id);
    stack.clear();
    stack.push((void *)fader);
    return stack.getSize();
}

int setSprite(lua_State * L)
{
    lua::Stack stack(2);
    Fader * fader = (Fader *)stack.get(1).getUserData();
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
    Fader * fader = (Fader *)stack.get(1).getUserData();
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
    Fader * fader = (Fader *)stack.get(1).getUserData();
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
    Fader * fader = (Fader *)stack.get(1).getUserData();
    if (fader)
    {
        fader->fadeIn();
    }
    return 0;
}

int fadeOut(lua_State * L)
{
    lua::Stack stack(1);
    Fader * fader = (Fader *)stack.get(1).getUserData();
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