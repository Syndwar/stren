#include "screen.h"

namespace stren
{

Screen::Screen(const std::string & id)
    : Container(id)
{
    setState(ViewState::Closed);
}

Screen::~Screen()
{
}

} // stren