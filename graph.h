#ifndef GRAPH_H
#define GRAPH_H

/*версия 2.2
 *
 * Граф поддерживает методы:
 * добавление вершины(в виде указателя на вершину)
 * просмотр/изменение текущих данных о вершине(
 * удаление вершины
 * получение данных о всех вершинах
 * очистка
 * проверка на вхождение вершины в мн. вершин графа
 *
 * По сравнению с предыдущей версией:
 * Добавлены умные указатели
*/

#include <qmap.h>
#include <qvector.h>
#include <qset.h>
#include <qlist.h>
#include "vertex.h"
#include "edge.h"
#include <QMutableListIterator>
#include <memory>

//smpt - smart pointer
using edge_smpt = std::shared_ptr<Edge>;

uint qHash(const vertex_smpt &v);

class Graph
{
public:
    Graph();
    Graph copy();
    void insert(const vertex_smpt &v, const QList<edge_smpt> &vp);
    void remove(const vertex_smpt &v);
    QList<edge_smpt>& vertexAt(const vertex_smpt &v);
    QList<edge_smpt>& operator[](const vertex_smpt &v);
    QVector<QVector<int>> toAdjacencyMatrix(bool(*compare)(const vertex_smpt&, const vertex_smpt&) = nullptr);
    const QSet<vertex_smpt>& getVertexAsKeys() const;
    bool contains(const vertex_smpt &v) const;
    void clear();

private:
    QSet<vertex_smpt> ver_list;//set указателей на все вершины
    QMap<vertex_smpt, QList<edge_smpt>> graph;//структура, хранящая полные данные о текущем графе
};

#endif // GRAPH_H
