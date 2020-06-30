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
    /// Construcor
    ///
    Screen(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Screen();
};
} // stren

#endif // STREN_SCREEN_H
