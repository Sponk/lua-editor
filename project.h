#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

class Project
{
    QString path;
    QString name;
    QString workingDir;

    // TODO: Aus settings rausnehmen!
    QString luaInterpreter;
public:
    Project();

    void setPath(QString path) { this->path = path; }
    QString getPath() { return this->path; }

    void setName(QString name) { this->name = name; }
    QString getName() { return this->name; }

    QString getWorkingDir() { return workingDir; }
    void setWorkingDir(QString workingDir) { this->workingDir = workingDir; }

    void save();
    bool load(QString path);
};

#endif // PROJECT_H
