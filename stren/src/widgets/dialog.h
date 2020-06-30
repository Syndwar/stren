#ifndef STREN_DIALOG_H
#define STREN_DIALOG_H

#include "container.h"

namespace stren
{
///
/// class Dialog
///
class Dialog : public Container
{
public:
    ///
    /// Constructor
    ///
    Dialog(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Dialog();
};

} // stren

#endif // STREN_DIALOG_H
