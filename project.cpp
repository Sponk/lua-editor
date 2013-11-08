#include "project.h"
#include <QFile>
#include <QDomDocument>
#include <fstream>

using namespace std;

Project::Project()
{

}

void Project::save()
{
    if(name == "" || path == "")
        return;

    ofstream out;
    out.open(path.toStdString().c_str(), ios::out);

    if(!out)
        return;

    out << "<?xml version='1.0' encoding='UTF-8'?>" << endl;

    out << "<project name='" << name.toStdString() << "'>" << endl;

    out << "<luainterpreter path='" << luaInterpreter.toStdString() << "'></luainterpreter>" << endl;
    out << "<workingdir path='" << workingDir.toStdString() << "'></workingdir>" << endl;

    out << "</project>" << endl;
    out.close();
}

bool Project::load(QString path)
{
   this->path = path;

   QDomDocument doc("project");
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

   QDomElement elem = doc.namedItem("project").toElement();

   if(elem.isNull())
       return false;

   if(elem.hasAttribute("name"))
       name = elem.attribute("name");

   QDomElement interpreter = elem.namedItem("luainterpreter").toElement();

   if(interpreter.hasAttribute("path"))
       luaInterpreter = interpreter.attribute("path");

   QDomElement dir = elem.namedItem("workingdir").toElement();

   if(dir.hasAttribute("path"))
       workingDir = dir.attribute("path");

   return true;
}

