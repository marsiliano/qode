#pragma once

#include <QToolBar>

class ToolBar final : public QToolBar
{
    Q_OBJECT

public:
    ToolBar();

private:
    enum class Action { Quit, About };
    std::unordered_map<Action, std::unique_ptr<QAction>> m_acitons;
};
