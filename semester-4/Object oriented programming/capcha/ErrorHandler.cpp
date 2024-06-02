#include "ErrorHandler.h"
#include "ProjectSpecific.h"
#include <QMessageBox>
#include <QFile>
#include <QDate>
#include <QTextStream>
#include <QDir>

ErrorHandler::ErrorHandler() {}

void ErrorHandler::callErrorPopup(const std::string& error_message) const {
    QMessageBox::critical(NULL, "Ошибка", QString::fromStdString(error_message));
    logError(error_message);
}

void ErrorHandler::logError(const std::string& error_message) const {
    QString path = project::getProjectPath() + "/logs/" + QDate::currentDate().toString() + ".txt";

    QFile log_file(path);
    log_file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream stream(&log_file);
    stream << QString::fromStdString(error_message) << "\n";
    log_file.close();
}
