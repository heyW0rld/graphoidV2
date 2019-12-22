#ifndef VERTEX_H
#define VERTEX_H

#include <qstring.h>
#include <qpoint.h>
#include <QPainter>

#define VER_RADIUS 50 //Визуальный радиус вершины

class Vertex
{
public:
    Vertex();
    Vertex(const QString & str, int x, int y);
    Vertex(const QString & str, const QPoint &p);
    void setName(const QString & str);
    void setPoint(const QPoint & p);
    void setColor(const QColor & color);
    void paint(QPainter *painter);
    const QString & getName() const;
    const QPoint & getPoint() const;

private:
    QString name;
    QPoint point;
    QColor color;
};

#endif // VERTEX_H
