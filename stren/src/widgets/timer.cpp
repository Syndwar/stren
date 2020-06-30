#include "timer.h"
#include "event.h"

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
} // stren