#include "map_editor/map_editor_items_panel.h"

#include "engine_handler.h"

#include "map_editor/map_data.h"

#include "widgets/area.h"
#include "widgets/button.h"
#include "widgets/scroll_container.h"
#include "screens/map_editor_screen.h"

namespace stren
{
MapEditorItemsPanel::MapEditorItemsPanel(const std::string & id, MapData * mapData)
    : Container(id)
    , m_mapData(mapData)
{
    const int screenWidth = EngineHandler::getScreenWidth();
    const int screenHeight = EngineHandler::getScreenHeight();

    ScrollContainer * scrollCnt = new ScrollContainer("scrollCnt");
    scrollCnt->setAlignment(Alignment::RightTop, 0, 32);
    scrollCnt->setRect(0, 0, 32, screenHeight - 64);
    scrollCnt->setScrollSpeed(500);
    attach(scrollCnt);

    Container * unitsCnt = new Container("unitsCnt");
    scrollCnt->attach(unitsCnt);

    Container * itemsCnt = new Container("itemsCnt");
    itemsCnt->view(false);
    scrollCnt->attach(itemsCnt);

    Container * objectsCnt = new Container("objectsCnt");
    objectsCnt->view(false);
    scrollCnt->attach(objectsCnt);

    Container * terrainCnt = new Container("terrainCnt");
    terrainCnt->view(false);
    scrollCnt->attach(terrainCnt);

    const std::vector<MapData::EntityData> & dataList = m_mapData->getFullData();
    int itemsCount = 0;
    int unitsCount = 0;
    int objectsCount = 0;
    for (auto & data : dataList)
    {
        Button * btn = new Button(data.id);
        btn->setSprites(data.sprite, data.sprite, data.sprite);
        btn->addCallback(EventType::MouseClicked, this, &MapEditorItemsPanel::onMapItemClicked);

        if (MapData::EntityData::Type::Item == data.type)
        {
            btn->setRect(0, itemsCount * 32, 32, 32);
            itemsCnt->attach(btn);
            ++itemsCount;
        }
        else if (MapData::EntityData::Type::Unit == data.type)
        {
            btn->setRect(0, unitsCount * 32, 32, 32);
            unitsCnt->attach(btn);
            ++unitsCount;
        }
        else if (MapData::EntityData::Type::Object == data.type)
        {
            btn->setRect(0, objectsCount * 32, 32, 32);
            objectsCnt->attach(btn);
            ++objectsCount;
        }
    }
    int maxRow = itemsCount;
    if (unitsCount > maxRow)
    {
        maxRow = unitsCount;
    }
    if (objectsCount > maxRow)
    {
        maxRow = objectsCount;
    }

    scrollCnt->setContentRect(0, 0, 32, maxRow * 32);

    Area * scrollUpArea = new Area("scrollUpArea");
    scrollUpArea->setRect(0, 0, 32, 32);
    scrollUpArea->setAlignment(Alignment::RightTop, 0, 0);
    IAction * upAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Up);
    scrollUpArea->setAction(EventType::MouseMove, upAction);
    attach(scrollUpArea);

    Area * scrollDownArea = new Area("scrollDownArea");
    scrollDownArea->setRect(0, 0, 32, 32);
    scrollDownArea->setAlignment(Alignment::RightBottom, 0, 0);
    IAction * downAction = scrollCnt->createAction(ScrollContainer::ScrollDirection::Down);
    scrollDownArea->setAction(EventType::MouseMove, downAction);
    attach(scrollDownArea);
}

MapEditorItemsPanel::~MapEditorItemsPanel()
{
}

void MapEditorItemsPanel::onMapItemClicked(Widget * sender)
{
    if (Screen * screen = EngineHandler::getCurrentScreen())
    {
        if (MapEditorScreen * editor = dynamic_cast<MapEditorScreen *>(screen))
        {
            const std::string & id = sender->getId();
            editor->selectItem(id);
        }
    }
}
} // stren