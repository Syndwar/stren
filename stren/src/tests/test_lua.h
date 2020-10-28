#ifndef STREN_TEST_LUA_H
#define STREN_TEST_LUA_H

#include "lua_wrapper.h"

#include "point.h"
#include "rect.h"
#include "utils.h"

using namespace lua;

namespace test
{
    int testFunction(lua_State * L)
    {
        Stack stack;
        stack.push("0.0.1");
        return 1;
    }
///
/// class LuaVirtualMachine
///
class LuaVirtualMachine
{
public:
    ///
    /// Constructor
    ///
    LuaVirtualMachine()
    {
        {
            Stack stack;
            int memoryUsage = stack.getAllocatedMemory();
            stack.collectGarbage();
            memoryUsage = stack.getAllocatedMemory();
        }
        {
            Stack stack;
            const int stackSize = stack.getSize();
            stren::assertMessage(0 == stackSize, "Error");
            stren::assertMessage(stack.isEmpty(), "Error");
            stack.checkEmptyOrDie();
            stack.checkSizeOrDie(0);
            stack.push(); // push nil
            stack.checkSizeOrDie(1);
            stack.pop(1);
            stack.checkEmptyOrDie();

            stack.push();
            stren::assertMessage(stack.get(-1).isNil(), "Error");

            stack.push(1); // push 2
            Value iValue = stack.get(-1);
            stren::assertMessage(iValue.isInt(), "Error");
            stren::assertMessage(iValue.getInt() == 1, "Error");

            stack.push(2.0f); // push 3
            Value fValue = stack.get(-1);
            stren::assertMessage(fValue.isNumber(), "Error");

            stack.push("test text"); // push 4
            Value charValue = stack.get(-1);
            stren::assertMessage(charValue.isString(), "Error");
            stren::assertMessage(charValue.getString() == "test text", "Error");

            stack.push(true); // push 5
            Value bValue = stack.get(-1);
            stren::assertMessage(bValue.isBool(), "Error");
            stren::assertMessage(bValue.getBool() == true, "Error");

            const std::string text = "test text";
            stack.push(text); // push 6
            Value strValue = stack.get(-1);
            stren::assertMessage(strValue.isString(), "Error");
            stren::assertMessage(strValue.getString() == text, "Error");

            const long longNumber = 15;
            stack.push(longNumber); // push 7
            Value lValue = stack.get(-1);
            stren::assertMessage(lValue.isInt(), "Error");
            stren::assertMessage(lValue.getInt() == longNumber, "Error");

            const double doubleNumber = 30.5;
            stack.push(doubleNumber); // push 8
            Value dValue = stack.get(-1);
            stren::assertMessage(dValue.isNumber(), "Error");
            stren::assertMessage(dValue.getDouble() == doubleNumber, "Error");

            const size_t sizeNumber = 45;
            stack.push(sizeNumber); // push 9
            Value sValue = stack.get(-1);
            stren::assertMessage(sValue.isInt(), "Error");
            stren::assertMessage(sValue.getInt() == sizeNumber, "Error");

            struct { int a = 60; } testStruct;
            void * pTestStruct = &testStruct;
            stack.push(pTestStruct); // push 10
            Value uValue = stack.get(-1);
            stren::assertMessage(uValue.isUserData(), "Error");
            stren::assertMessage(uValue.getUserData() == pTestStruct, "Error");

            stack.checkSizeOrDie(10);
            stack.pop(5);
            stack.checkSizeOrDie(5);
            stack.pop(5);
            stack.checkEmptyOrDie();
        }

        {
            Stack stack;
            Table tbl;
            tbl.create();
            stack.checkEmptyOrDie();
            stren::assertMessage(0 == tbl.getSize(), "Error");
            stren::assertMessage(tbl.isValid(), "Error");
            {
                Table tbl2(tbl);
                stren::assertMessage(tbl2.getRef() != tbl.getRef(), "Error");
            }
            {
                Table tbl3(LUA_NOREF);
                stren::assertMessage(!tbl3.isValid(), "Error");
                tbl3 = tbl;
                stren::assertMessage(tbl3.isValid(), "Error");
                stren::assertMessage(tbl3.getRef() != tbl.getRef(), "Error");
            }
            tbl.set(1, 33);
            stren::assertMessage(0 != tbl.getSize(), "Error");
            stren::assertMessage(tbl.get(1).isInt(), "Error");
            tbl.set("a", "test_string");
            stren::assertMessage(tbl.get("a").isString(), "Error");
            stren::assertMessage(tbl.get("b").isNil(), "Error");
            stren::assertMessage(tbl.hasKey("a"), "Error");
            stren::assertMessage(!tbl.hasKey("b"), "Error");

            std::vector<Value> keys;
            tbl.getKeys(keys);
            stren::assertMessage(2 == keys.size(), "Error");
            for (auto & key : keys)
            {
                if (key.isString())
                {
                    stren::assertMessage(key.getString() == "a", "Error");
                    stren::assertMessage(tbl.get(key).getString() == "test_string", "Error");
                }
                else if (key.isInt())
                {
                    stren::assertMessage(key.getInt() == 1, "Error");
                    stren::assertMessage(tbl.get(key).getInt() == 33, "Error");
                }
            }
        }
        {
            Table tbl;
            tbl.create();
            tbl.set(1, 33);
            tbl.set(2, 66);
            tbl.set(3, 99);
            tbl.set(4, 122);
            std::vector<Value> values;
            tbl.fill(values);
            stren::assertMessage(values.size() == 4, "Error");
            stren::assertMessage(values[0].getInt() == 33, "Error");
            stren::assertMessage(values[1].getInt() == 66, "Error");
            stren::assertMessage(values[2].getInt() == 99, "Error");
            stren::assertMessage(values[3].getInt() == 122, "Error");
        }
        {
            Table tbl;
            tbl.create();
            tbl.set("a", 33);
            tbl.set("b", "dooo");
            tbl.set("c", 99);
            tbl.set("d", "hi");
            std::map<Value, Value> values;
            tbl.fill(values);
            stren::assertMessage(values.size() == 4, "Error");
            stren::assertMessage(values["a"].getInt() == 33, "Error");
            stren::assertMessage(values["b"].getString() == "dooo", "Error");
            stren::assertMessage(values["c"].getInt() == 99, "Error");
            stren::assertMessage(values["d"].getString() == "hi", "Error");

            Table tbl2 = tbl.copy();
            stren::assertMessage(tbl2.get("a").getInt() == tbl.get("a").getInt(), "Error");
            stren::assertMessage(tbl2.get("b").getString() == tbl.get("b").getString(), "Error");
            stren::assertMessage(tbl2.get("c").getInt() == tbl.get("c").getInt(), "Error");
            stren::assertMessage(tbl2.get("d").getString() == tbl.get("d").getString(), "Error");

            stren::assertMessage(!tbl.isEmpty(), "Error");
        }
        {
            Table tbl;
            tbl.create();
            tbl.set(1, 33);
            tbl.set(2, 66);
            tbl.set(3, 99);
            tbl.set(4, 122);
            stren::Rect rect;
            tableToRect(tbl, rect);
            stren::assertMessage(rect.getX() == 33, "Error");
            stren::assertMessage(rect.getY() == 66, "Error");
            stren::assertMessage(rect.getWidth() == 99, "Error");
            stren::assertMessage(rect.getHeight() == 122, "Error");
        }
        {
            Table tbl;
            tbl.create();
            tbl.set(1, 33);
            tbl.set(2, 66);
            stren::Point point;
            tableToPoint(tbl, point);
            stren::assertMessage(point.getX() == 33, "Error");
            stren::assertMessage(point.getY() == 66, "Error");
        }

        testLuaAPI();

        Stack().destroy();
    }

private:
    void LuaVirtualMachine::testLuaAPI()
    {
        Stack stack;
        stack.loadScript("base/scripts/usersave.lua");

        Table tbl("UserSaveData");
        stren::assertMessage(tbl.isValid(), "Error");
        Table tbl2("UserSave");
        Function("UserSave.init").call({ tbl2 });
        tbl = Table("UserSaveData");
        Value userName = tbl.get("user_name");
        stren::assertMessage(userName.isString(), "Error");
        Value created = tbl.get("created");
        stren::assertMessage(created.isInt(), "Error");
        tbl.set("user_name", 3);
        stren::assertMessage(tbl.get("user_name").getInt() == 3, "Error");

        const luaL_reg engine_functions[] =
        {
            { "testFunc", testFunction },
            { NULL, NULL }
        };
        stack.loadLibs("Engine", engine_functions);
        const luaL_reg new_engine_functions[] =
        {
            { "testFunc2", testFunction },
            { NULL, NULL }
        };
        stack.loadLibs("Engine", new_engine_functions);
        {
            Function testFunc("Engine.testFunc");
            std::vector<Value> results(1);
            testFunc.call(Function::kEmptyParams, results);
            stren::assertMessage(results.size() == 1, "Error");
            stren::assertMessage(results[0].getString() == "0.0.1", "Error");
        }
        {
            Function testFunc("Engine.testFunc2");
            std::vector<Value> results(1);
            testFunc.call(Function::kEmptyParams, results);
            stren::assertMessage(results.size() == 1, "Error");
            stren::assertMessage(results[0].getString() == "0.0.1", "Error");
        }
    }
};

} // test

#endif // STREN_TEST_LUA_H
