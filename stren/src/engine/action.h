#ifndef STREN_ACTION_H
#define STREN_ACTION_H
namespace stren 
{
class Event;
///
/// class IAction
///
class IAction
{
public:
    ///
    /// Destructor
    ///
    virtual ~IAction() {}
    ///
    /// @todo
    ///
    virtual bool exec() = 0;
    ///
    /// @todo
    ///
    virtual bool exec(const Event & event) = 0;
};

} // stren
#endif // STREN_ACTION_H