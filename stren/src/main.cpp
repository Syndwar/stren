/// \mainpage StrEn - a strategy engine based on SDL with Lua scripts".
///
///  \section code_style Code style info:
///  AnyClassName
///  
///  AnyClassName.anyClassMemeber_
///  
///  AnyClassName::anyMethod
///  
///  bool AnyClassName::isAnyBoolValue, hasAnyBoolValue
///  
///  void AnyClassName::getAnyValue
///  
///  void AnyClassName::setAnyValue
///  
///  anyFunction
///  
///  anyVariable
///  
///  any_namespace
///  
///  kAnyGlobalConstant
/// 

#include "SDL.h"

#include "engine_handler.h"

#ifdef STREN_UNIT_TEST
#include "test_unit.h"
#endif

#ifdef WIN32
#include "windows.h"
#endif

bool createEngine()
{
    EngineHandler::destroy();
    bool created = EngineHandler::create();
    if (created)
    {
        if (EngineHandler::init())
        {
            EngineHandler::createGame();
        }
        else
        {
            EngineHandler::stop();
            created = false;
        }
    }
    return created;
}

int main(int argc, char * args[]) 
{
    try
    {
#ifdef STREN_UNIT_TEST
        test::run();
#endif
        bool hasEngine = createEngine();
        while (hasEngine)
        {
            if (EngineHandler::isRunning())
            {
                EngineHandler::process();
            }
            else if (EngineHandler::isRestarting())
            {
                hasEngine = createEngine();
            }
            else
            {
                hasEngine = false;
            }
        }
        EngineHandler::destroy();
    }
    catch (std::exception & e)
    {
        MessageBox(nullptr, e.what(), "Assert crush", MB_OK | MB_ICONERROR);
        EngineHandler::destroy();
    }

    return 0;
}