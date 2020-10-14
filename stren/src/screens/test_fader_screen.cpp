#include "screens/test_fader_screen.h"

#include "engine_handler.h"
#include "widgets/button.h"
#include "widgets/fader.h"
#include "widgets/label.h"
#include "widgets/primitive.h"
#include "screen_ids.h"

namespace stren
{

TestFaderScreen::TestFaderScreen()
    : Screen("testFaderScreen")
{
    const int screenWidth = EngineHandler::getScreenWidth();
    const int screenHeight = EngineHandler::getScreenHeight();
    const int fadeSpeed = 255;
    
    Primitive * primitive = new Primitive();
    primitive->setColour(Colour::White);
    const Rect rect(0, 0, screenWidth, screenHeight);
    primitive->createRect(rect, true);
    attach(primitive);

    Button * btn = new Button("backBtn");
    btn->setText("Main Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->setOrder(2);
    btn->addCallback(EventType::MouseClicked, this, &TestFaderScreen::onBackBtnClick);
    btn->setColour(Colour::Red);
    attach(btn);

    Fader * fader = new Fader("fader");
    fader->setRect(0, 0, screenWidth, screenHeight);
    fader->setFadeSpeed(fadeSpeed);
    fader->setSprite("dark_img_spr");
    attach(fader);

    btn = new Button("fadeSpeedUpBtn");
    btn->setText("+");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(700, 620, 64, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestFaderScreen::onFadeSpeedUpBtnClick);
    attach(btn);

    btn = new Button("fadeSpeedDownBtn");
    btn->setText("-");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(800, 620, 64, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestFaderScreen::onFadeSpeedDownBtnClick);
    attach(btn);

    btn = new Button("fadeInBtn");
    btn->setText("Fade In");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(656, 428, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestFaderScreen::onFadeInBtnClick);
    attach(btn);

    btn = new Button("fadeOutBtn");
    btn->setText("Fade Out");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(656, 502, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestFaderScreen::onFadeOutBtnClick);
    attach(btn);

    Label * lbl = new Label();
    lbl->setRect(696, 566, 100, 64);
    lbl->setText("Fade speed:");
    lbl->setFont("robo_bold_15_fnt");
    lbl->setTextAlignment(Alignment::Right | Alignment::Middle);
    lbl->setColour(Colour::Red);
    attach(lbl);

    lbl = new Label("fadeSpeedLbl");
    lbl->setRect(810, 566, 256, 64);
    lbl->setText(std::to_string(fadeSpeed));
    lbl->setFont("robo_bold_15_fnt");
    lbl->setTextAlignment(Alignment::Left | Alignment::Middle);
    lbl->setColour(Colour::Blue);
    attach(lbl);
}

TestFaderScreen::~TestFaderScreen()
{
}

void TestFaderScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(nullptr, nullptr);
}

void TestFaderScreen::onFadeSpeedUpBtnClick()
{
    if (Fader * fader = findWidget<Fader>("fader"))
    {
        int speed = fader->getFadeSpeed();
        fader->setFadeSpeed(speed + 1);
        if (Label * lbl = findWidget<Label>("fadeSpeedLbl"))
        {
            speed = fader->getFadeSpeed();
            lbl->setText(std::to_string(speed));
        }
    }
}

void TestFaderScreen::onFadeSpeedDownBtnClick()
{
    if (Fader * fader = findWidget<Fader>("fader"))
    {
        int speed = fader->getFadeSpeed();
        fader->setFadeSpeed(speed - 1);
        if (Label * lbl = findWidget<Label>("fadeSpeedLbl"))
        {
            speed = fader->getFadeSpeed();
            lbl->setText(std::to_string(speed));
        }
    }
}

void TestFaderScreen::onFadeInBtnClick()
{
    if (Fader * fader = findWidget<Fader>("fader"))
    {
        fader->fadeIn();
    }
}

void TestFaderScreen::onFadeOutBtnClick()
{
    if (Fader * fader = findWidget<Fader>("fader"))
    {
        fader->fadeOut();
    }
}

} // stren
