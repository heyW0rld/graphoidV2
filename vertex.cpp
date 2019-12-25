#include "vertex.h"

Vertex::Vertex() : Vertex("", 0, 0) {}

Vertex::Vertex(const QString & str, int x, int y): name(str), point(QPoint(x, y)) {}

Vertex::Vertex(const QString & str, const QPoint &p): name(str), point(p) {}

void Vertex::setName(const QString & str)
{
    name = str;
}

void Vertex::setPoint(const QPoint & p)
{
    point = p;
}

void Vertex::setColor(const QColor &color)
{
    this->color = color;
}

void Vertex::paint(QPainter *painter)
{
    painter->setBrush(QBrush(color));
    painter->drawEllipse(getPoint().x() - VER_RADIUS/2, getPoint().y() - VER_RADIUS/2, VER_RADIUS, VER_RADIUS);
    painter->drawText(QPoint(getPoint().x() - VER_RADIUS/3,getPoint().y()+VER_RADIUS/3), name);
}

const QString & Vertex::getName() const
{
    return name;
}

const QPoint & Vertex::getPoint() const
{
    return point;
}

const QColor & Vertex::getColor() const
{
    return color;
}
