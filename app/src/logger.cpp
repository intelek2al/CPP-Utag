#include "logger.h"
#include "ui_mainwindow.h"

Logger::Logger(Ui::MainWindow *child) {
    ui = child;
}

Logger::~Logger() {

}

QVector<QString> Logger::show_logger() const {

    return m_logger;
}

void Logger::add_log_massage(QString& message) {
    QDate current_date;

    current_date.currentDate();

    current_date.toString( Qt::ISODate);
    QString event = current_date.toString( Qt::ISODate) + message;
    m_logger.push_back(event);
}
