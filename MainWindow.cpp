#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

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
