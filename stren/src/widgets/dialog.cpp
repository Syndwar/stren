#include "dialog.h"

namespace stren
{
Dialog::Dialog(const std::string & id /* = String::kEmpty */)
    : Container(id)
{
    setState(ViewState::Closed);
}

Dialog::~Dialog()
{
}

} // stren