#ifndef EDGE_H
#define EDGE_H

#include <vertex.h>
#include <QPair>
#include <memory>
#include <math.h>

#define EDGE_RADIUS 12 //Визуальный радиус центра ребра

//Класс ребра

using vertex_smpt = std::shared_ptr<Vertex>;

class Edge
{
public:
    Edge() { }
    Edge(const vertex_smpt &eVer, int w);
    Edge(int x, int y, const vertex_smpt &eVer, int w);
    Edge(const vertex_smpt &sVer, const vertex_smpt &eVer, int w);//откуда, куда, вес
    int x() const;
    int y() const;
    const QPoint getPoint() const;
    void setPoint(int x, int y);
    void setPoint(QPoint point);
    const vertex_smpt& getVertex() const;
    const vertex_smpt& getStartVertex() const;
    void setVertex(const vertex_smpt &sVer, const vertex_smpt &eVer);//откуда, куда
    void setVertex(const vertex_smpt &sVer);
    void setVecSrc(bool value);
    void setVecEnd(bool value);
    void paint(QPainter *painter, int visualRadius);
    int getWeight() const;
    void setWeight(int w);
    void setColor(const QColor & value);
    bool operator==(const Edge &n);
    bool getVecSrc() const;
    bool getVecEnd() const;

private:
    int edge_x;
    int edge_y;
    QColor color = Qt::green;
    vertex_smpt srcVer, endVer; //endVer - куда, srcVer - откуда
    int weight;
    bool vecSrc = false, vecEnd = false; // будет ли стрелка
};

#endif // EDGE_H
