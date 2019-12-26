#ifndef TASK14_H
#define TASK14_H

#include "graph.h"
#include <qdebug.h>
#include <QMap>
#include <algorithm>

//мапа степеней всех вершин, нужна для сортировки
//в процессе работы алгоритма
QMap<QString, int> verDegree;

bool degreeCompare(const vertex_smpt& first, const vertex_smpt& second)
{
    if(verDegree[first->getName()] < verDegree[second->getName()])
        return false;
    return true;
}

//проверяю все смежные с данной вершиной вершины
bool checkColor(Graph &g, const vertex_smpt &ver, QColor color)
{
    //возвращаю false когда есть смежная вершина такого цвета
    //проверяю для вершин, откуда ребро
    //может идти в текущую вершину
    for(auto v : g.getVertexAsKeys()){
        for(auto ed : g[v]){
            if(ed->getVertex()->getName() == ver->getName()){
                if(v->getColor() == color)
                    return false;
            }
        }
    }
    //проверяю для вершин
    //в которые ребро идет из текущей
    for(auto ed : g[ver]) {
        if(ed->getVertex()->getColor() == color){
            return false;
        }
    }
    return true;
}

//считаю количество смежных ребер для каждой вершины
void countVertexDegree(Graph &g, const QList<vertex_smpt> &vertices)
{
    for(auto ver : vertices) {
        int degree = 0;
        for(auto v : g.getVertexAsKeys()){
            for(auto ed : g[v]){
                if(ed->getVertex()->getName() == ver->getName()){
                    ++degree;
                }
            }
        }
        for(auto ed : g[ver]) {
            ++degree;
        }
        verDegree[ver->getName()] = degree;
    }
}

int colourVertex(Graph &g)
{
    //хроматическое число
    int chrom_number = 0;

    //по гипотезе «четырех красок», которую доказали,
    //максимум цветов 4, так что генерировать цвета не надо
    QList<QColor> colorList;
    colorList.append(QColor(Qt::gray));
    colorList.append(QColor(Qt::red));
    colorList.append(QColor(Qt::yellow));
    colorList.append(QColor(Qt::blue));

    //лист всех незакрашенных вершин (закрашенные вершины будут из него удаляться)
    QList<vertex_smpt> vertices = g.getVertexAsKeys().toList();
    //нахожу степени каждой вершины и заполняю ими мапу
    countVertexDegree(g, vertices);
    //сортирую список по невозрастанию степеней
    while(!vertices.isEmpty()) {
        QColor color = colorList[chrom_number];
        //крашу вершины в цвет color, окрашенные удаляю
        for(auto ver : vertices) {
            if(checkColor(g, ver, color)) {
                ver->setColor(color);
                vertices.removeOne(ver);
            }
        }

        ++chrom_number;
        if(chrom_number == colorList.size())
                        colorList.append(QColor(Qt::white + chrom_number * 20));
    }

    return chrom_number;
}

#endif // TASK14_H
