#include "screens/start_screen.h"

#include "widgets/button.h"
#include "widgets/label.h"
#include "widgets/timer.h"
#include "engine_handler.h"
#include "screen_ids.h"

namespace stren
{

StartScreen::StartScreen()
    : Screen("startScreen")
{
    const int screenWidth = EngineHandler::getScreenWidth();
    const int screenHeight = EngineHandler::getScreenHeight();

    Button * logoBtn = new Button("logo_btn");
    logoBtn->setRect(0, 0, screenWidth, screenHeight);
    logoBtn->setAlignment(Alignment::Left|Alignment::Top, 0, 0);
    logoBtn->addCallback(EventType::MouseClicked, this, &StartScreen::switchToNextScreen);
    attach(logoBtn);

    Label * lbl = new Label();
    lbl->setRect(0, 0, 200, 40);
    lbl->setText("Click to continue.");
    lbl->setAlignment(Alignment::Center | Alignment::Bottom, -40, 0);
    lbl->setFont("robo_bold_24_fnt");
    lbl->setColour(Colour::White);
    lbl->setTextAlignment(Alignment::Center | Alignment::Bottom);
    attach(lbl);

    Timer * timer = new Timer();
    timer->restart(5000);
    timer->addCallback(EventType::TimerElapsed, this, &StartScreen::switchToNextScreen);
    attach(timer);
}

StartScreen::~StartScreen()
{
}

void StartScreen::switchToNextScreen()
{
    EngineHandler::switchScreen(ScreenId::MainScreen);
}
} // stren
