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
    connect(&m_toolbar, &ToolBar::requestSave, this, &MainWindow::save);
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
    m_currentOpen.setFileName(filename);
    if (!m_currentOpen.exists()) {
        qWarning() << filename << "not existes";
        return;
    }

    m_currentOpen.open(QIODevice::OpenModeFlag::ReadOnly);
    m_editor.setPlainText(m_currentOpen.readAll());
    m_currentOpen.close();
}

void MainWindow::save()
{
    m_currentOpen.open(QIODevice::WriteOnly | QIODevice::Truncate);
    m_currentOpen.write(m_editor.toPlainText().toUtf8());
    m_currentOpen.close();
}
