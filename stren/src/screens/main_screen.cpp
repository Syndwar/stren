#include "main_screen.h"

#include "widgets/button.h"
#include "engine_handler.h"
#include "screen_ids.h"

namespace stren
{

MainScreen::MainScreen()
    : Screen("mainScreen")
{
    Button * btn = new Button("testBtn");
    btn->setText("Test Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setColour(Colour::Green);
    btn->setTextAlignment(Alignment::CenterMiddle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &MainScreen::onTestBtnClicked);
    attach(btn);

    btn = new Button("newGameBtn");
    btn->setText("New Game");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::RightTop, -64, 64);
    btn->setTextAlignment(Alignment::CenterMiddle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &MainScreen::onNewGameBtnClicked);
    attach(btn);

    btn = new Button("loadGameBtn");
    btn->setText("Load Game");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::RightTop, -64, 138);
    btn->setTextAlignment(Alignment::CenterMiddle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &MainScreen::onLoadGameBtnClick);
    attach(btn);

    btn = new Button("optionsBtn");
    btn->setText("Options");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::RightTop, -64, 212);
    btn->setTextAlignment(Alignment::CenterMiddle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &MainScreen::onOptionsBtnClick);
    attach(btn);

    btn = new Button("mapEditorBtn");
    btn->setText("Map Editor");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::RightTop, -64, 286);
    btn->setTextAlignment(Alignment::CenterMiddle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &MainScreen::onMapEditorBtnClick);
    attach(btn);

    btn = new Button("exitBtn");
    btn->setText("Exit");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setColour(Colour::Red);
    btn->setAlignment(Alignment::RightBottom, -64, -64);
    btn->setTextAlignment(Alignment::CenterMiddle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &MainScreen::onExitBtnClick);
    attach(btn);
}

MainScreen::~MainScreen()
{
}

void MainScreen::onTestBtnClicked()
{
    EngineHandler::switchScreen(nullptr, nullptr);
}

void MainScreen::onNewGameBtnClicked()
{
}

void MainScreen::onLoadGameBtnClick()
{
}

void MainScreen::onOptionsBtnClick()
{
    EngineHandler::switchScreen(nullptr, nullptr);
}

void MainScreen::onMapEditorBtnClick()
{
    EngineHandler::switchScreen(nullptr, nullptr);
}

void MainScreen::onExitBtnClick()
{
    EngineHandler::shutdown();
}
} // stren
