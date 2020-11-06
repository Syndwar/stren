#include "widgets/text_edit.h"

#include "engine/engine_handler.h"
#include "engine/event.h"
#include "engine/action.h"
#include "lua/lua_wrapper.h"

namespace stren
{

///
/// class TextInputAction provides an ability to modify text in the control
///
class TextInputAction : public IAction
{
private:
    TextEdit *  m_container;     ///< container who created the action
public:
    ///
    /// Constructor
    ///
    TextInputAction(TextEdit * container) : IAction(), m_container(container) {}
    ///
    /// Destructor
    ///
    virtual ~TextInputAction() {}
    ///
    /// Start action
    ///
    virtual bool exec() override { return false; }
    ///
    /// Start action
    ///
    virtual bool exec(const Event & event) override
    {
        if (m_container && m_container->isInputMode())
        {
            if ("Return" == event.key || "Escape" == event.key)
            {
                m_container->cancelInputMode();
            }
            else if ("Backspace" == event.key)
            {
                std::string new_text = m_container->getText();
                if (new_text.size() > 1)
                {
                    new_text.pop_back();
                    new_text.pop_back();
                    new_text.append("|");
                    m_container->setText(new_text);
                }
            }
            else if ("Space" == event.key)
            {
                std::string new_text = m_container->getText();
                new_text.pop_back();
                new_text.append(" |");
                m_container->setText(new_text);
            }
            else if (1 == event.key.size())
            {
                std::string new_text = m_container->getText();
                new_text.pop_back();
                if (Event::KeyMod::Shift == event.mod)
                {
                    const char input[] = { (char)toupper(event.key[0]), "\0" };
                    new_text.append(input);
                }
                else
                {
                    const char input[] = { (char)tolower(event.key[0]), "\0" };
                    new_text.append(input);
                }
                new_text.append("|");
                m_container->setText(new_text);
            }
        }
        return false;
    }
};
///
/// class MouseInputAction provides an ability to enable text input mode
///
class MouseInputAction : public IAction
{
private:
    TextEdit *  m_container;     ///< container who created the action
public:
    ///
    /// Constructor
    ///
    MouseInputAction(TextEdit * container) : IAction(), m_container(container) {}
    ///
    /// Destructor
    ///
    virtual ~MouseInputAction() {}
    ///
    /// Start action
    ///
    virtual bool exec() override { return false; }
    ///
    /// Start action
    ///
    virtual bool exec(const Event & event) override
    {
        if (m_container && m_container->getRect().hasCommon(event.pos))
        {
            m_container->enableInputMode();
            return true;
        }
        return false;
    }
};
///
/// class TextEdit
///
TextEdit::TextEdit(const std::string & id)
    : Widget(id)
    , m_textAlignment(Alignment::CenterMiddle)
    , m_isInputMode(false)
{
    IAction * action = nullptr;
    action = new TextInputAction(this);
    size_t key(0);
    key = EngineHandler::addKeyboardAction(EventType::KeyUp, "", action);
    m_actionKeys.push_back(key);
    action = new MouseInputAction(this);
    key = EngineHandler::addMouseAction(EventType::MouseUp, Event::MouseButton::None, action);
    m_actionKeys.push_back(key);
}

TextEdit::~TextEdit()
{
    for (size_t key : m_actionKeys)
    {
        EngineHandler::removeKeyboardAction(key);
    }
}

void TextEdit::enableInputMode()
{
    m_isInputMode = true;
    std::string new_text = getText();
    setText(new_text.append("|"));
}

void TextEdit::cancelInputMode()
{
    std::string new_text = getText();
    new_text.pop_back();
    setText(new_text);
    m_isInputMode = false;
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

namespace lua_text_edit
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    TextEdit * edit = new TextEdit(id);
    stack.clear();
    stack.push((void *)edit);
    return stack.getSize();
}

int setText(lua_State * L)
{
    lua::Stack stack(2);
    TextEdit * edit = (TextEdit *)stack.get(1).getUserData();
    if (edit)
    {
        const std::string text = stack.get(2).getString();
        edit->setText(text);
    }

    stack.clear();
    return 0;
}

int setFont(lua_State * L)
{
    lua::Stack stack(2);
    TextEdit * edit = (TextEdit *)stack.get(1).getUserData();
    if (edit)
    {
        const std::string font = stack.get(2).getString();
        edit->setFont(font);
    }
    stack.clear();
    return 0;
}

int setColour(lua_State * L)
{
    lua::Stack stack(2);
    TextEdit * edit = (TextEdit *)stack.get(1).getUserData();
    if (edit)
    {
        const std::string colorStr = stack.get(2).getString();
        edit->setColour(colorStr);
    }
    stack.clear();
    return 0;
}

int setTextAlignment(lua_State * L)
{
    lua::Stack stack(2);
    TextEdit * edit = (TextEdit *)stack.get(1).getUserData();
    if (edit)
    {
        const std::string textAlign = stack.get(2).getString();
        edit->setTextAlignment(textAlign);
    }
    stack.clear();
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
        { "setFont", lua_text_edit::setFont },
        { "setColour", lua_text_edit::setColour },
        { "setTextAlignment", lua_text_edit::setTextAlignment },
        { NULL, NULL }
    };
    stack.loadLibs("TextEdit", functions);
}

} // stren