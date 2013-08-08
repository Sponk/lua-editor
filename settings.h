#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
public:
    Settings();
    bool load(QString path);
    void save();

    void setLanguage(QString lang) { language = lang; }
    QString getLanguage() { return language; }

private:
    QString path;

    QString language;
};

#endif // SETTINGS_H
