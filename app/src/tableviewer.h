#ifndef TABLEVIEWER_H
#define TABLEVIEWER_H

#include <QTableWidgetItem>

#define TAG_SIZE 8

class TableViewer
{
    QVector<QTableWidgetItem *> m_tagItemList{TAG_SIZE};
    QTableWidget *m_parent;
    QModelIndex m_index;
public:
    TableViewer(QTableWidget *parent);
    ~TableViewer();
public:
    void setNewItems(const QVector<QString> &current);
    void setNewItems(const QVector<QString> &current, const QModelIndex &index);
    QVector<QString> getResult();
    QModelIndex getIndex();
};

#endif // TABLEVIEWER_H
