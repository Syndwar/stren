#include "test_battle_field_screen.h"

#include "widgets/button.h"
#include "engine_handler.h"

namespace stren
{
///
/// class TestBattleFieldScreen
///
TestBattleFieldScreen::TestBattleFieldScreen()
    : Screen("testBattleFieldScreen")
{
    Button * backBtn = new Button("backBtn");
    backBtn->setText("Exit");
    backBtn->setFont("robo_bold_15_fnt");
    backBtn->setRect(0, 0, 64, 64);
    backBtn->setAlignment(Alignment::LeftBottom, 0, 0);
    backBtn->setTextAlignment(Alignment::CenterMiddle);
    backBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    backBtn->addCallback(EventType::MouseClicked, this, &TestBattleFieldScreen::onBackBtnClick);
    backBtn->setColour(Colour::Red);
    attach(backBtn);
}

TestBattleFieldScreen::~TestBattleFieldScreen()
{
}

void TestBattleFieldScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(nullptr);
}

} // stren
