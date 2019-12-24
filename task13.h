#ifndef TASK13_H
#define TASK13_H

#include <QDebug>
#include "lab3.h"
#include "graph.h"
#include <QQueue>
#include <QVector>
namespace task13
{
QVector<int> Cycle_wideWalk(QVector<QVector<int>> g, int s)
{
    QVector<int> cycle;
    QQueue<int> q;
    q.push_back(s);
    QVector<bool> used (g.size());
    QVector<int> p (g.size());
    used[s] = true;
    p[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();

        for (int i=0; i < g.size(); ++i) {
            if(!g[v][i]) continue;

            if (!used[i])
            {
                used[i] = true;
                q.push_back(i);
                p[i] = v;
            }
            else if(i != p[v] && used[i])
            {
                for (; v!=-1; v=p[v])
                    cycle.push_back(v);
                for (v=i; v!=-1; v=p[v])
                    cycle.push_back(v);

                return cycle;
            }

        }
    }

    return cycle;
}

QVector<int> minCycle(QVector<QVector<int>> g)
{
    QVector<int> ans;
    ans = Cycle_wideWalk(g, 0);
    int minCyc = ans.size();
    for(int i = 1; i < g.size(); i++)
    {
        if(Cycle_wideWalk(g, i).size() < minCyc)
        {
            ans = Cycle_wideWalk(g, i);
            minCyc = ans.size();
            qDebug() << i;
        }
    }

    return ans;
}

QVector<int> centerVer(Graph graph)
{
    QVector<int> answer;
    QVector<QVector<int>> matrix = lab3::FloydWarshall(graph, 0);

    QList<vertex_smpt> vertices = graph.getVertexAsKeys().toList();
    QMap<vertex_smpt, int> result;

    for(int i = 0; i < matrix.count(); i++)
    {
        int eccentricity = *std::max_element(matrix[i].constBegin(), matrix[i].constEnd());
        if (eccentricity == 2147483644 || eccentricity == 0)
        {
            continue;
        }
        result.insert(vertices[i], eccentricity);
    }

    QVector<int> values = result.values().toVector();

    int radius = *std::min_element(values.constBegin(), values.constEnd());

    for(int i = 0; i < matrix.count(); i++)
    {
        int eccentricity = *std::max_element(matrix[i].constBegin(), matrix[i].constEnd());
        if (eccentricity == 2147483644 || eccentricity == 0)
        {
            continue;
        }

        if(eccentricity == radius)
            answer.append(i);
    }

    return answer;
}

int depth(Graph graph, int i)
{

    QVector<QVector<int>> matrix = lab3::FloydWarshall(graph, 0);

    int eccentricity = *std::max_element(matrix[i].constBegin(), matrix[i].constEnd());

    return eccentricity;
}

QVector<int> parent, degree;
QVector<QVector<int>> g;

void dfs (int v) {
    for (size_t i=0; i<g.size(); ++i) {
        if(!g[v][i]) continue;
        int to = i;
        if (to != parent[v]) {
            parent[to] = v;
            dfs (to);
        }
    }
}
QVector<int> Prufer(QVector<QVector<int>> graph)
{
        QVector<int> vec1(graph.size()), vec2(graph.size());
        parent = vec1;
        degree = vec2;
        g = graph;

        parent[graph.size()-1] = -1;
        dfs (graph.size()-1);

        int ptr = -1;
        for (int i=0; i<graph.size(); ++i) {
            for(auto it : graph[i])
                if(it) degree[i]++;
            if (degree[i] == 1 && ptr == -1)
                ptr = i;
        }

        QVector<int> result;
        int leaf = ptr;
        for (int iter=0; iter<graph.size()-2; ++iter) {
            int next = parent[leaf];
            result.push_back (next);
            --degree[next];
            if (degree[next] == 1 && next < ptr)
                leaf = next;
            else {
                ++ptr;
                while (ptr<graph.size() && degree[ptr] != 1)
                    ++ptr;
                leaf = ptr;
            }
        }
        return result;
    }
}








#endif // TASK13_H
