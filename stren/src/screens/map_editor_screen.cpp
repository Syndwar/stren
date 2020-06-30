#include "screens/map_editor_screen.h"

#include "engine_handler.h"
#include "game/battlefield.h"
#include "widgets/area.h"
#include "widgets/button.h"
#include "widgets/image.h"
#include "widgets/primitive.h"
#include "lua_wrapper.h"
#include "screen_ids.h"

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
/// class MapData
///
class MapData
{
public:
    struct EntityData
    {
        enum class Type
        {
            Item = 0,
            Unit,
            Object
        };

        Type type;
        std::string id;
        std::string sprite;
    };
private:

    std::map<std::string, size_t> map_;
    std::vector<EntityData> data_;
public:
    ///
    /// Constructor
    ///
    MapData()
    {
        std::vector<std::string> sections = { "Items", "Units", "Objects" };

        for (size_t j = 0, jEnd = sections.size(); j < jEnd; ++j)
        {
            const std::string & sectionId = sections[j];
            lua::Table tbl(sectionId);
            for (size_t i = 1, iEnd = tbl.getSize(); i <= iEnd; ++i)
            {
                lua::Table dataTbl(tbl.get(i));
                const std::string id = dataTbl.get("id").getString();
                const std::string spriteId = dataTbl.get("sprite").getString();
                map_[id] = data_.size();
                data_.push_back(EntityData{static_cast<EntityData::Type>(j), id, spriteId });
            }
        }
    }
    ///
    /// @todo
    ///
    const EntityData & getData(const std::string & id) const
    {
        auto it = map_.find(id);
        if (it != map_.end())
        {
            if (it->second < data_.size())
            {
                return data_.at(it->second);
            }
        }
        static EntityData emptyData;
        return emptyData;
    }
    ///
    /// @todo
    ///
    const std::vector<EntityData> & getDataList() const
    {
        return data_;
    }

};

///
/// class MapEditorFiltersPanel
///
class MapEditorFiltersPanel : public Container
{
public:
    ///
    /// Constructor
    ///
    MapEditorFiltersPanel(const std::string & id)
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
    ///
    /// Destructor
    ///
    virtual ~MapEditorFiltersPanel()
    {
    }
private:
    ///
    /// @todo
    ///
    void onFilterBtnClick(Widget * sender)
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
};
///
/// class MapEditorItemsPanel
///
class MapEditorItemsPanel : public Container
{
private:
    MapData * mapData_;   ///< @todo
public:
    ///
    /// Constructor
    ///
    MapEditorItemsPanel(const std::string & id, MapData * mapData)
        : Container(id)
        , mapData_(mapData)
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

        const std::vector<MapData::EntityData> & dataList = mapData_->getDataList();
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
    ///
    /// Destructor
    ///
    virtual ~MapEditorItemsPanel()
    {
    }
private:
    ///
    /// @todo
    ///
    void onMapItemClicked(Widget * sender)
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
};
///
/// class MapEditorSystemPanel
///
class MapEditorSystemPanel : public Container
{
private:
    bool isGridOn_;
public:
    ///
    /// Constructor
    ///
    MapEditorSystemPanel(const std::string & id)
        : Container(id)
        , isGridOn_(true)
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
        gridBtn->setText(isGridOn_ ? "Grid On" : "Grid Off");
        gridBtn->setFont("robo_bold_15_fnt");
        gridBtn->setRect(0, 0, 64, 64);
        gridBtn->setAlignment(Alignment::LeftBottom, 192, 0);
        gridBtn->setTextAlignment(Alignment::CenterMiddle);
        gridBtn->setSprites("up_btn_spr", "down_btn_spr", "over_btn_spr");
        gridBtn->addCallback(EventType::MouseClicked, this, &MapEditorSystemPanel::onGridBtnClick);
        gridBtn->setColour(Colour::Green);
        attach(gridBtn);
    }
    ///
    /// Destructor
    ///
    virtual ~MapEditorSystemPanel()
    {
    }
private:
    ///
    /// @todo
    ///
    void onBackBtnClick()
    {
        EngineHandler::switchScreen(ScreenId::MainScreen);
    }
    ///
    /// @todo
    ///
    void onSaveBtnClick()
    {
    }
    ///
    /// @todo
    ///
    void onLoadBtnClick()
    {
    }
    ///
    /// @todo
    ///
    void onGridBtnClick(Widget * sender)
    {
        if (!sender) return;

        isGridOn_ = !isGridOn_;

        if (Button * btn = dynamic_cast<Button *>(sender))
        {
            btn->setText(isGridOn_ ? "Grid On" : "Grid Off");
        }
        if (Screen * currentScreen = EngineHandler::getCurrentScreen())
        {
            if (MapEditorScreen * screen = dynamic_cast<MapEditorScreen *>(currentScreen))
            {
                screen->enableGrid(isGridOn_);
            }
        }
    }
    ///
    /// @todo
    ///
};
///
/// class MapEditorScreen
///
MapEditorScreen::MapEditorScreen()
    : Screen("mapEditorScreen")
{
    mapData_ = new MapData();

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

    grid_ = new Primitive("gridLines");
    grid_->setColour(Colour::Green);
    std::vector<Point> gridPoints;
    createGrid(gridPoints);
    grid_->createLines(gridPoints);
    battlefield->attach(grid_);

    MapEditorSystemPanel * systemPanel = new MapEditorSystemPanel("systemPanel");
    attach(systemPanel);

    MapEditorFiltersPanel * filtersCnt = new MapEditorFiltersPanel("filtersPanel");
    attach(filtersCnt);

    MapEditorItemsPanel * itemsPanel = new MapEditorItemsPanel("itemsPanel", mapData_);
    attach(itemsPanel);

    Image * selectedItemImg = new Image("selectedItemImg");
    selectedItemImg->setRect(0, 0, 32, 32);
    attach(selectedItemImg);
}

MapEditorScreen::~MapEditorScreen()
{
    if (mapData_)
    {
        delete mapData_;
        mapData_ = nullptr;
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
    if (grid_)
    {
        grid_->view(value);
    }
}

void MapEditorScreen::selectItem(const std::string & id)
{
    EngineHandler::consoleLog(id);
    selectedItemId_ = id;

    if (Image * img = findWidget<Image>("selectedItemImg"))
    {
        const MapData::EntityData & data = mapData_->getData(id);
        img->setSprite(data.sprite);
    }
}
} // stren
