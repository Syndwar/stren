#include "test_widgets_screen.h"

#include "engine_handler.h"
#include "widgets/area.h"
#include "widgets/button.h"
#include "widgets/dialog.h"
#include "widgets/image.h"
#include "widgets/progressbar.h"
#include "widgets/scroll_container.h"
#include "widgets/label.h"
#include "screen_ids.h"

namespace stren
{

//struct Desc
//{
//    std::string id;
//    std::string type;
//    std::string text;
//    std::string font;
//    std::string sprites[4];
//    Rect rect;
//    Colour colour;
//    int textAlign;
//    int align;
//};
//
//Desc desc = {
//    "testBtn",
//    "Button",
//    "Test Screen",
//    "robo_bold_15_fnt",
//    {"up_btn_spr", "down_btn_spr", "over_btn_spr", ""},
//    {0, 0, 256, 64},
//    Colour::Green,
//    Alignment::CenterMiddle,
//    0
//};

///
/// class TestDialog
///
class TestDialog : public Dialog
{
public:
    ///
    /// Constructor
    ///
    TestDialog(const std::string & id) : Dialog(id)
    {
        Transform openTransform;
        openTransform.add(0, 100, 1000);
        openTransform.add(100, 255, 1000);
        attachTransform(EventType::WidgetOpening, openTransform);
        Transform closeTransform;
        closeTransform.add(255, 0, 3000);
        attachTransform(EventType::WidgetClosing, closeTransform);

        setRect(0, 0, 400, 400);
        setAlignment(Alignment::Center | Alignment::Middle, 0, 0);

        Image * backImg = new Image();
        backImg->setRect(0, 0, 400, 400);
        backImg->setSprite("up_btn_spr");
        attach(backImg);

        Label * lbl = new Label();
        lbl->setRect(100, 180, 200, 40);
        lbl->setText("Hello");
        lbl->setFont("robo_bold_24_fnt");
        lbl->setColour(Colour::Green);
        lbl->setTextAlignment(Alignment::Center | Alignment::Middle);
        attach(lbl);
    }
    ///
    /// Destructor
    ///
    virtual ~TestDialog()
    {
    }
};

TestWidgetsScreen::TestWidgetsScreen()
    : Screen("testWidgetsScreen")
{
    Button * backBtn = new Button("backBtn");
    backBtn->setText("Main Screen");
    backBtn->setFont("robo_bold_15_fnt");
    backBtn->setRect(0, 0, 256, 64);
    backBtn->setTextAlignment(Alignment::Center | Alignment::Middle);
    backBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    backBtn->addCallback(EventType::MouseClicked, this, &TestWidgetsScreen::onBackBtnClick);
    backBtn->setColour(Colour::Red);
    attach(backBtn);

    Image * img = new Image();
    img->setRect(0, 0, 100, 100);
    img->setSprite("round_btn_spr");
    img->setAlignment(Alignment::Right | Alignment::Top, 0, 0);
    img->setAngle(0);
    img->setFlip(true, true);
    attach(img);

    Label * exitLbl = new Label("exitLbl");
    exitLbl->setRect(100, 200, 100, 100);
    exitLbl->setText("exit_lbl");
    exitLbl->setFont("robo_bold_24_fnt");
    exitLbl->setColour(Colour::Green);
    attach(exitLbl);

    Button * lockBtn = new Button("lockBtn");
    lockBtn->setRect(400, 300, 256, 64);
    lockBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    lockBtn->addCallback(EventType::MouseClicked, this, &TestWidgetsScreen::onLockBtnClick);
    attach(lockBtn);

    Button * windBtn = new Button("windBtn");
    windBtn->setText("Wind Progressbar");
    windBtn->setFont("robo_bold_15_fnt");
    windBtn->setRect(656, 428, 256, 64);
    windBtn->setTextAlignment(Alignment::Center | Alignment::Middle);
    windBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    windBtn->addCallback(EventType::MouseClicked, this, &TestWidgetsScreen::onWindBtnClicked);
    windBtn->setColour(Colour::Yellow);
    attach(windBtn);

    Button * moveCntBtn = new Button("moveCnt");
    moveCntBtn->setText("Move Container");
    moveCntBtn->setFont("robo_bold_15_fnt");
    moveCntBtn->setRect(0, 428, 256, 64);
    moveCntBtn->setTextAlignment(Alignment::Center | Alignment::Middle);
    moveCntBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    moveCntBtn->addCallback(EventType::MouseClicked, this, &TestWidgetsScreen::onMoveCntBtnClick);
    moveCntBtn->setColour(Colour::White);
    attach(moveCntBtn);

    ProgressBar * progressbar1 = new ProgressBar("pb1");
    progressbar1->setRect(656, 620, 100, 20);
    progressbar1->setSprite("progressbar_spr");
    progressbar1->setCurrentValue(0);
    progressbar1->setMaxValue(100);
    progressbar1->setFillSpeed(100);
    progressbar1->setVertical(false);
    attach(progressbar1);

    ProgressBar * progressbar2 = new ProgressBar("pb2");
    progressbar2->setRect(626, 620, 20, 100);
    progressbar2->setSprite("progressbar_spr");
    progressbar2->setCurrentValue(100);
    progressbar2->setMaxValue(100);
    progressbar2->setFillSpeed(100);
    progressbar2->setVertical(true);
    attach(progressbar2);
        
    Container * container = new Container("widgetCnt");
    container->setRect(0, 0, 0, 0);
    attach(container);

    Label * cntLbl = new Label("cntLbl");
    cntLbl->setRect(0, 328, 100, 100);
    cntLbl->setText("Label in Container");
    cntLbl->setColour(Colour::White);
    cntLbl->setFont("robo_bold_24_fnt");
    cntLbl->setOrder(999);
    container->attach(cntLbl);

    Button * cntBtn = new Button("cntBtn");
    cntBtn->setText("Button in Container");
    cntBtn->setFont("robo_bold_15_fnt");
    cntBtn->setRect(100, 428, 256, 64);
    cntBtn->setTextAlignment(Alignment::Center | Alignment::Middle);
    cntBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    cntBtn->setColour(Colour::White);
    cntBtn->addCallback(EventType::MouseClicked, this, &TestWidgetsScreen::onButtonInContainerClick);
    container->attach(cntBtn);

    ScrollContainer * scrollCnt = new ScrollContainer("scrollCnt");
    scrollCnt->setAlignment(Alignment::Right | Alignment::Top, -160, 60);
    scrollCnt->setRect(0, 0, 100, 100);
    scrollCnt->setScrollSpeed(500);
    scrollCnt->setContentRect(0, 0, 100, 200);
    attach(scrollCnt);

    Image * img1 = new Image();
    img1->setRect(0, 0, 100, 100);
    img1->setSprite("round_btn_spr");
    scrollCnt->attach(img1);

    Image * img2 = new Image();
    img2->setRect(0, 100, 100, 100);
    img2->setSprite("round_btn_spr");
    scrollCnt->attach(img2);

    Area * scrollUpArea = new Area("scrollUpArea");
    scrollUpArea->setRect(0, 0, 20, 20);
    scrollUpArea->setAlignment(Alignment::Right | Alignment::Top, -100, 0);
    IAction * upAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Up);
    scrollUpArea->setAction(EventType::MouseMove, upAction);
    attach(scrollUpArea);

    Area * scrollDownArea = new Area("scrollDownArea");
    scrollDownArea->setRect(0, 0, 20, 20);
    scrollDownArea->setAlignment(Alignment::Right | Alignment::Top, -100, 20);
    IAction * downAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Down);
    scrollDownArea->setAction(EventType::MouseMove, downAction);
    attach(scrollDownArea);

    dialog_ = new TestDialog("testWidgetsDialog");
    attach(dialog_);
}

TestWidgetsScreen::~TestWidgetsScreen()
{
}

void TestWidgetsScreen::onBackBtnClick()
{
    EngineHandler::switchScreen(ScreenId::MainScreen);
}

void TestWidgetsScreen::onLockBtnClick()
{
    if (Widget * w = findWidget<Widget>("exitLbl"))
    {
        w->view(!w->isOpened());
    }
}

void TestWidgetsScreen::onWindBtnClicked()
{
    int toValue = 100;
    if (ProgressBar * pb = findWidget<ProgressBar>("pb1"))
    {
        const int currentValue = pb->getCurrentValue();
        if (currentValue == 100)
        {
            toValue = 0;
            pb->windTo(toValue);
        }
        else if (currentValue == 0)
        {
            toValue = 100;
            pb->windTo(toValue);
        }
    }

    if (ProgressBar * pb = findWidget<ProgressBar>("pb2"))
    {
        const int currentValue = pb->getCurrentValue();
        if (currentValue == 100)
        {
            toValue = 0;
            pb->windTo(toValue);
        }
        else if (currentValue == 0)
        {
            toValue = 100;
            pb->windTo(toValue);
        }
    }
}

void TestWidgetsScreen::onMoveCntBtnClick()
{
    if (Widget * w = findWidget<Widget>("widgetCnt"))
    {
        w->moveTo(100, 0);
    }
}

void TestWidgetsScreen::onButtonInContainerClick()
{
    if (dialog_)
    {
        dialog_->view(!dialog_->isOpened());
    }
}

} // stren
