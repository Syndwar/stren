#include "test_font_screen.h"

#include "engine_handler.h"
#include "widgets/button.h"
#include "itexture.h"
#include "sprite.h"
#include "lua_wrapper.h"
#include "screen_ids.h"

namespace stren
{
TestFontScreen::TestFontScreen()
    : Screen("testFontScreen")
    , index_(0)
{
    Button * btn = new Button("backBtn");
    btn->setText("Exit");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setAlignment(Alignment::Right | Alignment::Bottom, 0, 0);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestFontScreen::onBackBtnClick);
    attach(btn);

    btn = new Button("changeFontBtn");
    btn->setText("Show Next Font");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setAlignment(Alignment::Right | Alignment::Bottom, 0, -70);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestFontScreen::onChangeFontBtnClick);
    attach(btn);
}

TestFontScreen::~TestFontScreen()
{
}

void TestFontScreen::doRender()
{
    Screen::doRender();

    if (!fontId_.empty())
    {
        if (ITexture * texture = EngineHandler::getTexture(fontId_))
        {
            static Rect rect;
            static Colour colour(Colour::White);
            rect.setSize(texture->getWidth(), texture->getHeight());
            texture->render(rect, rect, 0, Sprite::Flip::None, Point::getEmpty(), colour);
        }
    }
}

void TestFontScreen::setFont(const std::string & fontId)
{
    fontId_ = fontId;
}

void TestFontScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(nullptr, nullptr);
}

void TestFontScreen::onChangeFontBtnClick()
{
    ++index_;
    lua::Table fontsTbl("Fonts");
    int fontsCount = fontsTbl.getSize();
    if (index_ > fontsCount)
    {
        index_ = 1;
    }

    lua::Table fontTbl(fontsTbl.get(index_));
    const std::string fontId = fontTbl.get("id").getString();
    setFont(fontId);
}

} // stren