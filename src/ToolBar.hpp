#pragma once

#include <QToolBar>

class ToolBar final : public QToolBar
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);

signals:
    void requestOpen(QString filename);
    void requestSave();

private slots:
    void quit();
    void about();
    void open();
    void save();

private:
    enum class Action { Quit, About, Open, Save };
    std::unordered_map<Action, std::unique_ptr<QAction>> m_acitons;
};
