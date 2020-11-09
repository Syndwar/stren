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
///
/// class ImageAction
///
class SystemToolsAction : public IAction
{
private:
    SystemTools *  m_container;     ///< container who created the action
public:
    ///
    /// Constructor
    ///
    SystemToolsAction(SystemTools * container) : IAction(), m_container(container) {}
    ///
    /// Destructor
    ///
    virtual ~SystemToolsAction() {}
    ///
    /// Start action
    ///
    virtual bool exec() override { return false; }
    ///
    /// Start action
    ///
    virtual bool exec(const Event & event) override
    {
        if (m_container)
        {
            if ("F1" == event.key)
            {
                if (Widget * debugPanel = m_container->findWidget<Widget>("debugPanel"))
                {
                    debugPanel->view(!debugPanel->isOpened());
                }
                return true;
            }
            else if ("F2" == event.key)
            {
                if (Screen * currentScreen = EngineHandler::getCurrentScreen())
                {
                    currentScreen->setDebugView(!currentScreen->isDebugView());
                }
                return true;
            }
            else if ("F3" == event.key)
            {
                if (Widget * widgetsTree = m_container->findWidget<Widget>("widgetTree"))
                {
                    widgetsTree->view(!widgetsTree->isOpened());
                }
                return true;
            }
            else if ("`" == event.key)
            {
                if (Widget * console = m_container->findWidget<Widget>("console"))
                {
                    console->view(!console->isOpened());
                }
                return true;
            }
        }
        return false;
    }
};
///
/// class SystemTools
///
SystemTools::SystemTools()
    : Container("systemTools")
    , m_isReady(false)
    , m_actionKey(0)
{
}

SystemTools::~SystemTools()
{
}

void SystemTools::initialize()
{
    IAction * action = new SystemToolsAction(this);
    m_actionKey = EngineHandler::addKeyboardAction(EventType::KeyUp, "", action);

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
    EngineHandler::removeKeyboardAction(m_actionKey);
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

} // stren
