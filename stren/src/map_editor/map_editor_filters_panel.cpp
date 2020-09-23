#include "map_editor/map_editor_filters_panel.h"

#include "widgets/button.h"

namespace stren
{
MapEditorFiltersPanel::MapEditorFiltersPanel(const std::string & id)
    : Container(id)
{
    setRect(0, 0, 256, 64);
    setAlignment(Alignment::CenterBottom, 0, 0);

    Button * itemsBtn = new Button("itemsBtn");
    itemsBtn->setText("Items");
    itemsBtn->setFont("robo_bold_15_fnt");
    itemsBtn->setRect(0, 0, 64, 64);
    itemsBtn->setTextAlignment(Alignment::CenterMiddle);
    itemsBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    itemsBtn->addCallback(EventType::MouseClicked, this, &MapEditorFiltersPanel::onFilterBtnClick);
    itemsBtn->setColour(Colour::Green);
    attach(itemsBtn);

    Button * unitsBtn = new Button("unitsBtn");
    unitsBtn->setText("Units");
    unitsBtn->setFont("robo_bold_15_fnt");
    unitsBtn->setRect(64, 0, 64, 64);
    unitsBtn->setTextAlignment(Alignment::CenterMiddle);
    unitsBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    unitsBtn->addCallback(EventType::MouseClicked, this, &MapEditorFiltersPanel::onFilterBtnClick);
    unitsBtn->setColour(Colour::Green);
    attach(unitsBtn);

    Button * terrainBtn = new Button("objectsBtn");
    terrainBtn->setText("Objects");
    terrainBtn->setFont("robo_bold_15_fnt");
    terrainBtn->setRect(128, 0, 64, 64);
    terrainBtn->setTextAlignment(Alignment::CenterMiddle);
    terrainBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    terrainBtn->addCallback(EventType::MouseClicked, this, &MapEditorFiltersPanel::onFilterBtnClick);
    terrainBtn->setColour(Colour::Green);
    attach(terrainBtn);

    Button * objectsBtn = new Button("terrainBtn");
    objectsBtn->setText("Terrain");
    objectsBtn->setFont("robo_bold_15_fnt");
    objectsBtn->setRect(196, 0, 64, 64);
    objectsBtn->setTextAlignment(Alignment::CenterMiddle);
    objectsBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
    objectsBtn->addCallback(EventType::MouseClicked, this, &MapEditorFiltersPanel::onFilterBtnClick);
    objectsBtn->setColour(Colour::Green);
    attach(objectsBtn);
}

MapEditorFiltersPanel::~MapEditorFiltersPanel()
{
}

void MapEditorFiltersPanel::onFilterBtnClick(Widget * sender)
{
    const std::string & senderId = sender->getId();
    // @todo Find a way to solve this problem without ids (using actions, maybe)
    Widget * parent = getParent();
    if (!parent) return;
    Container * cnt = dynamic_cast<Container *>(parent);
    if (!cnt) return;
    std::string sectionId;

    static std::string sectionPrefix = "itemsPanel.scrollCnt.";

    static std::vector<std::string> sections = {
        "unitsCnt",
        "itemsCnt",
        "objectsCnt",
        "terrainCnt"
    };

    static std::vector<std::string> buttons = {
        "unitsBtn",
        "itemsBtn",
        "objectsBtn",
        "terrainBtn"
    };

    int i = 0;
    for (const std::string & sectionId : sections)
    {
        bool isVisible(false);
        if (senderId == buttons[i])
        {
            isVisible = true;
        }
        const std::string sectionPath = sectionPrefix + sectionId;
        if (Widget * section = cnt->findWidget<Widget>(sectionPath))
        {
            section->view(isVisible);
        }
        ++i;
    }
}
} // stren