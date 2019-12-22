#include "edge.h"

Edge::Edge(const vertex_smpt &eVer, int w) : Edge(0, 0, eVer, w) { }

Edge::Edge(int x, int y, const vertex_smpt &eVer, int w) : edge_x(x), edge_y(y), endVer(eVer), weight(w) { }

Edge::Edge(const vertex_smpt &sVer, const vertex_smpt &eVer, int w) : srcVer(sVer), endVer(eVer), weight(w) //откуда, куда
{
    edge_x = (sVer->getPoint().x() + eVer->getPoint().x()) / 2;
    edge_y = (sVer->getPoint().y() + eVer->getPoint().y()) / 2;
}

int Edge::x() const
{
    return edge_x;
}

int Edge::y() const
{
    return edge_y;
}

const QPoint Edge::getPoint() const
{
    return QPoint(edge_x, edge_y);
}

void Edge::setPoint(int x, int y)
{
    edge_x = x;
    edge_y = y;
}

void Edge::setPoint(QPoint point)
{
    edge_x = point.x();
    edge_y = point.y();
}

const vertex_smpt& Edge::getVertex() const
{
    return endVer;
}

const vertex_smpt& Edge::getStartVertex() const
{
    return srcVer;
}

void Edge::setVertex(const vertex_smpt &sVer, const vertex_smpt &eVer)
{
    this->srcVer = sVer;
    this->endVer = eVer;
}

void Edge::setVecSrc(bool value)
{
    vecSrc = value;
}

void Edge::setVecEnd(bool value)
{
    vecEnd = value;
}

void Edge::paint(QPainter *painter, int visualRadius)
{
    QPen pen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setPen(pen);
    painter->setBrush(color);

    double Pi = 3.141592;
    double arrowSize = 20;

//     отрисовка части ребра к исходной вершине
    if(srcVer)
    {
        double angle1 = acos(QLineF(srcVer->getPoint(), getPoint()).dx() /
                             QLineF(srcVer->getPoint(), getPoint()).length());
        if (QLineF(srcVer->getPoint(), getPoint()).dy() >= 0)
            angle1 = 2 * Pi - angle1;
        if(vecSrc)
        {
            QPointF sourceArrowP1 = srcVer->getPoint()+ QPointF(sin(angle1 + Pi / 3) * arrowSize,
                                                                cos(angle1 + Pi / 3) * arrowSize)+ QPointF(VER_RADIUS/2*cos(angle1),
                                                                                                           VER_RADIUS/2 * sin(angle1-Pi));
            QPointF sourceArrowP2 = srcVer->getPoint() + QPointF(sin(angle1 + Pi - Pi / 3) * arrowSize,
                                                                 cos(angle1 + Pi - Pi / 3) * arrowSize)+QPointF(VER_RADIUS/2*cos(angle1),
                                                                                                                VER_RADIUS/2 * sin(angle1-Pi));

            painter->drawLine(sourceArrowP1, srcVer->getPoint()+ QPointF(VER_RADIUS/2*cos(angle1), VER_RADIUS/2 * sin(angle1-Pi)));
            painter->drawLine(sourceArrowP2, srcVer->getPoint()+ QPointF(VER_RADIUS/2*cos(angle1), VER_RADIUS/2 * sin(angle1-Pi)));
        }
        painter->drawLine(srcVer->getPoint() + QPointF(VER_RADIUS/2*cos(angle1), VER_RADIUS/2 * sin(angle1-Pi)), getPoint());
    }

//    отрисовка части ребра к конечной вершине
    double angle2 = acos(QLineF(getVertex()->getPoint(), getPoint()).dx() /
                         QLineF(getVertex()->getPoint(), getPoint()).length());
    if (QLineF(getVertex()->getPoint(), getPoint()).dy() >= 0)
        angle2 = 2 * Pi - angle2;
    if(vecEnd)
    {
        QPointF destArrowP1 =  QPointF(getVertex()->getPoint() + QPointF(sin(angle2 + Pi/3) * arrowSize,
                                                                         cos(angle2 +Pi/3) * arrowSize)) + QPointF(VER_RADIUS/2*cos(angle2),
                                                                                                                   VER_RADIUS/2 * sin(angle2-Pi));
        QPointF destArrowP2 =  QPointF(getVertex()->getPoint() + QPointF(sin(angle2 + Pi - Pi/3) * arrowSize,
                                                                         cos(angle2 + Pi - Pi/3) * arrowSize))+ QPointF(VER_RADIUS/2*cos(angle2),
                                                                                                                        VER_RADIUS/2 * sin(angle2-Pi));

        painter->drawLine(destArrowP1, getVertex()->getPoint() + QPointF(VER_RADIUS/2*cos(angle2), VER_RADIUS/2 * sin(angle2-Pi)));
        painter->drawLine(destArrowP2, getVertex()->getPoint() + QPointF(VER_RADIUS/2*cos(angle2), VER_RADIUS/2 * sin(angle2-Pi)));
    }

    painter->drawLine(getPoint(),  getVertex()->getPoint() + QPointF(VER_RADIUS/2*cos(angle2), VER_RADIUS/2 * sin(angle2-Pi)));
    QPen tmp = painter->pen();
    painter->setPen(QPen(Qt::DotLine));
    painter->drawEllipse(x() - visualRadius, y() - visualRadius, 2 * visualRadius, 2 * visualRadius);
    painter->setPen(tmp);
    painter->drawText(QPoint(x() - EDGE_RADIUS/3, y() + EDGE_RADIUS/3), QString::number(getWeight()));
}

int Edge::getWeight() const
{
    return weight;
}

void Edge::setWeight(int w)
{
    weight = w;
}

bool Edge::operator==(const Edge &n)
{
    if(edge_x != n.x())
        return false;
    if(edge_y != n.y())
        return false;
    return true;
}

void Edge::setColor(const QColor &value)
{
    color = value;
}

bool Edge :: getVecSrc() const{
    return vecSrc;
}
bool Edge :: getVecEnd() const{
    return vecEnd;
}
