#include "button.h"

#include "SDL.h"

#include "engine_handler.h"
#include "renderer.h"
#include "event.h"
#include "fonts_repository.h"
#include "glyph.h"
#include "lua_wrapper.h"
#include "listener.h"
#include "sprite.h"

namespace stren
{
Button::Button(const std::string & id)
    : Widget(id)
    , textAlignment_(Alignment::Center | Alignment::Middle)
    , viewState_(ViewState::Up)
    , flip_(Sprite::Flip::None)
    , angle_(0)
{
    sprites_.resize(kSpritesCount);
    spriteIds_.resize(kSpritesCount);
}

Button::~Button()
{
}

void Button::setColour(const Colour & colour)
{
    label_.setColour(colour);
    addUpdateState(UpdateState::Update);
}

void Button::setText(const std::string & text)
{
    label_.setText(text);
    addUpdateState(UpdateState::Update);
}

void Button::setFont(const std::string & fontId)
{
    label_.setFont(fontId);
    addUpdateState(UpdateState::Update);
}

void Button::setTextAlignment(const int alignment)
{
    textAlignment_ = alignment;
    addUpdateState(UpdateState::Update);
}

void Button::setTextAlignment(const std::string & alignment)
{
    setTextAlignment(Alignment::stringToAlignment(alignment));
}

void Button::doPostMove(const int dx, const int dy)
{
    label_.align(getRect(), textAlignment_);
}

void Button::loadSprites()
{
    for (size_t i = 0; i < kSpritesCount; ++i)
    {
        const std::string & spriteId = spriteIds_[i];
        if (!spriteId.empty())
        {
            if (Sprite * sprite = EngineHandler::getSprite(spriteId))
            {
                sprites_[i] = *sprite;
            }
        }
    }
}

size_t Button::getTextureIndex() const
{
    if (ViewState::Over == viewState_) return 1;
    if (ViewState::Pressed == viewState_) return 2;
    return 0;
}

void Button::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        loadSprites();
        label_.update(getRect(), textAlignment_);
        removeUpdateState(UpdateState::Update);
    }

    const size_t index = getTextureIndex();
    Sprite & currentSprite = sprites_[index];
    currentSprite.render(getRect(), angle_, flip_, center_);

    label_.render();
}

void Button::setSprites(const std::string & upSpr, const std::string & downSpr, const std::string & overSpr, const std::string & disSpr)
{
    spriteIds_[0] = upSpr;
    spriteIds_[1] = downSpr;
    spriteIds_[2] = overSpr;
    addUpdateState(UpdateState::Update);
}

void Button::processEvent(const Event & event, bool & isEventCaptured)
{
    const bool hasMouse = !isEventCaptured && getRect().hasCommon(event.pos);
    if (hasMouse && isOpened())
    {
        switch (event.type)
        {
            case EventType::MouseMove:
            {
                if (ViewState::Over != viewState_ && ViewState::Pressed != viewState_)
                {
                    viewState_ = ViewState::Over;
                }
            }
            break;
            case EventType::MouseDown:
            {
                viewState_ = ViewState::Pressed;
            }
            break;
            case EventType::MouseUp:
            {
                if (ViewState::Pressed == viewState_)
                {
                    viewState_ = ViewState::Over;

                    callBack(EventType::MouseClicked, this);
                }
            }
            break;
        }
        isEventCaptured = true;
    }
    else if (ViewState::Up != viewState_)
    {
        viewState_ = ViewState::Up;
    }
}

namespace lua_button
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Button * btn = new Button(id);
    stack.clear();
    stack.push((void *)btn);
    return stack.getSize();
}

int setText(lua_State * L)
{
    lua::Stack stack(2);
    Button * btn = (Button *)stack.get(1).getUserData();
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
    Button * btn = (Button *)stack.get(1).getUserData();
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
    Button * btn = (Button *)stack.get(1).getUserData();
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
    Button * btn = (Button *)stack.get(1).getUserData();
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
    Button * btn = (Button *)stack.get(1).getUserData();
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

int addCallback(lua_State * L)
{
    lua::Stack stack(3);
    Button * btn = (Button *)stack.get(1).getUserData();
    if (btn)
    {
        const std::string eventTypeStr = stack.get(2).getString();
        const std::string callback = stack.get(3).getString();
        btn->addCallback(eventTypeStr, callback);
    }
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
        { "addCallback", lua_button::addCallback },
        { NULL, NULL }
    };
    stack.loadLibs("Button", functions);
}

} // stren