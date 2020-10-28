#include "timer.h"

#include "engine/event.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Timer::Timer(const std::string & id)
    : Widget()
    , m_time(0)
    , m_workTime(0)
    , m_workState(WorkState::Stopped)
{
}

Timer::Timer(const size_t ms)
    : Widget()
    , m_time(ms)
    , m_workTime(0)
    , m_workState(WorkState::Stopped)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
    m_workState = WorkState::Running;
    m_workTime = 0;
}

void Timer::stop()
{
    m_workState = WorkState::Stopped;
    m_workTime = 0;
}

void Timer::restart(const size_t ms)
{
    m_time = ms;
    stop();
    start();
}

void Timer::pause()
{
    if (WorkState::Running == m_workState)
    {
        m_workState = WorkState::Paused;
    }
}

void Timer::resume()
{
    if (WorkState::Paused == m_workState)
    {
        m_workState = WorkState::Running;
    }
}

void Timer::update(const size_t dt)
{
    if (WorkState::Running == m_workState)
    {
        m_workTime += dt;
        if (m_workTime >= m_time)
        {
            m_workState = WorkState::Elapsed;
            callBack(EventType::TimerElapsed, this);
        }
    }
}

namespace lua_timer
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Timer * timer = new Timer(id);
    stack.clear();
    stack.push((void *)timer);
    return stack.getSize();
}

int restart(lua_State * L)
{
    lua::Stack stack(1);
    Timer * timer = (Timer *)stack.get(1).getUserData();
    if (timer)
    {
        const int ms = stack.get(2).getInt();
        timer->restart(ms);
    }
    stack.clear();
    return 0;
}

int addCallback(lua_State * L)
{
    lua::Stack stack(3);
    Timer * timer = (Timer *)stack.get(1).getUserData();
    if (timer)
    {
        const std::string eventTypeStr = stack.get(2).getString();
        const std::string callback = stack.get(3).getString();
        timer->addCallback(eventTypeStr, callback);
    }
    return 0;
}
} // lua_timer

void Timer::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_timer::create },
        { "restart", lua_timer::restart },
        { "addCallback", lua_timer::addCallback },
        { NULL, NULL }
    };
    stack.loadLibs("Timer", functions);
}
} // stren