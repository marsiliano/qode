#pragma once

#include <QDockWidget>
#include <QFileSystemModel>
#include <QTreeView>

class FileSystemView final : public QDockWidget
{
    Q_OBJECT

public:
    explicit FileSystemView(QWidget *parent = nullptr);

    void setPath(const QString &p);

private:
    QFileSystemModel m_model;
    QTreeView m_tree;
};
