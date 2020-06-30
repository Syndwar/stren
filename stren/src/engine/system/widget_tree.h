#ifndef STREN_WIDGET_TREE_H
#define STREN_WIDGET_TREE_H

#include "widgets/scroll_container.h"

namespace stren
{
class IAction;
class Button;
///
/// class WidgetTreeBranch
///
class WidgetTreeBranch : public Container
{
private:
    bool               m_isContainer;   ///< @todo
    bool               m_isExpanded;    ///< @todo
    size_t             m_index;         ///< @todo
    Button *           m_expandBtn;     ///< @todo
    Button *           m_nameBtn;       ///< @todo
    Widget *           m_widget;        ///< @todo
    WidgetTreeBranch * m_parent;        ///< @todo
    IAction *          m_updateAction;  ///< @todo
public:
    ///
    /// Constructor
    ///
    WidgetTreeBranch(Widget * widget, WidgetTreeBranch * parent, IAction * action);
    ///
    /// Destructor
    ///
    ~WidgetTreeBranch();
    ///
    /// @todo
    ///
    void setIndex(const size_t index) { m_index = index; }
    ///
    /// @todo
    ///
    size_t getIndex() const { return m_index; }
    ///
    /// @todo
    ///
    bool isContainer() const { return m_isContainer; }
    ///
    /// @todo
    ///
    bool isExpanded() const { return m_isExpanded; }
    ///
    /// @todo
    ///
    void onControlClicked();
    ///
    /// @todo
    ///
    void onWidgetClicked();
    ///
    /// @todo
    ///
    void setText(const std::string & value);
    ///
    /// @todo
    ///
    WidgetTreeBranch * getParent() { return m_parent; }
};
///
/// class WidgetTree
///
class WidgetTree : public ScrollContainer
{
private:
    size_t                          m_lineSize;     ///< @todo
    size_t                          m_counter;      ///< @todo
    Widget *                        m_root;         ///< @todo
    std::vector<WidgetTreeBranch *> m_branches;     ///< @todo
public:
    ///
    /// Constructor
    ///
    WidgetTree(const std::string & id);
    ///
    /// Destructor
    ///
    ~WidgetTree();
    ///
    /// @todo
    ///
    void updateBranches();
private:
    ///
    /// @todo
    ///
    void deleteBranches();
    ///
    /// @todo
    ///
    void createBranch(Widget * root, WidgetTreeBranch * parent);
    ///
    /// @todo
    ///
    virtual void doOpen() override;
};
} // stren

#endif // STREN_WIDGET_TREE_H
