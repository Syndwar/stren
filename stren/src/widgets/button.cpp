#include "button.h"

#include "SDL.h"

#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "engine/event.h"
#include "engine/listener.h"
#include "render/renderer.h"
#include "render/sprite.h"
#include "repo/fonts_repository.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Button::Button(const std::string & id)
    : Widget(id)
    , m_textAlignment(Alignment::Center | Alignment::Middle)
    , m_viewState(ViewState::Up)
    , m_flip(Sprite::Flip::None)
    , m_angle(0)
{
    m_sprites.resize(kSpritesCount);
    m_spriteIds.resize(kSpritesCount);
}

Button::~Button()
{
}

void Button::setColour(const Colour & colour)
{
    m_label.setColour(colour);
    addUpdateState(UpdateState::Update);
}

void Button::setText(const std::string & text)
{
    m_label.setText(text);
    addUpdateState(UpdateState::Update);
}

void Button::setFont(const std::string & fontId)
{
    m_label.setFont(fontId);
    addUpdateState(UpdateState::Update);
}

void Button::setTextAlignment(const int alignment)
{
    m_textAlignment = alignment;
    addUpdateState(UpdateState::Update);
}

void Button::setTextAlignment(const std::string & alignment)
{
    setTextAlignment(Alignment::stringToAlignment(alignment));
}

void Button::doPostMove(const int dx, const int dy)
{
    m_label.align(getRect(), m_textAlignment);
}

void Button::loadSprites()
{
    for (size_t i = 0; i < kSpritesCount; ++i)
    {
        const std::string & spriteId = m_spriteIds[i];
        if (!spriteId.empty())
        {
            if (Sprite * sprite = EngineHandler::getSprite(spriteId))
            {
                m_sprites[i] = *sprite;
            }
        }
    }
}

size_t Button::getTextureIndex() const
{
    if (ViewState::Over == m_viewState) return 1;
    if (ViewState::Pressed == m_viewState) return 2;
    return 0;
}

void Button::setFlip(const bool fliph, const bool flipv)
{
    int flip(Sprite::Flip::None);
    if (fliph)
    {
        flip |= Sprite::Flip::Horizontal;
    }
    if (flipv)
    {
        flip |= Sprite::Flip::Vertical;
    }
    setFlip(flip);
}

void Button::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        loadSprites();
        m_label.update(getRect(), m_textAlignment);
        removeUpdateState(UpdateState::Update);
    }

    const size_t index = getTextureIndex();
    Sprite & currentSprite = m_sprites[index];
    currentSprite.render(getRect(), m_angle, m_flip, m_center);

    m_label.render();
}

void Button::setSprites(const std::string & upSpr, const std::string & downSpr, const std::string & overSpr, const std::string & disSpr)
{
    m_spriteIds[0] = upSpr;
    m_spriteIds[1] = downSpr;
    m_spriteIds[2] = overSpr;
    addUpdateState(UpdateState::Update);
}

void Button::processEvent(const Event & event, bool & isEventCaptured)
{
    switch (event.type)
    {
    case EventType::MouseDown:
    case EventType::MouseUp:
    case EventType::MouseMove:
    {
        const bool hasMouse = !isEventCaptured && isOpened() && getRect().hasCommon(event.pos);
        if (hasMouse)
        {
            if (EventType::MouseMove == event.type)
            {
                if (ViewState::Over != m_viewState && ViewState::Pressed != m_viewState)
                {
                    m_viewState = ViewState::Over;
                    isEventCaptured = true;
                }
            }
            else if (EventType::MouseDown == event.type)
            {
                m_viewState = ViewState::Pressed;
                isEventCaptured = true;
            }
            else if (EventType::MouseUp == event.type)
            {
                if (ViewState::Pressed == m_viewState)
                {
                    m_viewState = ViewState::Over;

                    callBack(event, this);
                    isEventCaptured = true;
                }
            }
        }
        else if (ViewState::Up != m_viewState)
        {
            m_viewState = ViewState::Up;
        }
    }
    break;
    }
}

namespace lua_button
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new Button(id));
    stack.push(handler);
    return 1;
}

int setText(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Button * btn = EngineHandler::getMemoryObj<Button *>(tbl);
    if (btn)
    {
        const std::string text = stack.get(2).getString();
        btn->setText(text);
    }

    stack.clear();
    return 0;
}

int setFont(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Button * btn = EngineHandler::getMemoryObj<Button *>(tbl);
    if (btn)
    {
        const std::string font = stack.get(2).getString();
        btn->setFont(font);
    }
    stack.clear();
    return 0;
}

int setTextColour(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Button * btn = EngineHandler::getMemoryObj<Button *>(tbl);
    if (btn)
    {
        const std::string colorStr = stack.get(2).getString();
        btn->setColour(colorStr);
    }
    stack.clear();
    return 0;
}

int setTextAlignment(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Button * btn = EngineHandler::getMemoryObj<Button *>(tbl);
    if (btn)
    {
        const std::string textAlign = stack.get(2).getString();
        btn->setTextAlignment(textAlign);
    }
    stack.clear();
    return 0;
}

int setSprites(lua_State * L)
{
    lua::Stack stack(4);
    lua::Table tbl(stack.get(1));
    Button * btn = EngineHandler::getMemoryObj<Button *>(tbl);
    if (btn)
    {
        const std::string upSpr = stack.get(2).getString();
        const std::string downSpr = stack.get(3).getString();
        const std::string overSpr = stack.get(4).getString();
        const std::string disabledSpr = stack.get(5).getString();
        btn->setSprites(upSpr, downSpr, overSpr, disabledSpr);
    }
    stack.clear();
    return 0;
}
} // lua_button

void Button::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_button::create },
        { "setText", lua_button::setText },
        { "setFont", lua_button::setFont },
        { "setColour", lua_button::setTextColour },
        { "setTextAlignment", lua_button::setTextAlignment },
        { "setSprites", lua_button::setSprites },
        { NULL, NULL }
    };
    stack.loadLibs("Button", functions);
}

} // stren