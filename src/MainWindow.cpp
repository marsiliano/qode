#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(&m_editor);
    addToolBar(&m_toolbar);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, &m_fsView);

    connect(&m_toolbar, &ToolBar::requestOpen, this, &MainWindow::open);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(QString filename)
{
    if (QFileInfo(filename).isDir()) {
        m_fsView.setPath(filename);
        return;
    }

    auto path = filename;
    const auto i = filename.lastIndexOf('/');
    path.remove(i, std::distance(filename.begin() + i, filename.end()));
    m_fsView.setPath(path);
    QFile f(filename);
    if (!f.exists()) {
        return;
    }

    f.open(QIODevice::OpenModeFlag::ReadWrite);
    m_editor.setPlainText(f.readAll());
}
