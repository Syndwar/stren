#include "transform.h"

#include "render/renderer.h"
#include "lua/lua_wrapper.h"
#include <memory>

#define TransformPointsLimit 100

namespace stren
{

Transform::Transform()
    : m_state(State::Idle)
    , m_isDirty(false)
    , m_index(0)
    , m_time(0)
    , m_preTransformAlpha(0)
{
}

void Transform::free()
{
    m_values.clear();
}

void Transform::apply()
{
    if (!started() || finished()) return;

    for (int i = m_index, iEnd = m_values.size(); i < iEnd; ++i)
    {
        const TransformStep & value = m_values[i];
        if (i == iEnd - 1)
        {
            m_index = i;
            const TransformStep & value = m_values[m_index];
            m_preTransformAlpha = Renderer::getAlpha();
            Renderer::setAlpha(value.getValue());
            m_isDirty = true;
        }
        else if (value.getTime() <= m_time)
        {
            m_index = i;
        }
        else
        {
            const TransformStep & value = m_values[m_index];
            m_preTransformAlpha = Renderer::getAlpha();
            Renderer::setAlpha(value.getValue());
            m_isDirty = true;
            return;
        }
    }

    m_state = State::Finished;
}

void Transform::calculate()
{
    std::vector<TransformStep> newValues;

    if (m_values.empty()) return;

    size_t i = 0;

    const size_t pointsCount = m_values.size();

    newValues.push_back(m_values[i]);

    int startValue = m_values[i].getValue();
    int startTime = m_values[i].getTime();
    
    ++i;

    while (i < pointsCount)
    {
        const size_t step = (TransformPointsLimit - pointsCount) / (pointsCount - 1);

        const int endValue = m_values[i].getValue();
        const int endTime = m_values[i].getTime();

        const float valueChange = (endValue - startValue) / static_cast<float>(step);
        const float timeChange = (endTime - startTime) / static_cast<float>(step);

        size_t lastTimeValue = startTime;

        for (size_t j = 0; j < step; ++j)
        {
            const int midValue = static_cast<int>(startValue + valueChange * j);
            const size_t midTime = startTime + static_cast<size_t>(timeChange * j);
            if (midTime != lastTimeValue)
            {
                newValues.push_back(TransformStep(midValue, midTime));
                lastTimeValue = midTime;
            }
        }

        startValue = endValue;
        startTime = endTime;

        newValues.push_back(m_values[i]);
        ++i;
    }

    m_values = std::move(newValues);
}

void Transform::restore()
{
    if (m_isDirty)
    {
        Renderer::setAlpha(m_preTransformAlpha);
        m_isDirty = false;
    }
}

void Transform::start()
{
    m_state = State::Started;
    m_index = 0;
    m_time = 0;
    calculate();
}


void Transform::stop()
{
    m_state = State::Finished;
}

void Transform::update(const size_t dt)
{
    // check if transformation was finished
    if (!started() || finished()) return;

    m_time += dt;
}

void Transform::add(const int start, const int end, const size_t time)
{
    const bool isEmpty = m_values.empty();
    const size_t lastTime = isEmpty ? 0 : m_values.back().getTime();
    if (isEmpty || m_values.back().getValue() != start)
    {
        m_values.push_back(TransformStep(start, lastTime));
    }
    m_values.push_back(TransformStep(end, lastTime + time));
}

namespace lua_transform 
{
int create(lua_State * L)
{
    lua::Stack stack(0); // __call pushes tbl on the stack, so stack size is 1
    const size_t size = sizeof(Transform *);
    Transform ** transform = (Transform **)stack.createNewFullDataWitMetatable(size, "luaL_Transform");
    *transform = new Transform();
    return 1;
}

int free(lua_State *L)
{
    lua::Stack stack(1);
    Transform ** transform = (Transform **)stack.get(1).getUserData();
    if (transform && *transform)
    {
        delete (*transform);
        (*transform) = nullptr;
    }
    return 0;
}

int add(lua_State * L)
{
    lua::Stack stack(4);
    Transform ** transform = (Transform **)stack.get(1).getUserData();
    if (transform && *transform)
    {
        const int start = stack.get(2).getInt();
        const int end = stack.get(3).getInt();
        const size_t time = (size_t)stack.get(4).getInt();
        (*transform)->add(start, end, time);
    }
    return 0;
}
} //lua_transform

void Transform::bind()
{
    luaL_Reg functions[] =
    {
        { "add", lua_transform::add },
        { "__gc", lua_transform::free },
        { NULL, NULL }
    };
    luaL_Reg metafunctions[] =
    {
        { "__call", lua_transform::create },
        { NULL, NULL }
    };
    lua::Stack stack;
    stack.createNewMetatable("luaL_Transform", "Transform", functions, metafunctions);
}

} // stren