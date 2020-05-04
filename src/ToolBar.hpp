#pragma once

#include <QToolBar>

class ToolBar final : public QToolBar
{
    Q_OBJECT

public:
    ToolBar();

signals:
    void requestOpen(QString filename);

private slots:
    void quit();
    void about();
    void open();

private:
    enum class Action { Quit, About, Open, Save };
    std::unordered_map<Action, std::unique_ptr<QAction>> m_acitons;
};
