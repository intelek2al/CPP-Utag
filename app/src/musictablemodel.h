#ifndef MUSICTABLEMODEL_H
#define MUSICTABLEMODEL_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QVector>

struct MusicList
{
    QString title = "";
    QString artist = "";
    QString gener = "";
};

class MusicTableModel : public QAbstractItemModel
{
    Q_OBJECT
    QWidget *m_parent;
    QHash<int, QByteArray> m_roleNames;
    QVector<MusicList> music_list{{"aaa", "AAA", "Rock"}, {"bbb", "BBB", "R&B"}, {"ccc", "CCC", "Rock"}};

public:
    explicit MusicTableModel(QWidget *parent = nullptr);
    QModelIndex parent(const QModelIndex &child);
    int rowCount(const QModelIndex &parent = QModelIndex());
    int columnCount(const QModelIndex &parent = QModelIndex());
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);
};

#endif // MUSICTABLEMODEL_H
