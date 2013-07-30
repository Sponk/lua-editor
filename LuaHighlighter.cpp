#include "LuaHighlighter.h"
#include <cstdio>

LuaHighlighter::LuaHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
    endColor.setRgb(0x33, 0xCC, 0xFF);
    commentColor.setRgb(0x33, 0xFF, 0xCC);
}

void LuaHighlighter::highlightBlock(const QString& text)
{
    for(int i = 0; i < text.length(); i++)
    {
        if(text.at(i).isNumber())
        {
            setFormat(i, 1, Qt::green);
        }


        // Keywords
        int idx = text.indexOf("end");

        if(idx != -1)
            setFormat(idx, 3, endColor);

        idx = text.indexOf("function");

        if(idx != -1)
            setFormat(idx, 8, endColor);

        // Comments
        idx = text.indexOf("--");
        int comment = idx;

        if(idx != -1)
        {
            setFormat(idx, text.length() - idx, commentColor);
        }

        // Quotes
        idx = text.indexOf("\"");

        if(idx != -1 && (idx < comment || comment == -1))
        {
            int idx2 = text.indexOf("\"", idx + 1);

            if(idx2 != -1)
            {
                idx2++;
                setFormat(idx, idx2 - idx, Qt::red);
            }
        }
    }
}
