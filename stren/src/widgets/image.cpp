#include "image.h"

#include "SDL.h"

#include "engine_handler.h"
#include "event.h"
#include "point.h"
#include "renderer.h"
#include "sprite.h"
#include "lua_wrapper.h"

namespace stren
{
Image::Image(const std::string & id)
    : Widget(id)
    , angle_(0)
    , flip_(Sprite::Flip::None)
{
}

Image::~Image()
{
}

void Image::setFlip(const bool flipv, const bool fliph)
{
    int flip(Sprite::Flip::None);
    if (flipv)
    {
        flip |= Sprite::Flip::Vertical;
    }
    if (fliph)
    {
        flip |= Sprite::Flip::Horizontal;
    }
    setFlip(flip);
}

void Image::setSprite(const std::string & spriteId)
{
    spriteId_ = spriteId;
    addUpdateState(UpdateState::Update);
}

void Image::loadSprite()
{
    if (!spriteId_.empty())
    {
        if (Sprite * sprite = EngineHandler::getSprite(spriteId_))
        {
            sprite_ = *sprite;
        }
    }
}

void Image::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        loadSprite();
        removeUpdateState(UpdateState::Update);
    }
    sprite_.render(getRect(), angle_, flip_, center_);
}

void Image::setCenter(const int x, const int y)
{
    center_.moveTo(x, y);
}

void Image::processEvent(const Event & event, bool & isEventCaptured)
{
    if (!isEventCaptured)
    {
            switch (event.type)
            {
            case EventType::MouseUp:
            case EventType::MouseDown:
            case EventType::MouseClicked:
            case EventType::MouseMove:
            {
                if (getRect().hasCommon(event.pos))
                {
                    isEventCaptured = true;
                }
            }
            break;
        }
    }
}

} // stren