#include "progressbar.h"

#include "engine_handler.h"

namespace stren
{

ProgressBar::ProgressBar(const std::string & id)
    : Widget(id)
    , type_(Type::Horizontal)
    , currentValue_(0)
    , maxValue_(100)
    , fillSpeed_(1)
    , updateInterval_(1000)
    , targetValue_(0)
    , camera_(getRect())
{
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::setVertical(const bool value)
{
    setType(value ? Type::Vertical : Type::Horizontal);
}

void ProgressBar::setCurrentValue(const int value)
{
    if (value <= maxValue_)
    {
        currentValue_ = value;
    }
}

void ProgressBar::setFillSpeed(const int speed)
{
    fillSpeed_ = speed;
    updateInterval_ = 1000 / speed;
}

void ProgressBar::windTo(const int value)
{
    if (value <= maxValue_)
    {
        targetValue_ = value;
        timer_.restart(updateInterval_);
    }
}

bool ProgressBar::isWinding() const
{
    return targetValue_ != currentValue_;
}

void ProgressBar::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        loadSprite();
        removeUpdateState(UpdateState::Update);
    }
    const Rect & rect = getRect();

    int left(rect.getX());
    int top(rect.getY());
    int width(rect.getWidth());
    int height(rect.getHeight());

    if (Type::Horizontal == type_)
    {
        width = width * currentValue_ / maxValue_;
    }
    else if (Type::Vertical == type_)
    {
        const int oldHeight(height);
        height = height * currentValue_ / maxValue_;
        top = top + oldHeight - height;
    }

    camera_.moveTo(left, top);
    camera_.resize(width, height);
    camera_.place();
    sprite_.render(rect, Sprite::Flip::None, 0, center_);
    camera_.restore();
}

void ProgressBar::doUpdate(const size_t dt)
{
    timer_.update(dt);

    if (timer_.isElapsed())
    {
        if (currentValue_ < targetValue_)
        {
            ++currentValue_;
            timer_.restart(updateInterval_);
        }
        else if (currentValue_ > targetValue_)
        {
            --currentValue_;
            timer_.restart(updateInterval_);
        }
        else
        {
            timer_.stop();
        }
    }
}

void ProgressBar::loadSprite()
{
    if (!spriteId_.empty())
    {
        if (Sprite * sprite = EngineHandler::getSprite(spriteId_))
        {
            sprite_ = *sprite;
        }
    }
}

} // stren