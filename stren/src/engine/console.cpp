#include "console.h"

#include "engine_handler.h"
#include "event.h"
#include "widgets/label.h"
#include "widgets/primitive.h"
#include "widgets/image.h"

namespace stren
{

Console::Console(const std::string & id)
    : Dialog(id)
    , index_(0)
{
    const int screenWidth = EngineHandler::getScreenWidth();
    const int screenHeight = EngineHandler::getScreenHeight();
    const int dialogHeight = screenHeight / 2;

    Image * backImg = new Image();
    backImg->setRect(0, 0, screenWidth, dialogHeight);
    backImg->setSprite("dark_img_spr");
    attach(backImg);

    Primitive * primitive = new Primitive();
    primitive->createLines({ { 0, 0 },{ screenWidth, 0 } });
    primitive->moveBy(0, dialogHeight);
    primitive->setColour(Colour::Green);
    attach(primitive);

    const size_t labelHeight = 16;
    const size_t labelsAmount = dialogHeight / labelHeight;
    for (size_t i = 0; i < labelsAmount; ++i)
    {
        Label * lbl = new Label();
        lbl->setRect(0, i * labelHeight, screenWidth, labelHeight);
        lbl->setColour(Colour::White);
        lbl->setTextAlignment(Alignment::LeftTop);
        lbl->setFont("system_16_fnt");
        attach(lbl);

        labels_.push_back(lbl);
    }
    stack_.resize(labelsAmount);
}

Console::~Console()
{
}

void Console::log(const std::string & message)
{
    std::string tmp(message);
    for (size_t i = stack_.size(); i > 0; --i)
    {
        std::string & value = stack_[i - 1];
        std::string oldValue = std::move(value);
        value = std::move(tmp);
        tmp = std::move(oldValue);
    }
    
    size_t i(0);
    for (Label * lbl : labels_)
    {
        if (lbl)
        {
            lbl->setText(stack_[i]);
            ++i;
        }
    }
}
} // stren