#include "FileSystemView.hpp"

#include <QHeaderView>

FileSystemView::FileSystemView()
{
    setFeatures(features() & ~QDockWidget::DockWidgetClosable);
    setFeatures(features() & ~QDockWidget::DockWidgetFloatable);

    m_tree.setModel(&m_model);
    auto headerView = m_tree.header();
    for (auto i = 1; i < headerView->count(); ++i) {
        headerView->setSectionHidden(i, true);
    }

    setWidget(&m_tree);
}

void FileSystemView::setPath(const QString &p)
{
    m_model.setRootPath(p);
    m_tree.setRootIndex(m_model.index(p));
}
