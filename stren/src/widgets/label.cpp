#include "label.h"

#include "SDL.h"

#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "common/point.h"
#include "render/renderer.h"
#include "render/glyph.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Label::Label(const std::string & id)
    : Widget(id)
    , m_textAlignment(Alignment::CenterMiddle)
{
}

Label::~Label()
{
}

void Label::setColour(const Colour & colour)
{
    m_label.setColour(colour);
    addUpdateState(UpdateState::Update);
}

void Label::setFont(const std::string & fontId)
{
    m_label.setFont(fontId);
    addUpdateState(UpdateState::Update);
}

void Label::setText(const std::string & text)
{
    m_label.setText(text);
    addUpdateState(UpdateState::Update);
}

const std::string & Label::getText() const
{
    return m_label.getText();
}

void Label::setTextAlignment(const int alignment)
{
    m_textAlignment = alignment;
    addUpdateState(UpdateState::Update);
}

void Label::setTextAlignment(const std::string & alignment)
{
    setTextAlignment(Alignment::stringToAlignment(alignment));
}

void Label::doPostMove(const int dx, const int dy)
{
    m_label.align(getRect(), m_textAlignment);
}

void Label::doPostResize(const int dw, const int dh)
{
    addUpdateState(UpdateState::Align);
}

void Label::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        m_label.update(getRect(), m_textAlignment);
        removeUpdateState(UpdateState::Update);
    }

    if (hasUpdateState(UpdateState::Align))
    {
        m_label.align(getRect(), m_textAlignment);
        removeUpdateState(UpdateState::Align);
    }

    m_label.render();
}

void Label::setWrap(const bool value)
{
    m_label.setWrap(value);
}

namespace lua_label
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new Label(id));
    stack.push(handler);
    return 1;
}

int setText(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Label * lbl = EngineHandler::getMemoryObj<Label *>(tbl);
    if (lbl)
    {
        const std::string text = stack.get(2).getString();
        lbl->setText(text);
    }
    return 0;
}

int setFont(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Label * lbl = EngineHandler::getMemoryObj<Label *>(tbl);
    if (lbl)
    {
        const std::string font = stack.get(2).getString();
        lbl->setFont(font);
    }
    return 0;
}

int setColour(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Label * lbl = EngineHandler::getMemoryObj<Label *>(tbl);
    if (lbl)
    {
        const std::string colorStr = stack.get(2).getString();
        lbl->setColour(colorStr);
    }
    return 0;
}

int setTextAlignment(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Label * lbl = EngineHandler::getMemoryObj<Label *>(tbl);
    if (lbl)
    {
        const std::string textAlign = stack.get(2).getString();
        lbl->setTextAlignment(textAlign);
    }
    return 0;
}

int setWrap(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Label * lbl = EngineHandler::getMemoryObj<Label *>(tbl);
    if (lbl)
    {
        const bool isWrapEnable = stack.get(2).getBool();
        lbl->setWrap(isWrapEnable);
    }
    return 0;
}
} // lua_label

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
        { "setWrap", lua_label::setWrap },
        { NULL, NULL }
    };
    stack.loadLibs("Label", functions);
}

} // stren