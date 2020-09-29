#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QLineEdit>
#include <QComboBox>
#include <QVector>
#include <QString>

class Searcher : public QObject
{
    Q_OBJECT
public:
    explicit Searcher(QLineEdit *parent = nullptr, QComboBox *hendler = nullptr, QVector<QVector<QString>> *tableMusic = nullptr);
    ~Searcher() override = default;
    void setDown();
    QVector<QVector<QString>> getList() const;

//public slots:
    QVector<QVector<QString>> search();

private:
    QString m_searchParam;
    QLineEdit *m_parent = nullptr;
    QComboBox *m_hendler = nullptr;
    QVector<QVector<QString>> *m_list = nullptr;
    QVector<QVector<QString>> m_searched_list;
};

#endif // SEARCHER_H
