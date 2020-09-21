#include "musictablemodel.h"

MusicTableModel::MusicTableModel(QWidget *parent) : m_parent(parent) {}

QModelIndex MusicTableModel::parent(const QModelIndex &child)
{
    return *this;
}

int MusicTableModel::rowCount(const QModelIndex &parent = QModelIndex())
{
    return music_list.size();
}

int MusicTableModel::columnCount(const QModelIndex &parent = QModelIndex())
{
    return 3;
}

QVariant MusicTableModel::data(const QModelIndex &index, int role = Qt::DisplayRole)
{
    if (!music_list.empty())
        return music_list[index.row()]->title;
    else
        return QString();
}
