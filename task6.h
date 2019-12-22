#ifndef TASK6_H
#define TASK6_H
#include "graph.h"
#include <QDebug>

namespace  task6{
QVector<QVector<int>> graph, graphT;

int timer;
QVector<int> tin, fup;
int count_bridges, count_cutpoint;
QVector<bool> used;
QVector<int> comp;
QVector<int> order, component;

void comps_dfs (int v) {
    used[v] = true;
    comp.push_back (v);
    for (size_t i=0; i<graph[v].size(); ++i) {
        int to;
        if(graph[v][i]) to = i;
        else continue;
        if (! used[to])
            comps_dfs (to);
    }
}

QVector<QVector<int>> find_comps(QVector<QVector<int>> g)
{
    QVector<QVector<int>> res;
    if(!g.size()) return res;

    graph = g;
    used.clear();
    for (int i=0; i < g.size(); i++)
        used.push_back(false);

    for (int i=0; i<graph.size(); ++i)
        if (! used[i]) {
            comp.clear();
            comps_dfs(i);
            res.push_back(comp);
        }

    return res;
}

void cutpoint_dfs (int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (size_t i=0; i < graph[v].size(); ++i) {
        int to;
        if(graph[v][i]) to = i;
        else continue;
        if (to == p)  continue;
        if (used[to])
            fup[v] = fup[v] > tin[to] ? tin[to] : fup[v];
        else {
            cutpoint_dfs (to, v);
            fup[v] = fup[v] > fup[to] ? fup[to] : fup[v];
            if (fup[to] >= tin[v] && p != -1)
                count_cutpoint++;
            ++children;
        }
    }
    if (p == -1 && children > 1)
        count_cutpoint++;
}

void bridgets_dfs (int v, int p = -1)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i=0; i < graph[v].size(); ++i) {
        int to;
        if(graph[v][i]) to = i;
        else continue;
        if (to == p)  continue;
        if (used[to])
            fup[v] = fup[v] > tin[to] ? tin[to] : fup[v];
        else {
            bridgets_dfs(to, v);
            fup[v] = fup[v] > fup[to] ? fup[to] : fup[v];
            if (fup[to] > tin[v])
                count_bridges++;

        }
    }
}


int find_bridges(QVector<QVector<int>> g) {

    if(!g.size()) return 0;

    count_bridges = 0;
    graph = g;
    timer = 0;

    used.clear();
    tin.clear();
    fup.clear();

    for (int i=0; i < g.size(); i++)
    {
        used.push_back(false);
        tin.push_back(0);
        fup.push_back(0);
    }

    for (int i=0; i < g.size(); i++)
        if (!used[i])
            bridgets_dfs (i);

    return count_bridges;
}

int find_cutpoint(QVector<QVector<int>> g) {

    if(!g.size()) return 0;

    count_cutpoint = 0;
    graph = g;
    timer = 0;

    used.clear();
    tin.clear();
    fup.clear();

    for (int i=0; i < g.size(); i++)
    {
        used.push_back(false);
        tin.push_back(0);
        fup.push_back(0);
    }

    cutpoint_dfs(0);

    return count_cutpoint;
}

void strongcomp_dfs1 (int v)
{
    used[v] = true;
    for (size_t i=0; i<graph[v].size(); ++i)
    {
            if(graph[v][i] && !used[i])
                strongcomp_dfs1(i);
    }
    order.push_back (v);
}

void strongcomp_dfs2 (int v)
{
    used[v] = true;
    component.push_back (v);
    for (size_t i=0; i<graphT[v].size(); ++i)
    {
            if(graphT[v][i] && !used[i])
                    strongcomp_dfs2(i);
    }
}

int strongComp(QVector<QVector<int>> g)
{
    int count_comp = 0;
    graph = g;
    used.clear();
    order.clear();
    graphT = graph;
    for(int i = 0; i < graph.size(); ++i)
        for(int j = 0; j < graph.size(); ++j)
            graphT[j][i] = graph[i][j];

    for (int i=0; i < g.size(); i++)
        used.push_back(false);

    for (int i=0; i<g.size(); ++i)
        if (!used[i])
            strongcomp_dfs1(i);

    used.clear();
    for (int i=0; i < g.size(); i++)
        used.push_back(false);

    for (int i=0; i<graph.size(); ++i) {
        int v = order[graph.size()-1-i];
        if (!used[v]) {
            strongcomp_dfs2(v);
            count_comp++;
            component.clear();
        }
    }

    qDebug() << count_comp;
    return count_comp;
}

        bool isGraphOrient(QVector<QVector<int>> g)
        {
            for(int i = 0; i < g.size(); ++i)
                for(int j = 0; j < g.size(); ++j)
                    if(g[i][j] != g[j][i]) return true;

            return false;
        }
    }
#endif // TASK6_H
