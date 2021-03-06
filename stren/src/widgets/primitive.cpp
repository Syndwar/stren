#include "primitive.h"

#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "render/primitive_figures.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Primitive::Primitive(const std::string & id)
    : Widget(id)
    , m_figure(nullptr)
{
}

Primitive::~Primitive()
{
    if (m_figure)
    {
        delete m_figure;
        m_figure = nullptr;
    }
}

void Primitive::createPoint(const Point & point)
{
    m_figure = new PrimitivePoint(point);
}

void Primitive::createPoints(const std::vector<Point> & points)
{
    m_figure = new PrimitivePoints(points);
}

void Primitive::createRect(const Rect & rect, const bool fill)
{
    m_figure = new PrimitiveRect(rect, fill);
}

void Primitive::createRects(const std::vector<Rect> & rects, const bool fill)
{
    m_figure = new PrimitiveRects(rects, fill);
}

void Primitive::createLines(const std::vector<Point> & points)
{
    m_figure = new PrimitiveLines(points);
}

void Primitive::createCircle(const int x, const int y, const int radius)
{
    m_figure = new PrimitiveCircle(x, y, radius);
}

void Primitive::doRender()
{
    if (m_figure)
    {
        m_figure->render(m_colour);
    }
}

void Primitive::moveTo(const int x, const int y)
{
    if (m_figure)
    {
        m_figure->moveTo(x, y);
    }
}

void Primitive::moveBy(const int dx, const int dy)
{
    if (m_figure)
    {
        m_figure->moveBy(dx, dy);
    }
}

void Primitive::setRect(const int x, const int y, const int w, const int h)
{
    if (m_figure)
    {
        m_figure->moveTo(x, y);
        m_figure->resize(w, h);
    }
}

void Primitive::reset(const std::vector<Rect> & rects, const bool fill)
{
    if (m_figure)
    {
        m_figure->reset(rects, fill);
    }
}

namespace lua_primitive
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new Primitive(id));
    stack.push(handler);
    return 1;
}

int setColour(lua_State *L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        const std::string colorStr = stack.get(2).getString();
        primitive->setColour(colorStr);
    }
    stack.clear();
    return 0;
}

int createCircle(lua_State * L)
{
    lua::Stack stack(4);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        const int r = stack.get(4).getInt();
        primitive->createCircle(x, y, r);
    }
    return 0;
}

int createPoint(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        primitive->createPoint(Point(x, y));
    }
    return 0;
}

int createRect(lua_State * L)
{
    lua::Stack stack(6);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        const int w = stack.get(4).getInt();
        const int h = stack.get(5).getInt();
        const bool fill = stack.get(6).getBool();
        primitive->createRect(Rect(x, y, w, h), fill);
    }
    return 0;
}

int creatLines(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        lua::Table tbl(stack.get(2));
        std::vector<Point> points;
        lua::tableToPointsVector(tbl, points);
        primitive->createLines(points);
    }
    return 0;
}

int createPoints(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        lua::Table tbl(stack.get(2));
        std::vector<Point> points;
        lua::tableToPointsVector(tbl, points);
        primitive->createPoints(points);
    }
    return 0;
}

int createRects(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        lua::Table tbl(stack.get(2));
        const bool fill = stack.get(3).getBool();
        std::vector<Rect> rects;
        lua::tableToRectsVector(tbl, rects);
        primitive->createRects(rects, fill);
    }
    return 0;
}

int reset(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Primitive * primitive = EngineHandler::getMemoryObj<Primitive *>(tbl);
    if (primitive)
    {
        lua::Table tbl(stack.get(2));
        const bool fill = stack.get(3).getBool();
        std::vector<Rect> rects;
        lua::tableToRectsVector(tbl, rects);
        primitive->reset(rects, fill);
    }
    return 0;
}
} // primitive_bind

void Primitive::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_primitive::create },
        { "setColour", lua_primitive::setColour },
        { "createCircle", lua_primitive::createCircle },
        { "createPoint", lua_primitive::createPoint },
        { "createRect", lua_primitive::createRect },
        { "createLines", lua_primitive::creatLines },
        { "createPoints", lua_primitive::createPoints },
        { "createRects", lua_primitive::createRects },
        { "reset", lua_primitive::reset },
        { NULL, NULL }
    };
    stack.loadLibs("Primitive", functions);
}
} // stren
