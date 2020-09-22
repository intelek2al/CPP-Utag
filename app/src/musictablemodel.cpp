#include "musictablemodel.h"

MusicTableModel::MusicTableModel(QWidget *parent) : m_parent(parent)
{
    m_roleNames.insert(0, QByteArray("Title"));
    m_roleNames.insert(1, QByteArray("Artist"));
    m_roleNames.insert(2, QByteArray("Gener"));
}

// QModelIndex index(int row, int column, const QModelIndex &parent)
// {
//     return createIndex(row, column, /*&(music_list[index.row()].title)*/ "hello");
// }

// QModelIndex MusicTableModel::parent(const QModelIndex &child) const
// {
//     return QModelIndex();
// }

// QHash<int, QByteArray> MusicTableModel::roleNames() const
// {
//     return m_roleNames;
// }

int MusicTableModel::rowCount(const QModelIndex &parent) const
{
    return music_list.size();
}

int MusicTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MusicTableModel::data(const QModelIndex &index, int role) const
{

    if (!music_list.empty())
        return music_list[index.row()][index.column()];
    else
        return QString();
}

QVariant MusicTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    static int row = 0;

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "Title";
        case 1:
            return "Artist";
        case 2:
            return "Gener";
        }
    }
    return QVariant();
}

void MusicTableModel::sort(int column, Qt::SortOrder order)
{
    if (order == Qt::AscendingOrder)
    {
        std::sort(music_list.begin(), music_list.end(), [=](auto a, auto b) { return a[column] < b[column]; });
    }
    else
        std::sort(music_list.begin(), music_list.end(), [=](auto a, auto b) { return a[column] > b[column]; });
    this->update();
}
