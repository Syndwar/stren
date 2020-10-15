#include "screens/test_scroll_screen.h"

#include "engine_handler.h"
#include "widgets/area.h"
#include "widgets/button.h"
#include "widgets/image.h"
#include "widgets/scroll_container.h"

namespace
{
const int fieldWidth = 80;
const int fieldHeight = 50;
const int tileWidth = 128;
const int tileHeight = 64;
const std::string tileSprite = "test_tile_spr";
}

namespace stren
{

void addScrollContent(Screen * screen)
{
    if (screen)
    {
        if (ScrollContainer * sc = screen->findWidget<ScrollContainer>("scrollCnt"))
        {
            int contentWidth(0);
            int contentHeight(0);
            for (int i = 0; i < fieldWidth; ++i)
            {
                for (int j = 0; j < fieldHeight; ++j)
                {
                    const bool isOdd = 1 == j % 2;
                    const int offsetX = isOdd ? tileWidth / 2 : 0;
                    const int x = tileWidth * (fieldWidth - 1 - i) + offsetX;
                    const int y = tileHeight / 2 * j;

                    Image * img = new Image();
                    img->setRect(x, y, tileWidth, tileHeight);
                    img->setSprite(tileSprite);
                    sc->attach(img);
                    if (x + tileWidth > contentWidth)
                    {
                        contentWidth = x + tileWidth;
                    }
                    if (y + tileHeight)
                    {
                        contentHeight = y + tileHeight;
                    }
                }
            }
            sc->setContentRect(0, 0, contentWidth, contentHeight);
        }
    }
}

void getScrollContainerSize(int & w, int & h)
{
    w = fieldWidth * tileWidth + (fieldHeight - 1) * tileWidth / 2;
    h = tileHeight * (fieldHeight + 1) / 2;
}

TestScrollScreen::TestScrollScreen()
    : Screen("testScrollScreen")
{
    //    self : addWidgetsToScrollContainer();

    const int screenWidth = EngineHandler::getScreenWidth();
    const int screenHeight = EngineHandler::getScreenHeight();
    {
        ScrollContainer * scrollCnt = new ScrollContainer("scrollCnt");
        scrollCnt->setRect(0, 0, screenWidth, screenHeight);
        scrollCnt->setScrollSpeed(1000);
        attach(scrollCnt);

        Area * leftArea = new Area("scrollLeftArea");
        leftArea->setRect(0, 0, 20, 700);
        leftArea->setAlignment(Alignment::Left | Alignment::Middle, 0, 0);
        IAction * scrollLeftAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Left);
        leftArea->setAction(EventType::MouseMove, scrollLeftAction);
        attach(leftArea);

        Area * topArea = new Area("scrollUpArea");
        topArea->setRect(0, 0, 1000, 20);
        topArea->setAlignment(Alignment::Center | Alignment::Top, 0, 0);
        IAction * scrollUpAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Up);
        topArea->setAction(EventType::MouseMove, scrollUpAction);
        attach(topArea);

        Area * bottomArea = new Area("scrollDownArea");
        bottomArea->setAlignment(Alignment::Center | Alignment::Bottom, 0, 0);
        bottomArea->setRect(0, 0, 1000, 20);
        IAction * scrollDownAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Down);
        bottomArea->setAction(EventType::MouseMove, scrollDownAction);
        attach(bottomArea);

        Area * rightArea = new Area("scrollRightArea");
        rightArea->setRect(0, 0, 20, 700);
        rightArea->setAlignment(Alignment::Right | Alignment::Middle, 0, 0);
        IAction * scrollRightAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Right);
        rightArea->setAction(EventType::MouseMove, scrollRightAction);
        attach(rightArea);
    }
    {
        Button * btn = new Button("backBtn");
        btn->setText("Exit");
        btn->setFont("robo_bold_15_fnt");
        btn->setRect(0, 0, 64, 64);
        btn->setAlignment(Alignment::Right | Alignment::Bottom, 0, 0);
        btn->setTextAlignment(Alignment::Center | Alignment::Middle);
        btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
        btn->addCallback(EventType::MouseClicked, this, &TestScrollScreen::onBackBtnClick);
        btn->setColour(Colour::Red);
        attach(btn);
    }
    {
        Button * btn = new Button("jumpBtn");
        btn->setText("Jump");
        btn->setFont("robo_bold_15_fnt");
        btn->setRect(0, 0, 64, 64);
        btn->setAlignment(Alignment::Right | Alignment::Bottom, 0, -64);
        btn->setTextAlignment(Alignment::Center | Alignment::Middle);
        btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
        btn->setColour(Colour::Red);
        btn->addCallback(EventType::MouseClicked, this, &TestScrollScreen::onJumpBtnClick);
        attach(btn);
    }
    {
        Button * btn = new Button("scrollBtn");
        btn->setText("Scroll");
        btn->setFont("robo_bold_15_fnt");
        btn->setRect(0, 0, 64, 64);
        btn->setAlignment(Alignment::Right | Alignment::Bottom, 0, -128);
        btn->setTextAlignment(Alignment::Center | Alignment::Middle);
        btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
        btn->setColour(Colour::Red);
        btn->addCallback(EventType::MouseClicked, this, &TestScrollScreen::onScrollBtnClick);
        attach(btn);
    }

    addScrollContent(this);
}

TestScrollScreen::~TestScrollScreen()
{
}

void TestScrollScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(nullptr);
}

void TestScrollScreen::onJumpBtnClick()
{
    if (ScrollContainer * sc = findWidget<ScrollContainer>("scrollCnt"))
    {
        sc->jumpTo(1024, 768);
    }
}

void TestScrollScreen::onScrollBtnClick()
{
    if (ScrollContainer * sc = findWidget<ScrollContainer>("scrollCnt"))
    {
        if (!sc->isScrolling())
        {
            sc->scrollTo(0, 0);
        }
    }
}

} // stren
