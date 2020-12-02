#ifndef STREN_LISTENER
#define STREN_LISTENER

#include <map>
#include <memory>

#include "common/string_ext.h"
#include "common/delegate.h"

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
    ///
    /// call the callback with one param
    ///
    virtual void call(Widget * sender, const std::string & param) = 0;
};
///
/// class DelegateCallback
///
class DelegateCallback : public ICallback
{
private:
    Delegate m_callback; ///< delegate type callback
public:
    ///
    /// connect Holder's Method with the caller
    ///
    template<typename Holder, typename Method>
    void connect(Holder * holder, Method method)
    {
        m_callback.connect(holder, method);
    }
    ///
    /// call the delegate callback
    ///
    virtual void call(Widget * sender) override
    {
        m_callback(sender);
    }
    ///
    /// call the callback with one param
    ///
    virtual void call(Widget * sender, const std::string & param) override
    {
        m_callback(sender, param);
    }
};
///
/// class VmCallback
///
class VmCallback : public ICallback
{
private:
    std::string m_callback; ///< lua function type callback
public:
    ///
    /// Constructor
    ///
    VmCallback(const std::string & callback)
        : m_callback(callback)
    {
    }
    ///
    /// call the lua function callback
    ///
    virtual void call(Widget * sender) override;
    ///
    /// call the lua function with one param
    ///
    virtual void call(Widget * sender, const std::string & param) override;
};

template<typename Method, typename Param>
class VmCallback2 : public ICallback
{
private:
    Method m_method; // vm method
    Param m_param; // vm param
public:
    ///
    /// Constructor
    ///
    VmCallback2(const Method & method, const Param & param)
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
    ///
    /// call the lua function with one param
    ///
    virtual void call(Widget * sender, const std::string & param) override
    {
        lua::Function func(m_method);
        std::vector<lua::Value> values = { m_param, static_cast<void *>(sender), param };
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
    /// add delegate callback
    ///
    template<typename Holder, typename Method>
    void addCallback(EventType eventType, Holder * holder, Method method)
    {
        auto callback = std::make_unique<DelegateCallback>();
        callback->connect(holder, method);
        m_callbacks[eventType] = std::move(callback);
    }
    ///
    /// add vm callback
    ///
    template<typename Method, typename Param>
    void addCallback(const std::string & type, const Method & method, const Param & param)
    {
        EventType eventType = Event::strToType(type);
        auto callback = std::make_unique<VmCallback2<Method, Param>>(method, param);
        m_callbacks[eventType] = std::move(callback);
    }
    ///
    /// add vm callback with no params
    ///
    void addCallback(const std::string & type, const std::string & callback);
    ///
    /// add vm callback with no params
    ///
    void addCallback(const EventType & type, const std::string & callback);
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
    /// call the callback with one param
    ///
    void callBack(const EventType & type, Widget * widget, const std::string & param);
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