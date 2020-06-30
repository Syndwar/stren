#include "debug_panel.h"

#include "engine_handler.h"

#include "widgets/label.h"

namespace stren
{
DebugPanel::DebugPanel(const std::string & id)
    : Dialog(id)
{
    Label * fpsLbl = new Label("fpsLbl");
    fpsLbl->setFont("robo_bold_15_fnt");
    fpsLbl->setTextAlignment(Alignment::CenterMiddle);
    fpsLbl->setRect(0, 0, 100, 30);
    fpsLbl->setColour(Colour::Green);
    fpsLbl->setAlignment(Alignment::LeftTop, 0, 0);
    attach(fpsLbl);

    Label * mousePosLbl = new Label("mousePosLbl");
    mousePosLbl->setFont("robo_bold_15_fnt");
    mousePosLbl->setTextAlignment(Alignment::CenterMiddle);
    mousePosLbl->setRect(0, 0, 120, 30);
    mousePosLbl->setColour(Colour::Green);
    mousePosLbl->setAlignment(Alignment::RightTop, 0, 0);
    attach(mousePosLbl);
}

DebugPanel::~DebugPanel()
{
}

void DebugPanel::doUpdate(const size_t dt)
{
    updateFps(std::to_string(EngineHandler::getFPS()));
    const Point & mousePos = EngineHandler::getMousePos();
    updateMousePos(mousePos.getX(), mousePos.getY());

    Dialog::doUpdate(dt);
}

void DebugPanel::updateFps(const std::string & text)
{
    if (Label * lbl = findWidget<Label>("fpsLbl"))
    {
        lbl->setText(text);
    }
}

void DebugPanel::updateMousePos(const int x, const int y)
{
    if (Label * lbl = findWidget<Label>("mousePosLbl"))
    {
        static std::string text;
        text.clear();
        text = std::to_string(x) + "|" + std::to_string(y);
        lbl->setText(text);
    }
}
} // stren