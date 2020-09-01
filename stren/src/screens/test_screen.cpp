#include "screens/test_screen.h"

#include "widgets/button.h"
#include "engine_handler.h"
#include "screen_ids.h"

namespace stren
{
TestScreen::TestScreen()
    : Screen("testScreen")
{
    Button * btn = new Button("backBtn");
    btn->setText("Main Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::onBackBtnClick);
    btn->setColour(Colour::Red);
    attach(btn);

    btn = new Button("testPrimitiveScreenBtn");
    btn->setText("Test Primitives Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 138);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toTestPrimitiveScreen);
    attach(btn);

    btn = new Button("testFaderScreenBtn");
    btn->setText("Test Fader Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 212);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toTestFaderScreen);
    attach(btn);

    btn = new Button("testSoundScreenBtn");
    btn->setText("Test Sound Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 286);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toTestSoundScreen);
    attach(btn);

    btn = new Button("testWidgetsScreenBtn");
    btn->setText("Test Widgets Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 360);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toTestWidgetsScreen);
    attach(btn);

    btn = new Button("testScrollScreenBtn");
    btn->setText("Test Scroll Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 434);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toTestScrollScreen);
    attach(btn);

    btn = new Button("testFontScreenBtn");
    btn->setText("Test Font Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 508);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toTestFontScreen);
    attach(btn);

    btn = new Button("testAtlasScreenBtn");
    btn->setText("Test Atlas Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 582);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toAtlasScreen);
    attach(btn);

    btn = new Button("testBattlefieldScreenBtn");
    btn->setText("Test BattleField Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 656);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestScreen::toBattlefield);
    attach(btn);
}

TestScreen::~TestScreen()
{
}

void TestScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(ScreenId::MainScreen);
}

void TestScreen::toTestPrimitiveScreen()
{
    EngineHandler::switchScreen(ScreenId::TestPrimitiveScreen);
}

void TestScreen::toTestFaderScreen()
{
    EngineHandler::switchScreen(ScreenId::TestFaderScreen);
}

void TestScreen::toTestSoundScreen()
{
    EngineHandler::switchScreen(ScreenId::TestSoundScreen);
}

void TestScreen::toTestWidgetsScreen()
{
    EngineHandler::switchScreen(ScreenId::TestWidgetsScreen);
}

void TestScreen::toTestScrollScreen()
{
    EngineHandler::switchScreen(ScreenId::TestScrollScreen);
}

void TestScreen::toTestFontScreen()
{
    EngineHandler::switchScreen(ScreenId::TestFontScreen);
}

void TestScreen::toAtlasScreen()
{
    EngineHandler::switchScreen(ScreenId::TestAtlasScreen);
}

void TestScreen::toBattlefield()
{
    EngineHandler::switchScreen(ScreenId::TestBattlefieldScreen);
}
} // stren