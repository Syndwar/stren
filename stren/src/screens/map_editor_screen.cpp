#include "screens/map_editor_screen.h"

#include "engine_handler.h"

#include "game/battlefield.h"

#include "map_editor/map_data.h"
#include "map_editor/map_editor_system_panel.h"
#include "map_editor/map_editor_items_panel.h"
#include "map_editor/map_editor_filters_panel.h"

#include "widgets/primitive.h"
#include "widgets/image.h"

#include "engine/event.h"

namespace
{
struct Map
{
    stren::Point size = { 80, 50 };
    stren::Point cellSize = { 32, 32 };
} kMap;
}

namespace stren
{
///
/// class MapEditorScreen
///
MapEditorScreen::MapEditorScreen()
    : Screen("mapEditorScreen")
{
    m_mapData = new MapData();

    const int screenWidth = EngineHandler::getScreenWidth();
    const int screenHeight = EngineHandler::getScreenHeight();

    const int mapWidth = kMap.size.getX() * kMap.cellSize.getX();
    const int mapHeight = kMap.size.getY() * kMap.cellSize.getY();

    Battlefield * battlefield = new Battlefield("battlefield");
    battlefield->setRect(0, 0, screenWidth - 64, screenHeight - 96);
    battlefield->setScrollSpeed(500);
    battlefield->setContentRect(0, 0, mapWidth, mapHeight);
    battlefield->addCallback(EventType::MouseClicked, this, &MapEditorScreen::onBattleFieldClicked);
    attach(battlefield);

    battlefield->moveBy(32, 32);

    m_grid = new Primitive("gridLines");
    m_grid->setColour(Colour::Green);
    std::vector<Point> gridPoints;
    createGrid(gridPoints);
    m_grid->createLines(gridPoints);
    battlefield->attach(m_grid);

    MapEditorSystemPanel * systemPanel = new MapEditorSystemPanel("systemPanel");
    attach(systemPanel);

    MapEditorFiltersPanel * filtersCnt = new MapEditorFiltersPanel("filtersPanel");
    attach(filtersCnt);

    MapEditorItemsPanel * itemsPanel = new MapEditorItemsPanel("itemsPanel", m_mapData);
    attach(itemsPanel);

    Image * selectedItemImg = new Image("selectedItemImg");
    selectedItemImg->setRect(0, 0, 32, 32);
    attach(selectedItemImg);
}

MapEditorScreen::~MapEditorScreen()
{
    if (m_mapData)
    {
        delete m_mapData;
        m_mapData = nullptr;
    }
}

void MapEditorScreen::createGrid(std::vector<Point> & points)
{
    points.clear();

    const int cellsInRow = kMap.size.getX();
    const int cellsInColumn = kMap.size.getY();
    const int cellwidth = kMap.cellSize.getX();
    const int cellheight = kMap.cellSize.getY();
    const int mapWidth = cellsInRow * cellwidth;
    const int mapHeight = cellsInColumn * cellheight;

    const int rows = cellsInColumn / cellheight;
    const int columns = cellsInRow / cellwidth;

    {
        int row = 0;
        int w = 0;
        bool down = true;
        while (w <= mapWidth)
        {
            if (down)
            {
                points.push_back(Point(w, 0));
                points.push_back(Point(w, mapHeight));
            }
            else
            {
                points.push_back(Point(w, mapHeight));
                points.push_back(Point(w, 0));
            }
            ++row;
            w = row * cellwidth;
            down = !down;
        }
    }
    {
        int column = 0;
        int h = 0;
        bool left = false;
        while (h <= mapHeight)
        {
            if (left)
            {
                points.push_back(Point(0, h));
                points.push_back(Point(mapWidth, h));
            }
            else
            {
                points.push_back(Point(mapWidth, h));
                points.push_back(Point(0, h));
            }
            ++column;
            h = column * cellheight;
            left = !left;
        }
    }
}

void MapEditorScreen::onBattleFieldClicked()
{
    char buff[20];
    const Point pos = EngineHandler::getMousePos();
    sprintf_s(buff, "%i, %i", pos.getX(), pos.getY());
    EngineHandler::consoleLog(buff);
    if (Battlefield * battlefield = findWidget<Battlefield>("battlefield"))
    {
        const Point fieldPos = battlefield->screenToScrollPos(pos.getX(), pos.getY());
        sprintf_s(buff, "%i, %i", fieldPos.getX(), fieldPos.getY());
        EngineHandler::consoleLog(buff);
        /// @todo create cell
        //if (!selectedItemId_.empty())
        //{
        //    const MapData::EntityData & data = mapData_->getData(selectedItemId_);
        //    Image * img = new Image();
        //    img->setSprite(data.sprite);
        //    img->setRect(fieldPos.getX(), fieldPos.getY(), 32, 32);
        //    battlefield->attach(img);
        //}
    }
}

void MapEditorScreen::enableGrid(const bool value)
{
    if (m_grid)
    {
        m_grid->view(value);
    }
}

void MapEditorScreen::selectItem(const std::string & id)
{
    EngineHandler::consoleLog(id);
    m_selectedItemId = id;

    if (Image * img = findWidget<Image>("selectedItemImg"))
    {
        const MapData::EntityData & data = m_mapData->getEntityData(id);
        img->setSprite(data.sprite);
    }
}
} // stren
