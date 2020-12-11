#ifndef STREN_LISTENER
#define STREN_LISTENER

#include <map>
#include <memory>

#include "common/string_ext.h"

namespace stren
{
class Widget;
enum class EventType;
///
/// class ICallback
///
class ICallback
{
public:
    ///
    /// call the callback
    ///
    virtual void call(Widget * sender) = 0;
};
///
/// class VmCallback
///
template<typename Method, typename Param>
class VmCallback : public ICallback
{
private:
    Method m_method; // vm method
    Param m_param; // vm param
public:
    ///
    /// Constructor
    ///
    VmCallback(const Method & method, const Param & param)
        : m_method(method)
        , m_param(param)
    {
    }
    ///
    /// call the lua function callback
    ///
    virtual void call(Widget * sender) override
    {
        lua::Function func(m_method);
        std::vector<lua::Value> values = { m_param, static_cast<void *>(sender) };
        func.call(values);
    }
};
///
/// class Listener
///
class Listener
{
private:
    std::map<EventType, std::unique_ptr<ICallback>> m_callbacks; // a list of callbacks listener must call
public:
    ///
    /// add vm callback
    ///
    template<typename Method, typename Param>
    void addCallback(const std::string & type, const Method & method, const Param & param)
    {
        EventType eventType = Event::strToType(type);
        auto callback = std::make_unique<VmCallback<Method, Param>>(method, param);
        m_callbacks[eventType] = std::move(callback);
    }
    ///
    /// delete specific callback
    ///
    void removeCallback(const std::string & type);
    ///
    /// delete specific callback
    ///
    void removeCallback(const EventType & type);
    ///
    /// call the callback
    ///
    void callBack(const EventType & type, Widget * widget);
    ///
    /// return if callback exist
    ///
    bool hasCallback(const EventType & type) const;
    ///
    /// delete all callbacks
    ///
    void clear();
};
} // stren

#endif // STREN_LISTENER