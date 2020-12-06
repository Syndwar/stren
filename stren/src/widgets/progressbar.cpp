#include "progressbar.h"

#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "lua/lua_wrapper.h"

namespace stren
{

ProgressBar::ProgressBar(const std::string & id)
    : Widget(id)
    , m_type(Type::Horizontal)
    , m_currentValue(0)
    , m_maxValue(100)
    , m_fillSpeed(1)
    , m_updateInterval(1000)
    , m_targetValue(0)
    , m_camera(getRect())
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
    if (value <= m_maxValue)
    {
        m_currentValue = value;
    }
}

void ProgressBar::setFillSpeed(const int speed)
{
    m_fillSpeed = speed;
    m_updateInterval = 1000 / speed;
}

void ProgressBar::windTo(const int value)
{
    if (value <= m_maxValue)
    {
        m_targetValue = value;
        m_timer.restart(m_updateInterval);
    }
}

bool ProgressBar::isWinding() const
{
    return m_targetValue != m_currentValue;
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

    if (Type::Horizontal == m_type)
    {
        width = width * m_currentValue / m_maxValue;
    }
    else if (Type::Vertical == m_type)
    {
        const int oldHeight(height);
        height = height * m_currentValue / m_maxValue;
        top = top + oldHeight - height;
    }

    m_camera.moveTo(left, top);
    m_camera.resize(width, height);
    m_camera.place();
    m_sprite.render(rect, Sprite::Flip::None, 0, m_center);
    m_camera.restore();
}

void ProgressBar::doUpdate(const size_t dt)
{
    m_timer.update(dt);

    if (m_timer.isElapsed())
    {
        if (m_currentValue < m_targetValue)
        {
            ++m_currentValue;
            m_timer.restart(m_updateInterval);
        }
        else if (m_currentValue > m_targetValue)
        {
            --m_currentValue;
            m_timer.restart(m_updateInterval);
        }
        else
        {
            m_timer.stop();
        }
    }
}

void ProgressBar::loadSprite()
{
    if (!m_spriteId.empty())
    {
        if (Sprite * sprite = EngineHandler::getSprite(m_spriteId))
        {
            m_sprite = *sprite;
        }
    }
}

namespace lua_progressbar
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new ProgressBar(id));
    stack.push(handler);
    return 1;
}

int setSprite(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    ProgressBar * pb = EngineHandler::getMemoryObj<ProgressBar *>(tbl);
    if (pb)
    {
        const std::string spr = stack.get(2).getString();
        pb->setSprite(spr);
    }
    stack.clear();
    return 0;
}

int setCurrentValue(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    ProgressBar * pb = EngineHandler::getMemoryObj<ProgressBar *>(tbl);
    if (pb)
    {
        const int value = stack.get(2).getInt();
        pb->setCurrentValue(value);
    }
    stack.clear();
    return 0;
}

int setMaxValue(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    ProgressBar * pb = EngineHandler::getMemoryObj<ProgressBar *>(tbl);
    if (pb)
    {
        const int value = stack.get(2).getInt();
        pb->setMaxValue(value);
    }
    stack.clear();
    return 0;
}

int setFillSpeed(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    ProgressBar * pb = EngineHandler::getMemoryObj<ProgressBar *>(tbl);
    if (pb)
    {
        const int speed = stack.get(2).getInt();
        pb->setFillSpeed(speed);
    }
    stack.clear();
    return 0;
}

int setVertical(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    ProgressBar * pb = EngineHandler::getMemoryObj<ProgressBar *>(tbl);
    if (pb)
    {
        const bool isVertical = stack.get(2).getBool();
        pb->setVertical(isVertical);
    }
    stack.clear();
    return 0;
}

int windTo(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    ProgressBar * pb = EngineHandler::getMemoryObj<ProgressBar *>(tbl);
    if (pb)
    {
        const int value = stack.get(2).getInt();
        pb->windTo(value);
    }
    stack.clear();
    return 0;
}

int getCurrentValue(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    ProgressBar * pb = EngineHandler::getMemoryObj<ProgressBar *>(tbl);
    stack.clear();
    int value(0);
    if (pb)
    {
        value = pb->getCurrentValue();
    }
    stack.push(value);
    return stack.getSize();
}
} // lua_progressbar

void ProgressBar::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_progressbar::create },
        { "setSprite", lua_progressbar::setSprite },
        { "setCurrentValue", lua_progressbar::setCurrentValue },
        { "setMaxValue", lua_progressbar::setMaxValue },
        { "setFillSpeed", lua_progressbar::setFillSpeed },
        { "setVertical", lua_progressbar::setVertical },
        { "getCurrentValue", lua_progressbar::getCurrentValue },
        { "windTo", lua_progressbar::windTo },
        { NULL, NULL }
    };
    stack.loadLibs("ProgressBar", functions);
}

} // stren