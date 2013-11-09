#include "settings.h"
#include <QFile>
#include <QDomDocument>
#include <fstream>

using namespace std;

Settings::Settings()
{
    language = "lua-editor_en";
}

 bool Settings::load(QString path)
 {
#ifdef WIN32
    path = path.replace("/", "\\");
#endif
    this->path = path;

    QDomDocument doc("settings");
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        return false;
    }

    file.close();

    QDomElement elem = doc.namedItem("settings").toElement();

    if(elem.isNull())
        return false;

    QDomElement lang = elem.namedItem("language").toElement();

    if(lang.hasAttribute("name"))
        language = lang.attribute("name");

    QDomElement lua = elem.namedItem("luainterpreter").toElement();

    if(lua.hasAttribute("path"))
        luaInterpreter = lua.attribute("path");

    QDomElement args = elem.namedItem("luaargs").toElement();

    if(args.hasAttribute("args"))
        luaArgs = args.attribute("args");

    return true;
 }

 void Settings::save()
 {
    ofstream out;
    out.open(path.toStdString().c_str(), ios::out);

    if(!out)
        return;

    out << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
    out << "<settings>" << endl;

    out << "<language name='" << language.toStdString() << "'></language>" << endl;
    out << "<luainterpreter path='" << luaInterpreter.toStdString() << "'></luainterpreter>" << endl;
    out << "<luaargs args='" << luaArgs.toStdString() << "'></luaargs>" << endl;

    out << "</settings>";
    out.close();
 }
