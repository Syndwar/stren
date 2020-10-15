#include "screens/options_screen.h"

#include "save_data.h"
#include "widgets/button.h"
#include "engine_handler.h"

namespace
{
const std::string kVSyncOn = "VSync On";
const std::string kVSyncOff = "VSync Off";
const std::string kWindowBorderOn = "Window Border On";
const std::string kWindowBorderOff = "Window Border Off";
const std::string kFullscreenOn = "Fullscreen On";
const std::string kFullscreenOff = "Fullscreen Off";

struct Resolution
{
    int width;
    int height;

    Resolution(const int w = 0, const int h = 0) : width(w), height(h) {}
};
const std::vector<Resolution> kResolutions = { { 800, 600 },{ 1024, 768 },{ 1280, 720 },{ 1360, 768 },{ 1600, 1900 },{ 1920, 1080 } };
}

namespace stren
{
OptionsScreen::OptionsScreen()
    : Screen("optionsScreen")
    , isVSync_(false)
    , isBorderless_(false)
    , isFullscreen_(false)
    , vSyncBtn_(nullptr)
    , fullscreenBtn_(nullptr)
    , borderlessBtn_(nullptr)
    , resIndex_(0)
{
    if (SaveData * saveData = EngineHandler::getSaveData())
    {
        isVSync_ = saveData->isVSync();
        isBorderless_ = saveData->isBorderless();
        isFullscreen_ = saveData->isFullscreen();
    }

    Button * backBtn = new Button("backBtn");
    backBtn->setText("Main Screen");
    backBtn->setFont("robo_bold_15_fnt");
    backBtn->setRect(0, 0, 256, 64);
    backBtn->setAlignment(Alignment::Right | Alignment::Top, -64, 64);
    backBtn->setTextAlignment(Alignment::Center | Alignment::Middle);
    backBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    backBtn->addCallback(EventType::MouseClicked, this, &OptionsScreen::onBackBtnClick);
    backBtn->setColour(Colour::Red);
    attach(backBtn);

    vSyncBtn_ = new Button("vsyncBtn");
    vSyncBtn_->setText(isVSync_ ? kVSyncOn : kVSyncOff);
    vSyncBtn_->setFont("robo_bold_15_fnt");
    vSyncBtn_->setRect(0, 0, 256, 64);
    vSyncBtn_->setAlignment(Alignment::Left | Alignment::Top, 64, 64);
    vSyncBtn_->setTextAlignment(Alignment::Center | Alignment::Middle);
    vSyncBtn_->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    vSyncBtn_->setColour(isVSync_ ? Colour::Green : Colour::Red);
    vSyncBtn_->addCallback(EventType::MouseClicked, this, &OptionsScreen::onVsyncBtnClick);
    attach(vSyncBtn_);

    borderlessBtn_ = new Button("borderlessBtn");
    borderlessBtn_->setText(isBorderless_ ? kWindowBorderOn : kWindowBorderOff);
    borderlessBtn_->setFont("robo_bold_15_fnt");
    borderlessBtn_->setRect(0, 0, 256, 64);
    borderlessBtn_->setAlignment(Alignment::Left | Alignment::Top, 64, 128);
    borderlessBtn_->setTextAlignment(Alignment::Center | Alignment::Middle);
    borderlessBtn_->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    borderlessBtn_->setColour(isBorderless_ ? Colour::Green : Colour::Red);
    borderlessBtn_->addCallback(EventType::MouseClicked, this, &OptionsScreen::onBorderlessBtnClick);
    attach(borderlessBtn_);

    fullscreenBtn_ = new Button("fullscreenBtn");
    fullscreenBtn_->setText(isFullscreen_ ? kFullscreenOn : kFullscreenOff);
    fullscreenBtn_->setFont("robo_bold_15_fnt");
    fullscreenBtn_->setRect(0, 0, 256, 64);
    fullscreenBtn_->setAlignment(Alignment::Left | Alignment::Top, 64, 196);
    fullscreenBtn_->setTextAlignment(Alignment::Center | Alignment::Middle);
    fullscreenBtn_->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    fullscreenBtn_->setColour(isFullscreen_ ? Colour::Green : Colour::Red);
    fullscreenBtn_->addCallback(EventType::MouseClicked, this, &OptionsScreen::onFullscreenBtnClick);
    attach(fullscreenBtn_);

    Button * applyBtn = new Button("applyBtn");
    applyBtn->setText("Apply");
    applyBtn->setFont("robo_bold_15_fnt");
    applyBtn->setRect(0, 0, 256, 64);
    applyBtn->setAlignment(Alignment::Right | Alignment::Bottom, -64, -64);
    applyBtn->setTextAlignment(Alignment::Center | Alignment::Middle);
    applyBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    applyBtn->setColour(Colour::White);
    applyBtn->addCallback(EventType::MouseClicked, this, &OptionsScreen::onApplyBtnClick);
    attach(applyBtn);

    {
        const int screenWidth = EngineHandler::getScreenWidth();
        const int screenHeight = EngineHandler::getScreenHeight();

        char buff[10];
        for (const Resolution & res : kResolutions)
        {
            const bool isSelected = screenWidth == res.width && screenHeight == res.height;
            sprintf_s(buff, "%ix%i", res.width, res.height);
            const int index = resBtns_.size();
            Button * btn = new Button();
            btn->setText(buff);
            btn->setFont("robo_bold_15_fnt");
            btn->setRect(0, 0, 256, 64);
            btn->addCallback(EventType::MouseClicked, this, &OptionsScreen::onResolutionBtnClick);
            btn->setTextAlignment(Alignment::Center | Alignment::Middle);
            btn->setAlignment(Alignment::Left | Alignment::Top, 320, (index + 1) * 64);
            btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
            btn->setColour(isSelected ? Colour::Green : Colour::Red);
            attach(btn);

            resBtns_.push_back(btn);

            if (isSelected)
            {
                resIndex_ = index;
            }
        }
    }
}

OptionsScreen::~OptionsScreen()
{
}

void OptionsScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(nullptr);
}

void OptionsScreen::onVsyncBtnClick()
{
    isVSync_ = !isVSync_;
    if (vSyncBtn_)
    {
        vSyncBtn_->setText(isVSync_ ? kVSyncOn : kVSyncOff);
        vSyncBtn_->setColour(isVSync_ ? Colour::Green : Colour::Red);
    }
}

void OptionsScreen::onBorderlessBtnClick()
{
    isBorderless_ = !isBorderless_;
    if (borderlessBtn_)
    {
        borderlessBtn_->setText(isBorderless_ ? kWindowBorderOn : kWindowBorderOff);
        borderlessBtn_->setColour(isBorderless_ ? Colour::Green : Colour::Red);
    }
}

void OptionsScreen::onFullscreenBtnClick()
{
    isFullscreen_ = !isFullscreen_;
    if (fullscreenBtn_)
    {
        fullscreenBtn_->setText(isFullscreen_ ? kFullscreenOn : kFullscreenOff);
        fullscreenBtn_->setColour(isFullscreen_ ? Colour::Green : Colour::Red);
    }
}

void OptionsScreen::onApplyBtnClick()
{
    if (SaveData * saveData = EngineHandler::getSaveData())
    {
        saveData->setVSync(isVSync_);
        saveData->setBorderless(isBorderless_);
        saveData->setFullscreen(isFullscreen_);
        const Resolution & res = kResolutions[resIndex_];
        saveData->setResolution(res.width, res.height);
        saveData->serialize();
    }
    EngineHandler::restart();
}

void OptionsScreen::onResolutionBtnClick(Widget* sender)
{
    if (sender)
    {
        int index(0);
        for (Button * btn : resBtns_)
        {
            const bool isSelected = sender == btn;
            btn->setColour(isSelected ? Colour::Green : Colour::Red);
            if (isSelected)
            {
                resIndex_ = index;
            }
            ++index;
        }
    }
}
} // stren