#include "timer.h"

#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Timer::Timer(const std::string & id)
    : Widget(id)
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
    const size_t handler = EngineHandler::storeInMemoryController(new Timer(id));
    stack.push(handler);
    return 1;
}

int restart(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Timer * timer = EngineHandler::getMemoryObj<Timer *>(tbl);
    if (timer)
    {
        const int ms = stack.get(2).getInt();
        timer->restart(ms);
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
        { NULL, NULL }
    };
    stack.loadLibs("Timer", functions);
}
} // stren