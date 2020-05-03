#pragma once

#include <QDockWidget>
#include <QFileSystemModel>
#include <QTreeView>

class FileSystemView final : public QDockWidget
{
    Q_OBJECT

public:
    FileSystemView();

    void setPath(const QString &p);

private:
    QFileSystemModel m_model;
    QTreeView m_tree;
};
