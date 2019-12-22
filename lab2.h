#ifndef LAB2_H
#define LAB2_H
#include "graph.h"
#include "edge.h"
#include <QVector>
#include <QQueue>
#include <QStack>
#include <QDebug>
#include <QPair>
#include <memory>
#include "mainwindow.h"
#include"task.h"
#include"saving.h"
#include <string>
#include <QMessageBox>
#include <QObject>





using namespace std;

class lab2
{
public:
    static QVector<vertex_smpt> BFS(Graph& graph, int vBegin, int vEnd)
    {
        const int UNDEF = -1;

        QVector<QVector<int>> matrix = graph.toAdjacencyMatrix(compare);
        qDebug() << matrix;
        std::vector<int> len(matrix.count(), UNDEF);
        QQueue<int> q;
        QStack<edge_smpt> edges;
        QList <vertex_smpt> graphVertices = graph.getVertexAsKeys().toList();
        qSort(graphVertices.begin(), graphVertices.end(), compare);

        q.enqueue(vBegin);
        len[vBegin] = 0;
        while (true)
        {
            if (q.empty())
            {

                throw 1;
            }
            int current = q.dequeue();
            if (current == vEnd)
            {
                //printf("Size your path : %d\n", len[vEnd]);
                qDebug() << "Path from Vertex " << graphVertices[vBegin]->getName() << "to Vertex " << graphVertices[vEnd]->getName() <<" is ";
                qDebug() << vEnd + 1;
                QList<vertex_smpt> result;
                result.append(graphVertices[vEnd]);
                while (!edges.empty())
                {
                    //TODO
                    edge_smpt e = edges.pop();
                    if (graphVertices.indexOf(e->getVertex()) == vEnd)
                    {
                        vEnd = graphVertices.indexOf((*e).getStartVertex());
                        qDebug() << " <- " << graphVertices[vEnd]->getName();
                        result.append(graphVertices[vEnd]);
                    }
                }


                return result.toVector();
            }
            for (int next = 0; next < matrix.count(); next++)
            {
                if (len[next] == UNDEF && matrix[current][next] > 0)//node = current, j = next
                {
                    q.enqueue(next);
                    len[next] = len[current] + 1;
                    Edge* e = new Edge();
                    e->setVertex(graphVertices[current], graphVertices[next]);
                    edges.push(edge_smpt(e));
                    if (current == vEnd)
                    {
                        break;
                    }
                 }
            }

        }
    }

    static QVector<vertex_smpt> A_Star(Graph& graph, int vBegin, int vEnd)
    {
        const int UNDEF = -1;

        QVector<QVector<int>> matrix = graph.toAdjacencyMatrix(compare);
        QList<vertex_smpt> pointers_V = graph.getVertexAsKeys().toList();
        QList<edge_smpt> pointers_E;
        qDebug() << matrix;
        std::vector<int> len(matrix.count(), UNDEF);
        QQueue<int> q;
        QVector<vertex_smpt> came_from(graph.getVertexAsKeys().count());
        QStack<edge_smpt> edges;
        QList <vertex_smpt> graphVertices = graph.getVertexAsKeys().toList();
        qSort(graphVertices.begin(), graphVertices.end(), compare);
        int V = pointers_V.count(); // Колличество вершин
        int E = pointers_E.count();//Колличество ребер
        QVector<int> dist(pointers_V.count());


        q.enqueue(vBegin);
        len[vBegin] = 0;
        while (true)
        {
            if (q.empty())
            {

                throw 1;
            }
            int current = q.dequeue();
            if (current == vEnd)
            {
                QList<vertex_smpt> result;
                result.append(graphVertices[vEnd]);
                while (!edges.empty())
                {

                    edge_smpt e = edges.pop();
                    if (graphVertices.indexOf(e->getVertex()) == vEnd)
                    {
                        vEnd = graphVertices.indexOf((*e).getStartVertex());

                        result.append(graphVertices[vEnd]);
                    }
                }

                return result.toVector();
            }
            for (int next = 0; next < matrix.count(); next++)
            {
                if (len[next] == UNDEF && matrix[current][next] > 0)
                {
                    q.enqueue(next);
                    len[next] = len[current] + 1;
                    Edge* e = new Edge();

                    e->setVertex(graphVertices[current], graphVertices[next]);
                    edges.push(edge_smpt(e));
                    for (int i = 1; i <= V - 1; i++)
                    {
                        for (int j = 0; j < E; j++)
                        {
                            int u = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getStartVertex());
                            int v = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getVertex());//берем конечную вершину
                            int weight = pointers_E[j]->getWeight();

                            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                                dist[v] = dist[u] + Evristika(graph, vBegin,vEnd);
                        }
                    }

                    if (current == vEnd)
                    {
                        break;
                    }
                 }
            }

        }
    }

    static QVector<vertex_smpt> A_Star_IrerativeDeepening(Graph& graph, int vBegin, int vEnd)
    {
        const int UNDEF = -1;

        QVector<QVector<int>> matrix = graph.toAdjacencyMatrix(compare);
        qDebug() << matrix;
        std::vector<int> len(matrix.count(), UNDEF);
        QQueue<int> q;
        QList<vertex_smpt> pointers_V = graph.getVertexAsKeys().toList();
        QList<edge_smpt> pointers_E;
        QStack<edge_smpt> edges;
        int V = pointers_V.count(); // Колличество вершин
        int E = pointers_E.count();//Колличество ребер
        QVector<int> dist(pointers_V.count());

        QList <vertex_smpt> graphVertices = graph.getVertexAsKeys().toList();
        qSort(graphVertices.begin(), graphVertices.end(), compare);

        q.enqueue(vBegin);
        len[vBegin] = 0;
        while (true)
        {
            if (q.empty())
            {

                throw 1;
            }
            int current = q.dequeue();
            if (current == vEnd)
            {

                QList<vertex_smpt> result;
                result.append(graphVertices[vEnd]);
                while (!edges.empty())
                {

                    edge_smpt e = edges.pop();
                    if (graphVertices.indexOf(e->getVertex()) == vEnd)
                    {
                        vEnd = graphVertices.indexOf((*e).getStartVertex());
                        qDebug() << "   <- " << graphVertices[vEnd]->getName();
                        result.append(graphVertices[vEnd]);
                    }
                }

                return result.toVector();
            }
            for (int next = 0; next < matrix.count(); next++)
            {
                if (len[next] == UNDEF && matrix[current][next] > 0)
                {
                    q.enqueue(next);
                    len[next] = len[current] + 1;
                    Edge* e = new Edge();
                    e->setVertex(graphVertices[current], graphVertices[next]);
                    edges.push(edge_smpt(e));
                    for (int i = 1; i <= V - 1; i++)
                    {
                        for (int j = 0; j < E; j++)
                        {
                            int u = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getStartVertex());
                            int v = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getVertex());//берем конечную вершину
                            int weight = pointers_E[j]->getWeight();

                            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                                dist[v] = dist[u] + Evristika(graph, vBegin,vEnd);
                        }
                    }

                    if (current == vEnd)
                    {
                        break;
                    }
                 }
            }

        }
    }


    static int Evristika(Graph &graph, int vBegin, int vNext)
    {

        QVector<QVector<int>> matrix = graph.toAdjacencyMatrix();
        QList<vertex_smpt> pointers_V = graph.getVertexAsKeys().toList();
        QList<edge_smpt> pointers_E;
        QVector<int> addition(matrix.count());
        QVector<int> pathSize(matrix.count());
        int countOf_Vertex = pointers_V.count();
        edge_smpt min_ed = nullptr;
        int result;
        int amount1= 1, amount2 = 1;
        int u = graph.getVertexAsKeys().toList().indexOf(pointers_E[vBegin]->getStartVertex());
        for (int i = 1; i < pathSize.count(); i++)
        {

        for(int j = 0;graph.getVertexAsKeys().count(); ++j){
            if(min_ed->getVertex()->getName() == min_ed->getWeight()){
                if(min_ed.get() == nullptr)
                {
                    amount1 = amount1*min_ed->getWeight();
                }
                else{
                    if(min_ed->getWeight() < min_ed->getWeight())
                        amount2 = amount2*min_ed->getWeight();
                }
            }
        }

        for(int i = 0; i < graph.getVertexAsKeys().count(); ++i)
            {
                if(min_ed->getVertex()->getName() == min_ed->getWeight() && min_ed->getVecSrc())
                {
                    if(min_ed.get() == nullptr)
                    {
                            amount1 = amount1*min_ed->getWeight();
                    }
                        else{
                if(min_ed->getWeight() < min_ed->getWeight())
                        amount2 = amount2*min_ed->getWeight();

                    }
                result = std::sqrt(amount1*amount1 + amount2*amount2);

            }
          }
        }
        return result;
    }








};
#endif // LAB2_H
