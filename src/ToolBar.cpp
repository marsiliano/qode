#include "ToolBar.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>

ToolBar::ToolBar(QWidget *parent)
    : QToolBar(parent)
{
    auto actQuit = std::make_unique<QAction>(tr("Quit"));
    actQuit->setIcon(QIcon("://quit.png"));
    actQuit->setShortcut(QKeySequence::Quit);
    connect(actQuit.get(), &QAction::triggered, this, &ToolBar::quit);
    m_acitons[Action::Quit] = std::move(actQuit);

    auto actAbout = std::make_unique<QAction>(tr("About"));
    connect(actAbout.get(), &QAction::triggered, this, &ToolBar::about);
    m_acitons[Action::About] = std::move(actAbout);

    auto actOpen = std::make_unique<QAction>(tr("Open"));
    actOpen->setIcon(QIcon("://files.png"));
    connect(actOpen.get(), &QAction::triggered, this, &ToolBar::open);
    m_acitons[Action::Open] = std::move(actOpen);

    auto actSave = std::make_unique<QAction>(tr("Save"));
    actSave->setIcon(QIcon("://technology.png"));
    actSave->setShortcut(QKeySequence::Save);
    connect(actSave.get(), &QAction::triggered, this, &ToolBar::save);
    m_acitons[Action::Save] = std::move(actSave);

    setMovable(false);
    setFloatable(false);
    setIconSize(QSize(24, 24));
    addActions({m_acitons.at(Action::Open).get(),
                m_acitons.at(Action::Save).get(),
                m_acitons.at(Action::Quit).get(),
                m_acitons.at(Action::About).get()});
}

void ToolBar::quit()
{
    // TODO: add data to save
    QApplication::quit();
}

void ToolBar::about()
{
    QMessageBox::information(nullptr,
                             tr("About"),
                             QStringLiteral("%1 %2")
                                 .arg(qApp->applicationName())
                                 .arg(qApp->applicationVersion()));
}

void ToolBar::open()
{
    auto f = QFileDialog::getOpenFileName();
    if (f.isEmpty()) {
        qDebug() << "filename is empty";
        return;
    }

    emit requestOpen(f);
}

void ToolBar::save()
{
    emit requestSave();
}
