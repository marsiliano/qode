#include "ToolBar.hpp"

#include <QApplication>
#include <QMessageBox>

ToolBar::ToolBar()
{
    auto actQuit = std::make_unique<QAction>(tr("Quit"));
    actQuit->setIcon(QIcon("://quit.png"));
    actQuit->setShortcut(QKeySequence::Quit);
    connect(actQuit.get(), &QAction::triggered, this, []() { QApplication::quit(); });
    m_acitons[Action::Quit] = std::move(actQuit);

    auto actAbout = std::make_unique<QAction>(tr("About"));
    connect(actAbout.get(), &QAction::triggered, this, []() {
        QMessageBox::information(nullptr,
                                 tr("About"),
                                 QString("%1 %2")
                                     .arg(qApp->applicationName())
                                     .arg(qApp->applicationVersion()));
    });
    m_acitons[Action::About] = std::move(actAbout);

    setMovable(false);
    setFloatable(false);
    setIconSize(QSize(24, 24));
    addActions({m_acitons.at(Action::Quit).get(), m_acitons.at(Action::About).get()});
}
