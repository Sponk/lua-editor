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

    void setLuaInterpreter(QString lua) { luaInterpreter = lua; }
    QString getLuaInterpreter() { return luaInterpreter; }

    void setLuaArgs(QString args) { luaArgs = args; }
    QString getLuaArgs() { return luaArgs; }

private:
    QString path;

    QString luaInterpreter;
    QString language;
    QString luaArgs;
};

#endif // SETTINGS_H
