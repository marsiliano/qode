#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>

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

    void open(const QFileInfo &fi);

private:
    Ui::MainWindow *ui;

    QPlainTextEdit m_editor;
    ToolBar m_toolbar;
    FileSystemView m_fsView;
};
