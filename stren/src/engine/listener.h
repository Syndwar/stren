#ifndef STREN_LISTENER
#define STREN_LISTENER

#include <map>
#include <memory>

#include "common/string_ext.h"
#include "common/delegate.h"

namespace stren
{
class Widget;
enum EventType;
///
/// class ICallback
///
class ICallback
{
public:
    ///
    /// call the callback
    ///
    virtual void call(const EventType & type, Widget * sender) = 0;
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
    virtual void call(const EventType & type, Widget * sender) override
    {
        m_callback(sender);
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
    virtual void call(const EventType & type, Widget * sender) override;
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
    /// add specific callback
    ///
    void addCallback(const std::string & type, const std::string & callback);
    ///
    /// add specific callback
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