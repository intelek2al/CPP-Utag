//
// Created by Serhiy Nikolayenko on 9/28/20.
//

#include "logger.h"

Logger::Logger() {}

Logger::~Logger() {
}

QVector<QString> Logger::show_logger() const {
    return logger;
}

void Logger::add_log_massage(QString& message) {
    logger.push_back(message);
}
