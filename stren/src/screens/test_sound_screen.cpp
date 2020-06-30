#include "screens/test_sound_screen.h"

#include "engine_handler.h"
#include "sound_system.h"
#include "widgets/button.h"
#include "screen_ids.h"

namespace stren
{
TestSoundScreen::TestSoundScreen()
    : Screen("testSoundScreen")
{
    Button* btn = new Button("backBtn");
    btn->setText("Main Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestSoundScreen::onBackBtnClick);
    btn->setColour(Colour::Red);
    attach(btn);

    btn = new Button("playMusicBtn");
    btn->setText("Music On");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(256, 0, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestSoundScreen::onPlayMusicBtnClick);
    btn->setColour(Colour::Red);
    attach(btn);

    btn = new Button("stopMusicBtn");
    btn->setText("Music Off");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(256, 64, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestSoundScreen::onStopMusicBtnClick);
    btn->setColour(Colour::Red);
    attach(btn);

    btn = new Button("playSoundBtn");
    btn->setText("Play Sound");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(512, 0, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestSoundScreen::onPlaySoundBtnClick);
    btn->setColour(Colour::Red);
    attach(btn);
}

TestSoundScreen::~TestSoundScreen()
{
}

void TestSoundScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(ScreenId::MainScreen);
}

void TestSoundScreen::onPlayMusicBtnClick()
{
    if (SoundSystem * soundSystem = EngineHandler::getSoundSystem())
    {
        soundSystem->playMusic("main_menu_mus");
    }
}

void TestSoundScreen::onStopMusicBtnClick()
{
    if (SoundSystem * soundSystem = EngineHandler::getSoundSystem())
    {
        soundSystem->stopMusic();
    }
}

void TestSoundScreen::onPlaySoundBtnClick()
{
    if (SoundSystem * soundSystem = EngineHandler::getSoundSystem())
    {
        soundSystem->playSound("kick_snd", 0);
    }
}
} // stren


    