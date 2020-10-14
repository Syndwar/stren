#include "map_editor/map_editor_system_panel.h"

#include "widgets/button.h"
#include "engine_handler.h"
#include "screens/screen_ids.h"
#include "screens/map_editor_screen.h"

namespace stren
{
MapEditorSystemPanel::MapEditorSystemPanel(const std::string & id)
    : Container(id)
    , m_isGridOn(true)
{
    Button * backBtn = new Button("backBtn");
    backBtn->setText("Exit");
    backBtn->setFont("robo_bold_15_fnt");
    backBtn->setRect(0, 0, 64, 64);
    backBtn->setAlignment(Alignment::LeftBottom, 0, 0);
    backBtn->setTextAlignment(Alignment::CenterMiddle);
    backBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    backBtn->addCallback(EventType::MouseClicked, this, &MapEditorSystemPanel::onBackBtnClick);
    backBtn->setColour(Colour::Red);
    attach(backBtn);

    Button * saveBtn = new Button("saveBtn");
    saveBtn->setText("Save");
    saveBtn->setFont("robo_bold_15_fnt");
    saveBtn->setRect(0, 0, 64, 64);
    saveBtn->setAlignment(Alignment::LeftBottom, 64, 0);
    saveBtn->setTextAlignment(Alignment::CenterMiddle);
    saveBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    saveBtn->addCallback(EventType::MouseClicked, this, &MapEditorSystemPanel::onSaveBtnClick);
    saveBtn->setColour(Colour::Red);
    attach(saveBtn);

    Button * loadBtn = new Button("loadBtn");
    loadBtn->setText("Load");
    loadBtn->setFont("robo_bold_15_fnt");
    loadBtn->setRect(0, 0, 64, 64);
    loadBtn->setAlignment(Alignment::LeftBottom, 128, 0);
    loadBtn->setTextAlignment(Alignment::CenterMiddle);
    loadBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    loadBtn->addCallback(EventType::MouseClicked, this, &MapEditorSystemPanel::onLoadBtnClick);
    loadBtn->setColour(Colour::Red);
    attach(loadBtn);

    Button * gridBtn = new Button("gridBtn");
    gridBtn->setText(m_isGridOn ? "Grid On" : "Grid Off");
    gridBtn->setFont("robo_bold_15_fnt");
    gridBtn->setRect(0, 0, 64, 64);
    gridBtn->setAlignment(Alignment::LeftBottom, 192, 0);
    gridBtn->setTextAlignment(Alignment::CenterMiddle);
    gridBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    gridBtn->addCallback(EventType::MouseClicked, this, &MapEditorSystemPanel::onGridBtnClick);
    gridBtn->setColour(Colour::Green);
    attach(gridBtn);
}

MapEditorSystemPanel::~MapEditorSystemPanel()
{
}

void MapEditorSystemPanel::onSaveBtnClick()
{
}

void MapEditorSystemPanel::onLoadBtnClick()
{
}

void MapEditorSystemPanel::onBackBtnClick()
{
    EngineHandler::switchScreen(nullptr, nullptr);
}

void MapEditorSystemPanel::onGridBtnClick(Widget * sender)
{
    if (!sender) return;

    m_isGridOn = !m_isGridOn;

    if (Button * btn = dynamic_cast<Button *>(sender))
    {
        btn->setText(m_isGridOn ? "Grid On" : "Grid Off");
    }
    if (Screen * currentScreen = EngineHandler::getCurrentScreen())
    {
        if (MapEditorScreen * screen = dynamic_cast<MapEditorScreen *>(currentScreen))
        {
            screen->enableGrid(m_isGridOn);
        }
    }
}
} // stren