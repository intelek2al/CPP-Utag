#ifndef UTAG_LOGGER_H
#define UTAG_LOGGER_H

#include <QString>
#include <QVector>
#include <QDate>

namespace Ui {
    class MainWindow;
}

class Logger {
public:
    Logger();
    virtual ~Logger();

    void add_log_massage(QString& message);

    QVector<QString> show_logger() const;

private:
//    Ui::MainWindow *ui;
    QVector<QString> m_logger {0};
};


#endif //UTAG_LOGGER_H
