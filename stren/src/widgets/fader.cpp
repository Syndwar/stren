#include "fader.h"

#include "texture.h"
#include "renderer.h"
#include "point.h"
#include "engine_handler.h"

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
} // stren