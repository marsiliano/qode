#include "FileSystemView.hpp"

FileSystemView::FileSystemView()
{
    setFeatures(features() & ~QDockWidget::DockWidgetClosable);
    setFeatures(features() & ~QDockWidget::DockWidgetFloatable);

    m_tree.setModel(&m_model);
    setWidget(&m_tree);
}

void FileSystemView::setPath(const QString &p)
{
    m_model.setRootPath(p);
    m_tree.setRootIndex(m_model.index(p));
}
