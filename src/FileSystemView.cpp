#include "FileSystemView.hpp"

#include <QHeaderView>
#include <QtDebug>

FileSystemView::FileSystemView(QWidget *parent)
    : QDockWidget(parent)
{
    setFeatures(features() & ~QDockWidget::DockWidgetClosable);
    setFeatures(features() & ~QDockWidget::DockWidgetFloatable);

    m_model.setFilter(QDir::Filter::AllEntries | QDir::Filter::Hidden | QDir::Filter::NoDotAndDotDot);
    m_tree.setModel(&m_model);
    auto headerView = m_tree.header();
    for (auto i = 1; i < headerView->count(); ++i) {
        headerView->setSectionHidden(i, true);
    }

    setWidget(&m_tree);

    connect(&m_tree, &QTreeView::clicked, this, &FileSystemView::checkOpenFile);
}

void FileSystemView::setPath(const QString &p)
{
    m_model.setRootPath(p);
    m_tree.setRootIndex(m_model.index(p));
}

void FileSystemView::checkOpenFile(const QModelIndex &index)
{
    auto fn = createPath(index);
    QFileInfo file(fn);
    if (file.isDir()) {
        return;
    }

    emit requestOpen(fn);
}

QString FileSystemView::createPath(const QModelIndex &index) const
{
    QStringList foldersNested{m_model.data(index).toString()};
    auto p = index.parent();
    while (p.isValid()) {
        foldersNested.push_back(m_model.data(p).toString());
        p = p.parent();
    }

    std::reverse(std::begin(foldersNested), std::end(foldersNested));
    QString filename;
    for (auto &i : foldersNested) {
        filename += QDir::toNativeSeparators("/") + i;
    }
    return filename;
}
