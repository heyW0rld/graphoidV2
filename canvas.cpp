#include "canvas.h"
#include <QDebug>
#include <QMouseEvent>
#include <math.h>
#include <QPainter>
#include "file.h"

//Вершина - настоящая вершина, нарисованная на полотне
//Фиктивная вершина - вершина, не нарисованная на полотне и
//задействованная для рисования анимации проведения ребра
//Ребро для анамации - его рисует пользователь до нужной вершины
//Основное ребро - ребро, уже отображенное на полотне


vertex_smpt checkVertex(const QSet<vertex_smpt> &s, const QPoint &p, int r);
int checkArrow(const QList<edge_smpt> &n, const QPoint &p, int r);
QPair<vertex_smpt, int> checkEdge(Graph &g, const QPoint &p, int r);

Canvas::Canvas(QWidget *parent) : QWidget(parent), chv(false, vertex_smpt()), chv_arrow(false, nullptr), \
    chv_edge(false, QPair<Vertex*, int>(nullptr, -1)) {}

//------------------------------!!!!---------------------------------
//Тут происходит вся отрисовка
void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

//    Создаём объект отрисовщика
    QPainter *painter = new QPainter(this);
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(0,0,((this->width())-1),((this->height())-1));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

//    отрисовка
    for(auto v : graph.getVertexAsKeys())
    {
         v->paint(painter);
         for(auto eg : graph[v])
            eg->paint(painter, EDGE_RADIUS);
    }
    delete painter;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{

    vertex_smpt check_ver = checkVertex(graph.getVertexAsKeys(), event->pos(), VER_RADIUS);
    QPair<vertex_smpt, int> eg_p = checkEdge(graph, event->pos(), EDGE_RADIUS);
//    по левой кнопке мыши передвигаем вершину или ребро
    if(event->button() == Qt::LeftButton){

//        ребро точно определяется через два параметра:
//        вершиной, от которой проведено, и индексом в QList
        if(eg_p.second != -1)
        {
            chv_edge.first = true;//помечаем ребро как активное
            chv_edge.second.first = eg_p.first;//кладем вершину от которой проведено активное ребро
            chv_edge.second.second = eg_p.second;//кладем индекс в QList
        }

//        проверяем, есть ли тут вершина
//        если есть помечаем как активную
        else if(check_ver)
        {
            check_ver->getPoint();
            chv.first = true;
            chv.second = check_ver;
        }
    }

    if(event->button() == Qt::RightButton){
        if(eg_p.second != -1){
            chv_edge.second = eg_p;
            QMenu *menu = new QMenu(this);
            menu->addAction("Удалить ребро");
            menu->addAction("Задать вес");
            connect(menu,
                    SIGNAL(triggered(QAction*)),
                    SLOT(menuEdge(QAction*))
                    );
            menu->exec(this->mapToGlobal(event->pos()));
        }
        else if(check_ver){
            chv.second = check_ver;
            QMenu *menu = new QMenu(this);
//            menu->addAction("Изменение имени вершины");
            menu->addAction("Удалить вершину");
            menu->addAction("Создать петлю");
            connect(menu,
                    SIGNAL(triggered(QAction*)),
                    SLOT(menuVertex(QAction*))
                    );
            menu->exec(this->mapToGlobal(event->pos()));
        }
    }
}

void Canvas::menuVertex(QAction *action)
{
    if(action->text() == "Удалить вершину")
    {
        undoPush();
        graph.remove(chv.second);

        if(graph.getVertexAsKeys().size() == 0)
            count = 0;
//        Испускается сигнал удаления вершины
        emit changeGraph();

        repaint();
    }
    else if(action->text() == "Создать петлю")
    {
           undoPush();
           auto vertex_data = graph[chv.second];
           edge_smpt edge = edge_smpt(new Edge(chv.second, chv.second, 1));
           edge->setPoint(chv.second->getPoint().x(), chv.second->getPoint().y() - VER_RADIUS > 0
                          ? chv.second->getPoint().y() - VER_RADIUS : chv.second->getPoint().y() + VER_RADIUS);
           vertex_data.append(edge);
           graph[chv.second] = vertex_data;

//           Испускается сигнал добавления петли
           emit changeGraph();

           repaint();
     }
    else
    {
//        установка нового имени вершины
    }
}

void Canvas::menuEdge(QAction *action)
{
   undoPush();
   if(action->text() == "Удалить ребро")
   {
         graph[chv_edge.second.first].removeAt(chv_edge.second.second);
   }
   else if(action->text() == "Задать вес")
   {
//         qDebug() <<graph[chv_edge.second.first][chv_edge.second.second]->getWeight();
         bool ok;
         QString text = QInputDialog::getText(this, tr("Вес ребра"),
                                              tr("Вес ребра:"), QLineEdit::Normal,
                                              "", &ok);
         if(ok)
             graph[chv_edge.second.first][chv_edge.second.second]->setWeight(text.toInt());
//         qDebug() <<graph[chv_edge.second.first][chv_edge.second.second]->getWeight();
    }
    emit changeGraph();
    repaint();
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

//    Проверяем, активно ли сейчас основное ребро
    if(chv_edge.first)
    {
//        получаем по ключу chv_edge.second.first список QList ребер, исходящих из этой вершины
//        chv_edge.second.second - по данному индексу из QList получаем нужное нам ребро
//        graph[ключ] -> QList(), QList[индекс] -> Edge()
        graph[chv_edge.second.first][chv_edge.second.second]->setPoint(QPoint(event->x(), event->y()));
//        перерисовка
        repaint();
    }

//    проверяем, активна ли сейчас вершина
    if(chv.first){
        chv.second->setPoint(event->pos());
//        перерисовка
        repaint();
    }

//    проверяем, активно ли сейчас ребро для анимации
    if(chv_arrow.first){
//        если активно, изменяем координаты фиктивной вершины
//        ребро для анимации лежит последним

//        Вот тут была ошибка, но это не плохо, так как
//        альтернативный вариант
//        graph[chv_arrow.second].back().setPoint(event->pos());

//        Вот как я хотел
        graph[chv_arrow.second].back()->getVertex()->setPoint(event->pos());

//        перерисовка
        repaint();
    }

}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{

    Q_UNUSED(event)

    if(event->button() == Qt::LeftButton){
//        Добавляем ребро в общую структуру
        if(chv_arrow.first)
        {
//            мы добавили фиктивную вершину, чтобы сделать анимацию отрисовки ребра
//            ------------------теперь удалим ее
            auto vertex_data = graph[chv_arrow.second];

            vertex_data.pop_back();//ребро для анимации было добавлено последним

            vertex_smpt check_ver = checkVertex(graph.getVertexAsKeys(), event->pos(), VER_RADIUS);

//            Если ребро довели до вершины
//            если вершина не та же самая(петли создаются через контекстное меню)
            if(chv_arrow.second != check_ver)
            {

//                ----------------------!!!!!---------------------------
//                Здесь происходит создание узлов
//                у нас есть две вершины - chv_arraw.second и check_ver - соответственно откуда и куда
                if(check_ver){
//                    добаляем ребро в общую структуру graph
                    edge_smpt edge = edge_smpt(new Edge(chv_arrow.second, check_ver, 1));
                    if(modeOrient == false)
                        edge->setVecSrc(true);
                    edge->setVecEnd(true);
                    vertex_data.append(edge);
                }
                else
                    undoStack.pop();
            }
            else
            {
                undoStack.pop();
            }

//            либо добавили ребро, либо нет и вернули данные обратно
            graph[chv_arrow.second] = vertex_data;

            //!!!---- переделать по возможности
            if(check_ver){
//                Сигнал добавления ребра
                emit changeGraph();
            }

//            перерисовавыем, чтобы изменения вступили в силу
            repaint();
        }
//        если отпускается вершина(проверка на выход за пределы)
        if(chv.first){
            int x = event->x();
            int y = event->y();
            if(event->x() < 0)
                x = 0;
            else if(event->x() > this->width())
                x = this->width();
            if(event->y() < 0)
                y = 0;
            else if(event->y() > this->height())
                y = this->height();
            chv.second->setPoint(QPoint(x, y));
            repaint();
        }
//        если отпускается ребро(проверка на выход за пределы)
        if(chv_edge.first){
            int x = event->x();
            int y = event->y();
            if(event->x() < 0)
                x = EDGE_RADIUS;
            else if(event->x() > this->width())
                x = this->width() - EDGE_RADIUS;
            if(event->y() < 0)
                y = EDGE_RADIUS;
            else if(event->y() > this->height())
                y = this->height() - EDGE_RADIUS;
            graph[chv_edge.second.first][chv_edge.second.second]->setPoint(QPoint(x, y));
            repaint();
        }

//        Делаем вершины и ребра не активными
        chv.first = false;
        chv_arrow.first = false;
        chv_edge.first = false;
    }

}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
//    тут задействована только левая кнопка мыши
//    Происходит обработка двух событий:
//    1)рисуется вершина(кликнуть два раза по пустому месту)
//    2)рисуется ребро от данной вершины(если кликнуть два раза на существующую)

    if(event->button() == Qt::LeftButton)
    {
        undoPush();
//        проверяем есть ли тут вершина
        vertex_smpt check_ver = checkVertex(graph.getVertexAsKeys(), event->pos(), VER_RADIUS);

//        ------------------------!!!!------------------------
//        Отрисовка вершины(рисуем, если в данном месте нет уже нарисованной вершины)
//        То есть в указателе будет nullptr
        if(!check_ver){

            for(auto ver: graph.getVertexAsKeys()){
                if(ver->getName() =="Ver" + QString::number(count)){
                    count++;
                }
            }
            vertex_smpt v(new Vertex("Ver" + QString::number(count), event->pos()));
            v->setColor(Qt::green);
            graph.insert(v, QList<edge_smpt>());
            count++;
//            чтобы можно было сразу перетаскивать помечаем как активную
            chv.first = true;
            chv.second = v;

//            Испускается сигнал добавления вершины
            emit changeGraph();
//            перерисовка
            repaint();
        }

//        ------------------------!!!!------------------------
//        Если на данном месте есть вершина, начинается отрисовка ребра
//        тут создается фиктивная вершина!!!
        else {
            chv_arrow.first = true;
            chv_arrow.second = check_ver;

//            добавляем ребро с мнимой вершиной
            edge_smpt edge(new Edge(check_ver->getPoint().x(), check_ver->getPoint().y(), vertex_smpt(new Vertex("", event->pos())), 0));
            graph[check_ver].append(edge);
//            перерисовка
            repaint();
        }

    }
}

void Canvas::setGraph(const Graph &g)
{
    graph = g;
    count = g.getVertexAsKeys().size();
}

void Canvas::setModeOrient(bool value)
{
    modeOrient = value;
}

Graph& Canvas::getGraph()
{
    return graph;
}

void Canvas::clear()
{
    if(!getGraph().getVertexAsKeys().isEmpty())
        undoPush();
    getGraph().clear();
    count = 0;
}

Canvas::~Canvas()
{
}

//-------------------!!!!!!!!!----------------------------
//Проверка на то, указывает ли сейчас мышка на одну из вершин
vertex_smpt checkVertex(const QSet<vertex_smpt> &s, const QPoint &p, int r)
{
    for(auto ver : s){
        double res = pow(ver->getPoint().x() - p.x(), 2) + pow(ver->getPoint().y() - p.y(), 2) * 0.9;
        if(pow(res, 0.5) < r)
            return ver;
    }
    return nullptr;
}
//функция проверки одного списка ребер на то, попал ли курсор на ребро или нет
//вся математика тут
int checkArrow(const QList<edge_smpt> &n, const QPoint &p, int r)
{
    for(auto ed : n){
        double res = pow(ed->getPoint().x() - p.x(), 2) + pow(ed->getPoint().y() - p.y(), 2) * 0.9;
        if(pow(res, 0.5) < r)
            return n.indexOf(ed);
    }
    return -1;
}
//проверка всего графа на попадание на ребро
//вся математика в предыдущей функции
QPair<vertex_smpt, int> checkEdge(Graph &g, const QPoint &p, int r)
{
    for(auto ver : g.getVertexAsKeys()){
        int eg_index = checkArrow(g[ver], p, r);
        if(eg_index != -1)
            return QPair<vertex_smpt, int>(ver, eg_index);
    }
    return QPair<vertex_smpt, int>(nullptr, -1);
}

void Canvas::undo()
{
    if(undoStack.size())
    {
        redoPush();
        graph = undoStack.pop();
        repaint();
    }
}

void Canvas::undoPush()
{
    if(undoStack.size() == 10)
        undoStack.pop_front();
    redoStack.clear();
    undoStack.push(graph);
}

void Canvas::redo()
{
    if(redoStack.size())
    {
        undoStack.push(graph);
        graph = redoStack.pop();
        repaint();
    }
}


void Canvas::redoPush()
{
    if(redoStack.size() == 10)
        redoStack.pop_front();

    redoStack.push(graph);
}
