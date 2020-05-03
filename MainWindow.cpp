#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(&m_editor);
    this->addToolBar(&m_toolbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}
