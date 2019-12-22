#include "graph.h"
#include <QDebug>

Graph::Graph() {}

//просто ищет вершину с тем же именем
const vertex_smpt& findVertex(const QSet<vertex_smpt> &v_list, const vertex_smpt &find_ver){
    for(auto &ver : v_list)
        if(ver->getName() == find_ver->getName())
            return ver;
    return NULL;
}

//для корректной работы сделал через два цикла,
//чтобы при поиске точно быть уверенным, что
//все вершины уже есть и нужная найдется
Graph Graph::copy()
{
    Graph g;
    //Создаю заново вершины в новом графе
    for(auto ver : ver_list){
        vertex_smpt v(new Vertex(ver->getName(), ver->getPoint()));
        v->setColor(Qt::green);
        g.insert(v, QList<edge_smpt>());
    }
    //вставляю ребра
    for(auto ver : ver_list){
        for(auto edge : graph[ver]){
            const vertex_smpt &str_ver = findVertex(g.getVertexAsKeys(), ver);
            const vertex_smpt &end_ver = findVertex(g.getVertexAsKeys(), edge->getVertex());
            edge_smpt ed(new Edge(str_ver, end_ver, edge->getWeight()));
            if(edge->getVecSrc() == true)
                ed->setVecSrc(true);
            ed->setVecEnd(true);
            g[str_ver].append(ed);
        }
    }
    return g;
}

//получение всех текущих вершин
const QSet<vertex_smpt>& Graph::getVertexAsKeys() const
{
    return ver_list;
}

void Graph::insert(const vertex_smpt &v, const QList<edge_smpt> &v_data)
{
    if(!ver_list.contains(v)){//тут сравнение идет по адресу, который содержит указатель
        ver_list.insert(v);
        graph.insert(v, v_data);
    }
}

void Graph::remove(const vertex_smpt &v)
{
    graph.remove(v);
    for(auto ver : ver_list){
        QMutableListIterator<edge_smpt> i(graph[ver]);
        while(i.hasNext()){
            if(i.next()->getVertex() == v)
                i.remove();
        }
    }
//    раз вершина больше не нужна
    ver_list.remove(v);
}

//просто для удобства работы(полностью аналогичен последующему)
QList<edge_smpt>& Graph::vertexAt(const vertex_smpt &v)
{
    if(ver_list.contains(v)){
        return graph[v];
    } else {
        insert(v, QList<edge_smpt>());//если вершины сейчас нет
        return graph[v];
    }
}

QList<edge_smpt>& Graph::operator[](const vertex_smpt &v)
{
    if(ver_list.contains(v)){
        return graph[v];
    } else {
        insert(v, QList<edge_smpt>());//если вершины сейчас нет
        return graph[v];
    }
}

QVector<QVector<int>> Graph::toAdjacencyMatrix(bool(*compare)(const vertex_smpt&, const vertex_smpt&))
{
    auto all_vertex = ver_list.toList();

    if(compare != nullptr)
        std::sort(all_vertex.begin(), all_vertex.end(), compare);

//    Это матрица смежности, она изначально заполняется значениями -1
//    что означает, что никакого значения там нет
    QVector<QVector<int>> adjMatrix(ver_list.size(), QVector<int>(ver_list.size(), 0));

    int index = 0;//Это индекс вершины в матрице

    for(auto ver : all_vertex){
        for(auto edge : graph[ver]){

            int ver_index = all_vertex.indexOf(edge->getVertex());

            if(adjMatrix[index][ver_index] != 0){
                int weight = adjMatrix[index][ver_index];

                if(edge->getWeight() < weight)
                    weight = edge->getWeight();

                adjMatrix[index][ver_index] = weight;
            }
            else {
                adjMatrix[index][ver_index] = edge->getWeight();
            }
            //если ребро неориентированное и не петля
            if(edge->getVecSrc() && ver != edge->getVertex()){
                if(adjMatrix[ver_index][index] != 0){
                    int weight = adjMatrix[ver_index][index];

                    if(edge->getWeight() < weight)
                        weight = edge->getWeight();

                    adjMatrix[ver_index][index] = weight;
                }
                else {
                    adjMatrix[ver_index][index] = edge->getWeight();
                }
            }

        }
        index++;
    }

    return adjMatrix;
}

//проверка на вхождение
bool Graph::contains(const vertex_smpt &v) const
{
    return ver_list.contains(v);
}

void Graph::clear()
{
    graph.clear();
    ver_list.clear();
}

uint qHash(const vertex_smpt &v){
    uint hash = 2139062143;
    const QChar *str = v->getName().data();
    for(; str->unicode(); str++){
        hash = 37 * hash + str->unicode();
    }
    return hash;
}
