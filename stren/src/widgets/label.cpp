#include "label.h"

#include "SDL.h"

#include "point.h"
#include "renderer.h"
#include "glyph.h"
#include "lua_stack.h"
#include "lua_value.h"

namespace stren
{
Label::Label(const std::string & id)
    : Widget(id)
    , textAlignment_(Alignment::CenterMiddle)
{
}

Label::~Label()
{
}

void Label::setColour(const Colour & colour)
{
    label_.setColour(colour);
    addUpdateState(UpdateState::Update);
}

void Label::setFont(const std::string & fontId)
{
    label_.setFont(fontId);
    addUpdateState(UpdateState::Update);
}

void Label::setText(const std::string & text)
{
    label_.setText(text);
    addUpdateState(UpdateState::Update);
}

const std::string & Label::getText() const
{
    return label_.getText();
}

void Label::setTextAlignment(const int alignment)
{
    textAlignment_ = alignment;
    addUpdateState(UpdateState::Update);
}

void Label::setTextAlignment(const std::string & alignment)
{
    setTextAlignment(Alignment::stringToAlignment(alignment));
}

void Label::doPostMove(const int dx, const int dy)
{
    label_.align(getRect(), textAlignment_);
}

void Label::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        label_.update(getRect(), textAlignment_);
        removeUpdateState(UpdateState::Update);
    }

    label_.render();
}

namespace lua_label
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Label * lbl = new Label(id);
    stack.clear();
    stack.push((void *)lbl);
    return stack.getSize();
}

int setText(lua_State * L)
{
    lua::Stack stack(2);
    Label * lbl = (Label *)stack.get(1).getUserData();
    if (lbl)
    {
        const std::string text = stack.get(2).getString();
        lbl->setText(text);
    }

    stack.clear();
    return 0;
}

int setFont(lua_State * L)
{
    lua::Stack stack(2);
    Label * lbl = (Label *)stack.get(1).getUserData();
    if (lbl)
    {
        const std::string font = stack.get(2).getString();
        lbl->setFont(font);
    }
    stack.clear();
    return 0;
}

int setColour(lua_State * L)
{
    lua::Stack stack(2);
    Label * lbl = (Label *)stack.get(1).getUserData();
    if (lbl)
    {
        const std::string colorStr = stack.get(2).getString();
        lbl->setColour(colorStr);
    }
    stack.clear();
    return 0;
}

int setTextAlignment(lua_State * L)
{
    lua::Stack stack(2);
    Label * lbl = (Label *)stack.get(1).getUserData();
    if (lbl)
    {
        const std::string textAlign = stack.get(2).getString();
        lbl->setTextAlignment(textAlign);
    }
    stack.clear();
    return 0;
}
}

void Label::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_label::create },
        { "setText", lua_label::setText },
        { "setFont", lua_label::setFont },
        { "setColour", lua_label::setColour },
        { "setTextAlignment", lua_label::setTextAlignment },
        { NULL, NULL }
    };
    stack.loadLibs("Label", functions);
}

} // stren