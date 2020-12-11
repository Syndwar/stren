#include "memory_controller.h"

#include "widgets/widget.h"

namespace stren
{
MemoryController::MemoryController()
    : m_counter(0)
{
}

MemoryController::~MemoryController()
{
    release();
}

size_t MemoryController::store(Widget * widget)
{
    ++m_counter;
    m_content[m_counter] = widget;
    return m_counter;
}

size_t MemoryController::find(Widget * widget)
{
    if (widget)
    {
        for (const auto & it : m_content)
        {
            if (it.second == widget)
            {
                return it.first;
            }
        }
    }
    return 0;
}

void MemoryController::collectGarbage()
{
    if (!m_content.size()) return;

    for (auto it = m_content.cbegin(); it != m_content.cend(); /* */)
    {
        Widget * widget = it->second;
        if (widget && widget->isDead())
        {
            delete widget;
            it = m_content.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void MemoryController::release()
{
    if (m_content.size() > 0)
    {
        for (auto & it : m_content)
        {
            if (it.second)
            {
                delete it.second;
                it.second = nullptr;
            }
        }
        m_content.clear();
    }
    if (m_counter > 0)
    {
        m_counter = 0;
    }
}

} // stren