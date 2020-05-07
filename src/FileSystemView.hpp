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

signals:
    void requestOpen(QString filename);

private slots:
    void checkOpenFile(const QModelIndex &index);

private:
    QFileSystemModel m_model;
    QTreeView m_tree;

    QString createPath(const QModelIndex &index) const;
};
