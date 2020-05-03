#include "FileSystemView.hpp"

FileSystemView::FileSystemView()
{
    m_model.setRootPath("");
    m_model.setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    m_model.setOption(QFileSystemModel::DontWatchForChanges);
    m_tree.setModel(&m_model);
    setWidget(&m_tree);
}
