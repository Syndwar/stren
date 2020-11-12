#include "widget_tree.h"

#include "engine/engine_handler.h"
#include "engine/action.h"
#include "widgets/button.h"
#include "widgets/screen.h"

namespace stren
{

class UpdateTreeAction : public IAction
{
private:
    WidgetTree * m_tree;
public:
    ///
    /// Constructor
    ///
    UpdateTreeAction(WidgetTree * tree)
        : m_tree(tree)
    {
    }
    ///
    /// Destructor
    ///
    virtual ~UpdateTreeAction() {}
    ///
    /// update widget tree
    ///
    virtual bool exec() override
    {
        if (m_tree)
        {
            m_tree->updateBranches();
        }
        return false;
    }
};

WidgetTreeBranch::WidgetTreeBranch(Widget * widget, WidgetTreeBranch * parent, IAction * action)
    : Container()
    , m_widget(widget)
    , m_parent(parent)
    , m_updateAction(action)
    , m_isExpanded(false)
    , m_index(0)
{
    m_isContainer = nullptr != dynamic_cast<Container *>(widget);

    m_expandBtn = new Button();
    if (m_expandBtn)
    {
        m_expandBtn->setText(m_isContainer ? (m_isExpanded ? "-" : "+") : " ");
        m_expandBtn->setRect(0, 0, 32, 32);
        m_expandBtn->setFont("robo_bold_15_fnt");
        m_expandBtn->setTextAlignment(Alignment::CenterMiddle);
        m_expandBtn->addCallback(EventType::MouseClicked, this, &WidgetTreeBranch::onControlClicked);
        attach(m_expandBtn);
    }
    m_nameBtn = new Button();
    if (m_nameBtn)
    {
        m_nameBtn->setRect(32, 0, 200, 32);
        m_nameBtn->setFont("robo_bold_15_fnt");
        m_nameBtn->setTextAlignment(Alignment::LeftMiddle);
        m_nameBtn->addCallback(EventType::MouseClicked, this, &WidgetTreeBranch::onWidgetClicked);
        attach(m_nameBtn);
    }

    if (m_widget)
    {
        m_nameBtn->setColour(m_widget->isOpened() ? Colour::White : Colour::Grey);
        setText(m_widget->getId());
    }
}

WidgetTreeBranch::~WidgetTreeBranch()
{
    if (m_updateAction)
    {
        delete m_updateAction;
        m_updateAction = nullptr;
    }
}

void WidgetTreeBranch::onControlClicked()
{
    m_isExpanded = !m_isExpanded;
    if (m_expandBtn)
    {
        m_expandBtn->setText(m_isContainer ? (m_isExpanded ? "-" : "+") : " ");
    }
    if (m_updateAction)
    {
        m_updateAction->exec();
    }
}

void WidgetTreeBranch::onWidgetClicked()
{
    if (m_widget)
    {
        m_widget->instantView(!m_widget->isOpened());

        if (m_nameBtn)
        {
            m_nameBtn->setColour(m_widget->isOpened() ? Colour::White : Colour::Grey);
        }
    }
}

void WidgetTreeBranch::setText(const std::string & value)
{
    if (m_nameBtn)
    {
        if (value.empty())
        {
            m_nameBtn->setText("[noname]");
        }
        else
        {
            m_nameBtn->setText(value);
        }
    }
}

WidgetTree::WidgetTree(const std::string & id)
    : ScrollContainer(id)
    , m_lineSize(32)
    , m_root(nullptr)
    , m_counter(0)
{
    const int width = EngineHandler::getScreenWidth();
    const int height = EngineHandler::getScreenHeight();
    setRect(0, 0, width, height);
    instantClose();
}

WidgetTree::~WidgetTree()
{
}

void WidgetTree::doOpen()
{
    Screen * currentScreen = EngineHandler::getCurrentScreen();
    if (m_root != currentScreen)
    {
        deleteBranches();
        m_root = currentScreen;
        m_counter = 0;
        createBranch(m_root, nullptr);
    }
    updateBranches();
}

void WidgetTree::deleteBranches()
{
    detachAll();
    m_branches.clear();
    m_root = nullptr;
}

void WidgetTree::createBranch(Widget * root, WidgetTreeBranch * parent)
{
    if (root)
    {
        UpdateTreeAction * updateAction = new UpdateTreeAction(this);
        WidgetTreeBranch * branch = new WidgetTreeBranch(root, parent, updateAction);
        branch->setIndex(m_counter);
        attach(branch);
        m_branches.push_back(branch);

        if (Container * rootContainer = dynamic_cast<Container *>(root))
        {
            ++m_counter;
            const std::vector<Widget *> & attached = rootContainer->debugGetAttached();
            for (Widget * widget : attached)
            {
                createBranch(widget, branch);
            }
            --m_counter;
        }
    }
}

void WidgetTree::updateBranches()
{
    int y(0);
    for (WidgetTreeBranch * branch : m_branches)
    {
        const int x = branch->getIndex() * m_lineSize;
        branch->moveTo(x, y);
        WidgetTreeBranch * parent = branch->getParent();
        if (parent)
        {
            branch->instantView(parent->isExpanded());
        }
        if (branch->isOpened())
        {
            y += m_lineSize;
        } 
    }
    setContentRect(0, 0, getRect().getWidth(), y);
}
} // stren