#include "lua_binding.h"

#include "engine/engine_handler.h"
#include "widgets/screen.h"
#include "widgets/dialog.h"
#include "widgets/label.h"
#include "widgets/button.h"
#include "widgets/timer.h"
#include "widgets/primitive.h"
#include "widgets/fader.h"
#include "widgets/image.h"
#include "widgets/area.h"
#include "widgets/scroll_container.h"
#include "widgets/progressbar.h"
#include "game/game.h"

namespace lua
{
void bindWithVM()
{
    stren::EngineHandler::bind();
    stren::Game::bind();
    stren::Widget::bind();
    stren::Image::bind();
    stren::Primitive::bind();
    stren::Fader::bind();
    stren::Timer::bind();
    stren::Button::bind();
    stren::Label::bind();
    stren::Container::bind();
    stren::Dialog::bind();
    stren::ScrollContainer::bind();
    stren::Screen::bind();
    stren::Area::bind();
    stren::ProgressBar::bind();
    stren::Transform::bind();
}
} // lua