#include "system_tools.h"

#include "console.h"
#include "event.h"
#include "engine_handler.h"

#include "widgets/label.h"
#include "widgets/screen.h"

#include "system/debug_panel.h"
#include "system/widget_tree.h"

namespace stren
{
SystemTools::SystemTools()
    : Container("systemTools")
    , m_isReady(false)
{
}

SystemTools::~SystemTools()
{
}

void SystemTools::initialize()
{
    Console * console = new Console("console");
    attach(console);

    DebugPanel * debugPanel = new DebugPanel("debugPanel");
    debugPanel->setOrder(1000);
    attach(debugPanel);

    WidgetTree * widgetsTree = new WidgetTree("widgetTree");
    attach(widgetsTree);
    m_isReady = true;
}


void SystemTools::release()
{
    detachAll();
    m_isReady = false;
}

void SystemTools::log(const std::string & message)
{
    if (!m_isReady) return;

    if (Console * console = findWidget<Console>("console"))
    {
        console->log(message);
    }
}

void SystemTools::processEvent(const Event & event, bool & isEventCaptured)
{
    if (!isEventCaptured)
    {
        if (EventType::KeyUp == event.type)
        {
            if ("F1" == event.key)
            {
                if (Widget * debugPanel = findWidget<Widget>("debugPanel"))
                {
                    debugPanel->view(!debugPanel->isOpened());
                }
                isEventCaptured = true;
            }
            else if ("F2" == event.key)
            {
                if (Screen * currentScreen = EngineHandler::getCurrentScreen())
                {
                    currentScreen->setDebugView(!currentScreen->isDebugView());
                }
                isEventCaptured = true;
            }
            else if ("F3" == event.key)
            {
                if (Widget * widgetsTree = findWidget<Widget>("widgetTree"))
                {
                    widgetsTree->view(!widgetsTree->isOpened());
                }
                isEventCaptured = true;
            }
            else if ("`" == event.key)
            {
                if (Widget * console = findWidget<Widget>("console"))
                {
                    console->view(!console->isOpened());
                }
                isEventCaptured = true;
            }
        }
    }

    Container::processEvent(event, isEventCaptured);
}

} // stren
