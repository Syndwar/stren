#ifndef STREN_ACTION_H
#define STREN_ACTION_H
namespace stren 
{
///
/// class IAction
///
class IAction
{
public:
    ///
    /// @todo
    ///
    virtual void exec() = 0;
    ///
    /// @todo
    ///
    virtual void cancel() = 0;
};

} // stren
#endif // STREN_ACTION_H