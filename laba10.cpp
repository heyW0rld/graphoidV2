#include "lab10.h"
#include "graph.h"
//#include "edge.h"
#include <QVector>
//#include <QQueue>
//#include <QStack>
#include <QDebug>
//#include <algorithm>
//#include <qalgorithms.h>
//#include "lab3.h"
//#include "graph.h"
//#include "vertex.h"
//#include "edge.h"
//#include"saving.h"
//#include "mainwindow.h"
//#include "saving.h"
#include <string>
#include <QList>
#include <QString>
#include <QMessageBox>
//#include <QObject>
//#include "task.h"


// Сортировка вектора листов по возрастанию элементов c индексом num в листах
void sortVectAscending(QVector<QList<int>> &vector, int num) {
    for (int i = 0; i < vector.size() - 1; ++i) {
        for (int j = 0; j < vector.size() - i - 1; ++j)
            if (vector[j].at(num) < vector[j+1].at(num))
                std::swap(vector[j], vector[j+1]);
    }
}


// Сортировка вектора листов по убыванию элементов c индексом num в листах
void sortVectDescending(QVector<QList<int>> &vector, int num) {
    for (int i = 0; i < vector.size() - 1; ++i) {
        for (int j = 0; j < vector.size() - i - 1; ++j)
            if (vector[j].at(num) > vector[j+1].at(num))
                std::swap(vector[j], vector[j+1]);
    }
}


// Получает из вектора листов лист первых элементов (если нумерация с 0)
QList<int> getValues(QVector<QList<int>> vector) {
    QList<int> v;
    for (const QList<int> &el: vector)
        v.append(el[1]);

    return v;
}


// Для построения строки с промежуточным результатом работы редукционного алгоритма
QString buildString(QVector<QList<int>> vect2) {
    sortVectDescending(vect2, 0);
    QString str = "";
    for (int i = 0; i < vect2.size(); ++i) {
        str += QString::number(vect2[i][1]) + " ";
    }

    return str;
}


QList<QList<int>> lab10(QVector<int> &vect) {
    bool sov;

    QVector<QList<int>> vect2(vect.size());
    for (int i = 0; i < vect2.size(); ++i) {
        vect2[i] = QList<int>{i+1, vect.at(i)};
    }
//    qDebug() << vect2;

    QVector<QList<int>> tmp = vect2;
    if (tmp == vect2)
        sov = true;
    else
        sov = false;

    // сортирую пузырьком списки в векторe по 1 элементу (если считать с нуля)
    sortVectAscending(vect2, 1);
    //qDebug() << vect2;

    QList<QList<int>> edges; // я так понимаю список смежных вершин
    QList<QList<int>> bases;


    while (getValues(vect2).size() != getValues(vect2).count(0)) {
        //qDebug() << "get values = " << getValues(vect2);
        //qDebug() << vect2;
        qDebug() << buildString(vect2);
        QMessageBox msgBox;
        msgBox.setText("работа алгоритма - " +buildString(vect2));
        msgBox.exec();

        int i = 1;
        while ((vect2[0][1] != 0) && (i < vect2.size())) {
            if (vect2[i][1] == 0) {
                sov = false;
                qDebug() << "Граф не совершенный";
                return {}; // пустой лист, если чо
            }

            vect2[i][1] -= 1;
            vect2[0][1] -= 1;

            edges.append(QList<int>{vect2[0][0], vect2[i][0]}); // .push_back() ?

            i++;
        }

        if (vect2[0][1] != 0) {
            sov = false;
            qDebug() << "Граф не совершенный";
            return {};
        }

        sortVectAscending(vect2, 1);
    }

    if (sov)
        qDebug() << "Граф совершенный";
    else
        qDebug() << "Граф не совершенный";

    return edges;
}


// Строим базу
QList<QList<int>> graphBase(QVector<QVector<int>> matrix) {
    int n = matrix.size();
    QList<QList<int>> base;

    for (int i = 0; i < n - 1; ++i) {
        int b = -1;
        for (int j = i + 1; j < n; ++j)
            if (matrix[i][j] > 0) {
                if (b == -1 && j > i + 1)
                    return {};
                else
                    b = j;
            }

        if (b == -1)
            return base;

        if (base.size() != 0) {
            QList<int> prev_b = base[base.size()-1];
            if (prev_b[1] < b + 1)
                return {};
            else
                if (prev_b[1] == b + 1) prev_b[0] = i + 1;
            else
                    base.append(QList<int>{i + 1, b + 1});
        }
        else
            base.append(QList<int>{i + 1, b + 1});
    }

    return base;
}





Graph laba10(QList<int> powerList){
    QVector<int>vectorStepeney = powerList.toVector();
//    QVector<int> vectorSepeney = VectorStepeney(graph);
//    QVector<int> vect = {6 4 4 3 3 2 2};
    int n = vectorStepeney.size();


    //     Список смежных вершин
        QList<QList<int>> edges = lab10(vectorStepeney);

        if (edges.size() == 0){
            QMessageBox msgBox;
            msgBox.setText("Ошибка в записи.");
            msgBox.exec();
            qDebug() << "Граф невозможно построить";
        }
        //else строим

    //    Конечный результат работы алгоритма
        qDebug() << edges;
        Graph graph;
        for(int i = 1; i<=n;++i){
        vertex_smpt v1(new Vertex("Ver" + QString::number(i), (1+i)%200+ rand()%200,(1+i)%200+rand()%200));
        v1->setColor(Qt::green);
        graph.insert(v1, QList<edge_smpt>());
        }
        auto all_vertex = graph.getVertexAsKeys();
        for (QList<int> edge: edges) {
            for(auto v1:all_vertex){
                for(auto v2:all_vertex){
                    QString s1 = "Ver" + QString::number(edge[0]);
                    QString s2 = "Ver" + QString::number(edge[1]);
                    if(v1->getName() == s1 && v2->getName() == s2){
                    edge_smpt edge1 = edge_smpt(new Edge(v1, v2, 1));
                    graph[v1].append(edge1);
                    edge_smpt edge2 = edge_smpt(new Edge(v2, v1, 1));
                    graph[v2].append(edge2);
                    }
                }
            }
        }

    //     Cоздаём квадратную матрицу нулей
        QVector<QVector<int>> matrix(n, QVector<int> (n, 0));

    //    Строим матрицу из списка смежных вершин
        for (QList<int> edge: edges) {
            matrix[edge[0] - 1][edge[1] - 1] = 1;
            matrix[edge[1] - 1][edge[0] - 1] = 1;
        }
//        qDebug()<<matrix;
    //    Строим базу
        QString baza;
        QList<QList<int>> base = graphBase(matrix);
        for (QList<int> edge: base) {
            baza+="( ";
            baza+= QString::number(edge[0]);
            baza+=",";
//            for(int edg:edge){
//                baza
//            }

            baza+=QString::number(edge[1]);
            baza+=")";
        }

    //     Если база есть, то граф экстремальный
        if (base.size() != 0) {
            QMessageBox msgBox;
            msgBox.setText("Граф экстремальный  - База -" + baza);
            msgBox.exec();
            qDebug() << "Граф экстремальный";
            qDebug() << "База:" << base;
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Граф не экстремальный  ");
            msgBox.exec();
        }
    return graph;
}
