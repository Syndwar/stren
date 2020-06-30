#ifndef STREN_DELEGATE_H
#define STREN_DELEGATE_H

#include <assert.h>

namespace delegate_h
{
struct NIL {};
///
/// class IArguments - Arguments container, up to 2 arguments
///
class IArguments
{
public:
    ///
    /// Destructor
    ///
    virtual ~IArguments()
    {
    }
};

template< typename Arg1 = NIL, typename Arg2 = NIL >
class Arguments : public IArguments
{
public:
    Arg1 m_arg1; ///< first argument
    Arg2 m_arg2; ///< second argument
public:
    ///
    /// Constructor: no params
    ///
    Arguments()
    {
    }
    ///
    /// Constructor: one param
    ///
    Arguments(const Arg1 & arg1)
        : m_arg1(arg1)
    {
    }
    ///
    /// Constructor: two params
    ///
    Arguments(const Arg1 & arg1, const Arg2 & arg2)
        : m_arg1(arg1)
        , m_arg2(arg2)
    {
    }
};
///
/// class IContainer: arguments container
///
class IContainer
{
public: // methods
    ///
    /// call delegate methods
    ///
    virtual void call(IArguments * arguments) = 0;
};
///
/// class Container: default container
///
template<typename Holder, typename Method>
class Container : public IContainer
{
};
///
///  class Container: method without arguments
///
template<typename Holder>
class Container<Holder, void (Holder::*)(void)> : public IContainer
{
    typedef void (Holder::*Method)(void);
private:
    Holder * m_class;   ///< class
    Method m_method;    ///< method
public:
    ///
    /// Constructor
    ///
    Container(Holder * classType, Method method)
        : m_class(classType)
        , m_method(method)
    {
    }
    ///
    /// call delegate methods
    ///
    virtual void call(IArguments * arguments) override
    {
        (m_class->*m_method)();
    }
};
///
///  class Container: method with one argument
///
template<typename Holder, typename Arg1 >
class Container< Holder, void (Holder::*)(Arg1) > : public IContainer
{
    typedef void (Holder::*Method)(Arg1);
    typedef Arguments<Arg1> Arg;
private:
    Holder * m_class;   /// class
    Method m_method;    /// method
public:
    ///
    /// Constructor
    ///
    Container(Holder * classType, Method method)
        : m_class(classType)
        , m_method(method)
    {
    }
    ///
    /// call delegate methods
    ///
    virtual void call(IArguments * arguments) override
    {
        Arg * arg = dynamic_cast<Arg *>(arguments);
        assert(arg);
        if (arg)
        {
            (m_class->*m_method)(arg->m_arg1);
        }
    }
};

///
///  class Container: method with two arguments
///
template<typename Holder, typename Arg1, typename Arg2>
class Container< Holder, void (Holder::*)(Arg1, Arg2) > : public IContainer
{
    typedef void (Holder::*Method)(Arg1, Arg2);
    typedef Arguments<Arg1, Arg2> Arg;
private:
    Holder * m_class;   ///< class
    Method m_method;    ///< method

public:
    ///
    /// Constructor
    ///
    Container(Holder * classType, Method method)
        : m_class(classType)
        , m_method(method)
    {
    }
    ///
    /// call delegate methods
    ///
    virtual void call(IArguments * arguments) override
    {
        Arg * arg = dynamic_cast<Arg *>(arguments);
        assert(arg);
        if (arg)
        {
            (m_class->*m_method)(arg->m_arg1, arg->m_arg2);
        }
    }
};
} // delegate_h
///
/// class Delegate can hold and call methods from different classes
///
class Delegate
{
private:
    delegate_h::IContainer * m_container; ///< delegate container
public:
    ///
    /// Constructor
    ///
    Delegate()
        : m_container(nullptr)
    {
    }
    ///
    /// Destructor
    ///
    ~Delegate()
    {
        clear();
    }
    ///
    /// clear delegates
    ///
    void Delegate::clear()
    {
        if (m_container)
        {
            delete m_container;
            m_container = nullptr;
        }
    }
    ///
    /// connect methods with the delegate
    ///
    template<typename Holder, typename Method>
    void connect(Holder * holder, Method method)
    {
        if (m_container)
        {
            delete m_container;
        }
        m_container = new delegate_h::Container<Holder, Method>(holder, method);
    }
    ///
    /// call without arguments
    ///
    void operator()()
    {
        if (m_container)
        {
            m_container->call(&delegate_h::Arguments<>());
        }
    }
    ///
    /// call with one argument
    ///
    template<typename Arg1>
    void operator()(Arg1 arg)
    {
        if (m_container)
        {
            m_container->call(&delegate_h::Arguments< Arg1 >(arg));
        }
    }
    ///
    /// call with two arguments
    ///
    template<typename Arg1, typename Arg2>
    void operator() (Arg1 arg1, Arg2 arg2)
    {
        if (m_container)
        {
            m_container->call(&delegate_h::Arguments<Arg1, Arg2>(arg1, arg2));
        }
    }
};

#endif // STREN_DELEGATE_H