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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(const QFileInfo &fi)
{
    m_fsView.setPath(fi.absolutePath());
    QFile file(fi.absoluteFilePath());
    file.open(QIODevice::OpenModeFlag::ReadWrite);
    m_editor.setPlainText(file.readAll());
}
