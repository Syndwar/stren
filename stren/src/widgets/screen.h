#ifndef STREN_SCREEN_H
#define STREN_SCREEN_H

#include "container.h"
namespace stren
{
///
/// class Screen
///
class Screen : public Container
{
public:
    ///
    /// Constructor
    ///
    Screen(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Screen();
    ///
    /// @todo
    ///
    static void bind();
};
} // stren

#endif // STREN_SCREEN_H
