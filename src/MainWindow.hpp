#pragma once

#include <QMainWindow>

#include "Editor.hpp"
#include "FileSystemView.hpp"
#include "ToolBar.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
} // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setTreeViewPath(QString filename);

public slots:
    void open(QString filename);
    void openAndSetPath(QString filename);

private slots:
    void save();

private:
    Ui::MainWindow *ui;

    Editor m_editor;
    ToolBar m_toolbar;
    FileSystemView m_fsView;
    QFile m_currentOpen;
};
