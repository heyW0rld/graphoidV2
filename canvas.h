#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMenu>
#include <QStack>
#include <QPainter>
#include <QMouseEvent>
#include <QInputDialog>
#include <math.h>
#include "graph.h"
#include "edge.h"

/*Приложение V 1.1
 * Умеет:
 * 1)рисовать вершины (двойной щелчок по свободному месту)
 * 2)двигать вершины (щелкнуть по вершине и тащить)
 * Идеи:
 * 1)сделать ver_radius как static параметр класса отрисовки
 * 2)сделать общую структуру с условиями(как вектор условий)
 * По сравнению с предыдущей версией:
 * 1)методы рисования добавлены в классы, которые отрисовываются
 */

using CheckVertex = QPair<bool, vertex_smpt>;

using pair_node = QPair<bool, QPair<vertex_smpt, int>>;

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void setGraph(const Graph &g);
    Graph& getGraph();
    void undo();
    void undoPush();
    void redo();
    void redoPush();
    void clear();
    void setModeOrient(bool value);

signals:
    void changeGraph();

public slots:
    void menuVertex(QAction *action);
    void menuEdge(QAction *action);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Graph graph;//хранит полную информацию о графе
    int count = 0;//счетчик вершин
    CheckVertex chv;//нужно для отрисовки вершины
    CheckVertex chv_arrow;//нужно для отрисовки ребра
    pair_node chv_edge;
    QStack<Graph> undoStack, redoStack;
    bool modeOrient;

};
#endif // CANVAS_H
