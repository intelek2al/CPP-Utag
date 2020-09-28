//
// Created by Serhiy Nikolayenko on 9/28/20.
//

#ifndef UTAG_LOGGER_H
#define UTAG_LOGGER_H


#include <QString>
#include <QVector>

class Logger {
public:
    Logger();
    virtual ~Logger();

    void add_log_massage(QString& message);

    QVector<QString> show_logger() const;

private:
    QVector<QString> logger {0};
};


#endif //UTAG_LOGGER_H
