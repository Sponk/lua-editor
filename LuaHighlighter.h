#ifndef LUAHIGHLIGHTER_H
#define LUAHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class LuaHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit LuaHighlighter(QObject *parent = 0);
    void highlightBlock(const QString& text);
    
signals:
    
public slots:

private:
    QColor numberColor;
    QColor endColor;
    QColor functionColor;
    QColor commentColor;
    
};

#endif // LUAHIGHLIGHTER_H
