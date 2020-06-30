#include "label.h"

#include "SDL.h"

#include "point.h"
#include "renderer.h"
#include "glyph.h"

namespace stren
{
Label::Label(const std::string & id)
    : Widget(id)
    , textAlignment_(Alignment::CenterMiddle)
{
}

Label::~Label()
{
}

void Label::setColour(const Colour & colour)
{
    label_.setColour(colour);
    addUpdateState(UpdateState::Update);
}

void Label::setFont(const std::string & fontId)
{
    label_.setFont(fontId);
    addUpdateState(UpdateState::Update);
}

void Label::setText(const std::string & text)
{
    label_.setText(text);
    addUpdateState(UpdateState::Update);
}

const std::string & Label::getText() const
{
    return label_.getText();
}

void Label::setTextAlignment(const int alignment)
{
    textAlignment_ = alignment;
    addUpdateState(UpdateState::Update);
}

void Label::setTextAlignment(const std::string & alignment)
{
    setTextAlignment(Alignment::stringToAlignment(alignment));
}

void Label::doPostMove(const int dx, const int dy)
{
    label_.align(getRect(), textAlignment_);
}

void Label::doRender()
{
    if (hasUpdateState(UpdateState::Update))
    {
        label_.update(getRect(), textAlignment_);
        removeUpdateState(UpdateState::Update);
    }

    label_.render();
}

} // stren