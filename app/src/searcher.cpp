#include "searcher.h"
#include <algorithm>

Searcher::Searcher(QLineEdit *parent, QComboBox *hendler, QVector<QVector<QString>> *tableMusic)
    : m_parent(parent),
    m_hendler(hendler),
    m_list(tableMusic){
    //    connect(m_hendler, QComboBox::currentIndexChanged, this, search);
}

void Searcher::setDown()
{
    m_searched_list.clear();
    m_parent->clear();
}

QVector<QVector<QString>> Searcher::getList() const
{
    if (m_searched_list.empty())
        return *m_list;
    return m_searched_list;
}

QVector<QVector<QString>> Searcher::search() {
    QVector<QVector<QString>> m_searched_list;
    for(auto iter_song = m_list->begin(); iter_song != m_list->end(); ++iter_song) {
//        for (auto iter_tag = iter_song->begin();iter_tag != iter_song->end(); ++iter_tag) {
//            ite
//        }
        auto tmp = std::find(iter_song->begin(), iter_song->end(), m_parent->text());
        if (tmp != iter_song->end()) {
            m_searched_list.push_back(*iter_song);
        }
    }
    return m_searched_list;
}
