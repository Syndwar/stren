#include "debug_panel.h"

#include "engine/engine_handler.h"

#include "widgets/label.h"

namespace stren
{
DebugPanel::DebugPanel(const std::string & id)
    : Dialog(id)
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