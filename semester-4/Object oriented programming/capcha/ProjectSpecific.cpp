
#include "ProjectSpecific.h"
#include <QDir>
#include <QString>


QString project::getProjectPath() {
    QString fullPath = QDir::currentPath();
    QDir dir(fullPath);
    while (!dir.isRoot() && !dir.path().endsWith("capcha"))
        dir.cdUp();
    return dir.path();
}
