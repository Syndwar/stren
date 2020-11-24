#include "image.h"

#include "SDL.h"

#include "common/point.h"
#include "engine/engine_handler.h"
#include "engine/event.h"
#include "render/renderer.h"
#include "render/sprite.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Image::Image(const std::string & id)
    : Widget(id)
    , m_angle(0)
    , m_flip(Sprite::Flip::None)
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
    m_spriteId = spriteId;
    addUpdateState(UpdateState::Update);
}

void Image::loadSprite()
{
    if (!m_spriteId.empty())
    {
        if (Sprite * sprite = EngineHandler::getSprite(m_spriteId))
        {
            m_sprite = *sprite;
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
    m_sprite.render(getRect(), m_angle, m_flip, m_center);
}

void Image::setCenter(const int x, const int y)
{
    m_center.moveTo(x, y);
}

void Image::processEvent(const Event & event, bool & isEventCaptured)
{
    if (!isEventCaptured)
    {
        switch (event.type)
        {
        case EventType::MouseUp:
        case EventType::MouseDown:
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

namespace lua_image
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Image * btn = new Image(id);
    stack.clear();
    stack.push((void *)btn);
    return stack.getSize();
}

int setSprite(lua_State * L)
{
    lua::Stack stack(2);
    Image * img = (Image *)stack.get(1).getUserData();
    if (img)
    {
        const std::string spr = stack.get(2).getString();
        img->setSprite(spr);
    }
    stack.clear();
    return 0;
}

int setAngle(lua_State * L)
{
    lua::Stack stack(2);
    Image * img = (Image *)stack.get(1).getUserData();
    if (img)
    {
        const int angle = stack.get(2).getInt();
        img->setAngle(angle);
    }
    stack.clear();
    return 0;
}

int setFlip(lua_State * L)
{
    lua::Stack stack(3);
    Image * img = (Image *)stack.get(1).getUserData();
    if (img)
    {
        const bool flipv = stack.get(2).getBool();
        const bool fliph = stack.get(3).getBool();
        img->setFlip(flipv, fliph);
    }
    stack.clear();
    return 0;
}
} // lua_image

void Image::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_image::create },
        { "setSprite", lua_image::setSprite },
        { "setAngle", lua_image::setAngle },
        { "setFlip", lua_image::setFlip },
        { NULL, NULL }
    };
    stack.loadLibs("Image", functions);
}

} // stren