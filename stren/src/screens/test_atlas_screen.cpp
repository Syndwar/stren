#include "test_atlas_screen.h"

#include "engine_handler.h"
#include "widgets/button.h"
#include "widgets/image.h"
#include "lua_wrapper.h"
#include "utils.h"
#include "screen_ids.h"

namespace stren
{
TestAtlasScreen::TestAtlasScreen()
    : Screen("testAtlasScreen")
{
    lua::Table sprites("Sprites");
    for (size_t i = 1, iEnd = sprites.getSize(); i <= iEnd; ++i)
    {
        lua::Table sprite(sprites.get(i));
        const std::string textureId = sprite.get("texture").getString();
        if (textureId == "atlas_1_tex")
        {
            Image * img = new Image();
            const std::string id = sprite.get("id").getString();
            img->setSprite(id);
            lua::Table rect(sprite.get("rect"));
            Rect spriteRect;
            tableToRect(rect, spriteRect);
            img->setRect(spriteRect);
            attach(img);
        }
    }

    Button * btn = new Button("backBtn");
    btn->setText("Main Screen");
    btn->setFont("robo_bold_15_fnt");
    btn->setRect(0, 0, 256, 64);
    btn->setAlignment(Alignment::Right | Alignment::Top, -64, 64);
    btn->setTextAlignment(Alignment::Center | Alignment::Middle);
    btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    btn->addCallback(EventType::MouseClicked, this, &TestAtlasScreen::onBackBtnClick);
    btn->setColour(Colour::Red);
    attach(btn);
}

TestAtlasScreen::~TestAtlasScreen()
{
}

void TestAtlasScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(ScreenId::MainScreen);
}
} // stren