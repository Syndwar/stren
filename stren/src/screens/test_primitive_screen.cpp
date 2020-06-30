#include "screens/test_primitive_screen.h"

#include "widgets/button.h"
#include "widgets/primitive.h"
#include "engine_handler.h"
#include "screen_ids.h"

namespace stren
{
TestPrimitiveScreen::TestPrimitiveScreen()
    : Screen("testPrimitiveScreen")
{
    {
        Button * btn = new Button("backBtn");
        btn->setText("Exit");
        btn->setFont("robo_bold_15_fnt");
        btn->setRect(0, 0, 256, 64);
        btn->setTextAlignment(Alignment::Center | Alignment::Middle);
        btn->setAlignment(Alignment::Right | Alignment::Top, 0, 0);
        btn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
        btn->addCallback(EventType::MouseClicked, this, &TestPrimitiveScreen::onBackBtnClick);
        attach(btn);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::White);
        primitive->createCircle(630, 130, 100);
        attach(primitive);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::Green);
        const std::vector<Point> points = { { 0, 0 },{ 1024,768 } };
        primitive->createLines(points);
        attach(primitive);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::Red);
        const std::vector<Point> lines = { { 0, 0 },{ 200, 500 },{ 1024, 768 } };
        primitive->createLines(lines);
        attach(primitive);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::Yellow);
        const Point point(630, 130);
        primitive->createPoint(point);
        attach(primitive);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::Red);
        primitive->createRect(Rect(470, 70, 60, 60), false);
        attach(primitive);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::Green);
        primitive->createRect(Rect(400, 70, 60, 60), true);
        attach(primitive);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::Green);
        const std::vector<Point> points = { { 500, 101 },{ 500, 102 },{ 500, 103 } };
        primitive->createPoints(points);
        attach(primitive);
    }
    {
        Primitive * primitive = new Primitive();
        primitive->setColour(Colour::Yellow);
        const std::vector<Rect> rects = { { 120, 700, 40, 40 },{ 100, 650, 80, 80 } };
        primitive->createRects(rects, true);
        attach(primitive);
    }
}

TestPrimitiveScreen::~TestPrimitiveScreen()
{
}

void TestPrimitiveScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(ScreenId::MainScreen);
}
} // stren