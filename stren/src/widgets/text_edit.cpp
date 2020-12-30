#include "widgets/text_edit.h"

#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "engine/event.h"
#include "lua/lua_wrapper.h"

namespace stren
{
///
/// class TextEdit
///
TextEdit::TextEdit(const std::string & id)
    : Widget(id)
    , m_textAlignment(Alignment::CenterMiddle)
    , m_isInputMode(false)
{
}

TextEdit::~TextEdit()
{
}

void TextEdit::enableInputMode()
{
    if (!m_isInputMode)
    {
        m_isInputMode = true;
        std::string new_text = getText();
        setText(new_text.append("|"));
    }
}

void TextEdit::cancelInputMode()
{
    if (m_isInputMode)
    {
        std::string new_text = getText();
        new_text.pop_back();
        setText(new_text);
        m_isInputMode = false;
    }
}

bool TextEdit::isInputMode() const
{
    return m_isInputMode;
}

void TextEdit::setColour(const Colour & colour)
{
    m_label.setColour(colour);
    addUpdateState(UpdateState::Update);
}

void TextEdit::setFont(const std::string & fontId)
{
    m_label.setFont(fontId);
    addUpdateState(UpdateState::Update);
}

void TextEdit::setText(const std::string & text)
{
    m_label.setText(text);
    addUpdateState(UpdateState::Update);
}

const std::string & TextEdit::getText() const
{
    return m_label.getText();
}

void TextEdit::setTextAlignment(const int alignment)
{
    m_textAlignment = alignment;
    addUpdateState(UpdateState::Update);
}

void TextEdit::setTextAlignment(const std::string & alignment)
{
    setTextAlignment(Alignment::stringToAlignment(alignment));
}

void TextEdit::doPostMove(const int dx, const int dy)
{
    m_label.align(getRect(), m_textAlignment);
}

void TextEdit::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        m_label.update(getRect(), m_textAlignment);
        removeUpdateState(UpdateState::Update);
    }

    m_label.render();
}

void TextEdit::processEvent(const Event & event, bool & isEventCaptured)
{
    if (isEventCaptured)
    {
        if (isInputMode())
        {
            cancelInputMode();
        }
    }
    else
    {
        switch (event.type)
        {
        case EventType::KeyUp:
        {
            if (isInputMode())
            {
                if ("Return" == event.key || "Escape" == event.key)
                {
                    cancelInputMode();
                    isEventCaptured = true;
                }
                else if ("Backspace" == event.key)
                {
                    std::string new_text = getText();
                    if (new_text.size() > 1)
                    {
                        new_text.pop_back();
                        new_text.pop_back();
                        new_text.append("|");
                        setText(new_text);
                    }
                    isEventCaptured = true;
                }
                else if ("Space" == event.key)
                {
                    std::string new_text = getText();
                    new_text.pop_back();
                    new_text.append(" |");
                    setText(new_text);
                    isEventCaptured = true;
                }
                else if (1 == event.key.size())
                {
                    std::string new_text = getText();
                    new_text.pop_back();
                    if (Event::KeyMod::Shift == event.mod)
                    {
                        if ("-" == event.key)
                        {
                            new_text.append("_");
                        }
                        else
                        {
                            const char input[] = { (char)toupper(event.key[0]), "\0" };
                            new_text.append(input);
                        }
                    }
                    else
                    {
                        const char input[] = { (char)tolower(event.key[0]), "\0" };
                        new_text.append(input);
                    }
                    new_text.append("|");
                    setText(new_text);
                    isEventCaptured = true;
                }
            }
        }
        break;
        case EventType::MouseDown:
        {
            if (getRect().hasCommon(event.pos))
            {
                enableInputMode();
                isEventCaptured = true;
            }
        }
        break;
        }
    }
}

namespace lua_text_edit
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new TextEdit(id));
    stack.push(handler);
    return 1;
}

int setText(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    TextEdit * edit = EngineHandler::getMemoryObj<TextEdit *>(tbl);
    if (edit)
    {
        const std::string text = stack.get(2).getString();
        edit->setText(text);
    }
    return 0;
}

int getText(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    TextEdit * edit = EngineHandler::getMemoryObj<TextEdit *>(tbl);
    if (edit)
    {
        const std::string & text = edit->getText();
        stack.push(text);
    }
    else
    {
        stack.push();
    }

    return 1;
}

int setFont(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    TextEdit * edit = EngineHandler::getMemoryObj<TextEdit *>(tbl);
    if (edit)
    {
        const std::string font = stack.get(2).getString();
        edit->setFont(font);
    }
    return 0;
}

int setColour(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    TextEdit * edit = EngineHandler::getMemoryObj<TextEdit *>(tbl);
    if (edit)
    {
        const std::string colorStr = stack.get(2).getString();
        edit->setColour(colorStr);
    }
    return 0;
}

int setTextAlignment(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    TextEdit * edit = EngineHandler::getMemoryObj<TextEdit *>(tbl);
    if (edit)
    {
        const std::string textAlign = stack.get(2).getString();
        edit->setTextAlignment(textAlign);
    }
    return 0;
}
} // lua_text_edit

void TextEdit::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_text_edit::create },
        { "setText", lua_text_edit::setText },
        { "getText", lua_text_edit::getText },
        { "setFont", lua_text_edit::setFont },
        { "setColour", lua_text_edit::setColour },
        { "setTextAlignment", lua_text_edit::setTextAlignment },
        { NULL, NULL }
    };
    stack.loadLibs("TextEdit", functions);
}

} // stren