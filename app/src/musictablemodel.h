#ifndef MUSICTABLEMODEL_H
#define MUSICTABLEMODEL_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QVector>

// struct MusicList
// {
//     QString title = "";
//     QString artist = "";
//     QString gener = "";
// };

class MusicTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QWidget *m_parent;
    QVector<QString> listHeaders = {"Title", "Artist", "Gener", "Album", "Year", "Track"};
    QHash<int, QByteArray> m_roleNames;
    QVector<QVector<QString>> music_list{{"bbb", "BBB", "R&B", "bbb", "BBB", "R&B"}, {"cccaasdasdasasdasdasdasdasddasd", "CCC", "Rock", "ccc", "CCC", "Rock"}, {"aaa", "AAA", "Rock", "aaa", "AAA", "Rock"}, {"Killer", "Queen", "Jass", "aaa", "AAA", "Rock"}};

public:
    explicit MusicTableModel(QWidget *parent = nullptr);
    // virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    // virtual QModelIndex parent(const QModelIndex &child) const override;
    // QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
};

#endif // MUSICTABLEMODEL_H
