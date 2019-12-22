#ifndef LAB3_H
#define LAB3_H
#include "graph.h"
#include "edge.h"
#include <QVector>
#include <QQueue>
#include <QStack>
#include <QDebug>
#include<qalgorithms.h>
#include<math.h>
#include "mainwindow.h"
#include"task.h"
#include"saving.h"
#include <string>
#include <QMessageBox>
#include <QObject>
#include "task.h"




class lab3
{
public:

    static QVector<QVector<int>> FloydWarshall(Graph& graph, int src)
    {
         const int INF = 2147483644;
         QVector<QVector<int>> matrix = graph.toAdjacencyMatrix(compare);
         QVector<int> pathSize(matrix.count());
         QVector<int> allPath(matrix.count());


          for(int i = 0; i < matrix.count(); i++)
          {
              for(int j = 0; j < matrix.count(); j++)
              {
                  if(matrix[i][j] <= 0)
                  {
                      matrix[i][j] = INF;
                  }
              }
          }
         for(int k = 0; k < matrix.count(); ++k) {
                 for(int i = 0; i < matrix.count(); ++i) {
                     for(int j = 0; j < matrix.count(); ++j) {
                         //Новое значение ребра равно минимальному между старым
                         //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                         if (matrix[i][k] < INF && matrix[k][j] < INF
                                 && matrix[i][k] > 0 && matrix[k][j] > 0 && matrix[i][j] > 0)
                         matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                     }
                 }
             }
         for(int i = 0; i < matrix.count(); i++)
         {
             matrix[i][i] = 0;
             for(int j = 0; j < matrix[i].count(); j++)
             {
                 qDebug() << matrix[i][j] << " " ;

             }
             qDebug() << endl;
         }
         allPath = Dijkstra(graph, src);
         for(int i = 0; i < matrix.count(); ++i)
         {
             matrix[i][i] = 0;
             for(int j =0; j< matrix.count(); ++j)
             {
                 pathSize[j] = matrix[src][j];
             }
         }

//         for(int i = 0; i < pathSize.count(); ++i)
//         {
//             qDebug() << "Size path from vertex " << src << pathSize[i] << endl;
//         }

//         QString additionStr = "";
//         for(int i = 0; i < pathSize.count(); i++)
//         {

//             additionStr.append(QString::number(allPath[i]));
//             additionStr.append(" ");
//         }

//         QMessageBox::about(nullptr, "Результат:", "Вектор расстояния: " + additionStr);
//         QMessageBox msgBox;
//         msgBox.setIcon(QMessageBox::Question);
//         msgBox.setTextFormat(Qt::RichText);
//         //msgBox.setText("Все несохраненные данные будут утеряны!");
//         msgBox.setInformativeText("Желаете сохранить результат?");
//         QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
//         QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
//         msgBox.setDefaultButton(yesButton);
//         msgBox.exec();

//         if (msgBox.clickedButton() == yesButton)
//         {
//             //QVector<QVector<QString>> vec;
//             QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
//             Save_Result_Path(savefile, allPath);
//         }
//         else if (msgBox.clickedButton() == noButton)
//         {

//         }

         return matrix;
     }


    static QVector<int> Dijkstra(Graph &graph, int vBegin)
    {

        QVector<QVector<int>> matrix = graph.toAdjacencyMatrix();
        QVector<int> distance(matrix.count()); // минимальное расстояние
        QVector<int> visitedVertex(matrix.count());//посещенные вершины
        int temp, minIndex, min;
        QList<vertex_smpt> V = graph.getVertexAsKeys().toList();
        int countOfVertex = V.count();

        for(int i = 0; i < matrix.count(); i++)
        {
            distance[i] = 100000;
            visitedVertex[i] = 1;
        }

        distance[vBegin] = 0;

        //Шаг Алгоритма
        do{
           minIndex = 100000;
           min = 100000;

           for(int i = 0; i < matrix.count(); i++)
           {
               if((visitedVertex[i] == 1) && (distance[i] < min))
               {
                   min = distance[i];
                   minIndex = i;
               }
           }

           if(minIndex != 100000)
           {
               for(int i = 0; i < matrix.count(); i++)
               {
                   if(matrix[minIndex][i] > 0)
                   {
                       temp = min + matrix[minIndex][i];
                       if(temp < distance[i])
                       {
                           distance[i] = temp;
                       }
                   }
               }
               visitedVertex[minIndex] = 0;
           }
        } while(minIndex < 100000);

        for(int j = 0; j < matrix.count(); j++)
        {
            qDebug() << distance[j] << " ";

        }



        return distance;
    }



    static bool BellmanFord(Graph &graph, int src)
    {


        //Метод получения матрицы смежности отсортерованная
        QVector<QVector<int>> matrix = graph.toAdjacencyMatrix();
        QList<vertex_smpt> pointers_V = graph.getVertexAsKeys().toList();
        QList<edge_smpt> pointers_E;
        QVector<int> addition(matrix.count());
        QVector<int> pathSize(matrix.count());
        addition = Dijkstra(graph, src);
        pathSize = addition;


       if(src > 0)
       {
        for(auto ver : graph.getVertexAsKeys())
            for(auto ed : graph[ver])
                pointers_E.append(ed);
        int V = pointers_V.count(); // Колличество вершин
        int E = pointers_E.count();//Колличество ребер
        QVector<int> dist(pointers_V.count());



            // Step 1: Initialize distances from src to all other vertices
            // as INFINITE
            for (int i = 0; i < V; i++)
                dist[i] = INT_MAX;
            dist[src] = 0;

            for(int i = 0; i < pathSize.count(); ++i)
            {
                qDebug() << "PathBellman" << pathSize[i]<< endl;
            }
             if(matrix.count() > 0)
           {
            // Step 2: Relax all edges |V| - 1 times. A simple shortest
            // path from src to any other vertex can have at-most |V| - 1
            // edges
            for (int i = 1; i <= V - 1; i++)
            {
                for (int j = 0; j < E; j++)
                {
                    int u = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getStartVertex());
                    int v = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getVertex());//берем конечную вершину
                    int weight = pointers_E[j]->getWeight();

                    if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                        dist[v] = dist[u] + weight;
                }
            }



            // Step 3: check for negative-weight cycles.  The above step
            // guarantees shortest distances if graph doesn't contain
            // negative weight cycle.  If we get a shorter path, then there
            // is a cycle.
            for (int i = 0; i < E; i++)
            {
                int u = graph.getVertexAsKeys().toList().indexOf(pointers_E[i]->getStartVertex());
                int v = graph.getVertexAsKeys().toList().indexOf(pointers_E[i]->getVertex());//берем конечную вершину
                int weight = pointers_E[i]->getWeight();
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    qDebug() << "Graph contains negative weight cycle" <<endl;
                    //return  ; // If negative cycle is detected, simply return
                }
            }



            for(int  i = 0; i < matrix.count(); i++)
            {
                qDebug() << addition[i] << " " ;
            }

            QString additionStr = "";

            for(int i = 0; i < pathSize.count(); i++)
            {

                additionStr.append(QString::number(pathSize[i]));
                additionStr.append(" ");
            }

            QMessageBox::about(nullptr, "Результат:", "Вектор расстояния: " + additionStr);

            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setTextFormat(Qt::RichText);
            //msgBox.setText("Все несохраненные данные будут утеряны!");
            msgBox.setInformativeText("Желаете сохранить результат?");
            QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
            QPushButton *noButton = msgBox.addButton(QObject::tr("нет"), QMessageBox::ActionRole);

            msgBox.setDefaultButton(yesButton);
            msgBox.exec();

            if (msgBox.clickedButton() == yesButton)
            {

                QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
                Save_Result_Path(savefile, pathSize);
            }
            else if (msgBox.clickedButton() == noButton)
            {

            }
              }
             return true;
       } else
       {
           return false;
         }

        }

    static QVector<int> Jonson(Graph &graph, int vBegin)
    {
        QVector<QVector<int>> matrix = graph.toAdjacencyMatrix();
        QList<vertex_smpt> pointers_V = graph.getVertexAsKeys().toList();
        QList<edge_smpt> pointers_E;
        QVector<int> addition(matrix.count());
        QVector<int> pathSize(matrix.count());
        pathSize = Dijkstra(graph, vBegin);


        if(!BellmanFord(graph, vBegin))
        {



            for(auto ver : graph.getVertexAsKeys())
                for(auto ed : graph[ver])
                    pointers_E.append(ed);
            int V = pointers_V.count();
            int E = pointers_E.count();
            QVector<int> dist(pointers_V.count());


                for (int i = 0; i < V; i++)
                    dist[i] = INT_MAX;
                dist[vBegin] = 0;


                 if(matrix.count() > 0)
               {

                for (int i = 1; i <= V - 1; i++)
                {
                    for (int j = 0; j < E; j++)
                    {
                        int u = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getStartVertex());
                        int v = graph.getVertexAsKeys().toList().indexOf(pointers_E[j]->getVertex());
                        int weight = pointers_E[j]->getWeight();

                        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                            dist[v] = dist[u] + weight;
                    }
                }


                for (int i = 0; i < E; i++)
                {
                    int u = graph.getVertexAsKeys().toList().indexOf(pointers_E[i]->getStartVertex());
                    int v = graph.getVertexAsKeys().toList().indexOf(pointers_E[i]->getVertex());
                    int weight = pointers_E[i]->getWeight();
                }

                QString additionStr = "";

                for(int i = 0; i < pathSize.count(); i++)
                {

                    additionStr.append(QString::number(pathSize[i]));
                    additionStr.append(" ");
                }

                QMessageBox::about(nullptr, "Результат:", "Вектор расстояния: " + additionStr);

                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setTextFormat(Qt::RichText);
                //msgBox.setText("Все несохраненные данные будут утеряны!");
                msgBox.setInformativeText("Желаете сохранить результат?");
                QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
                QPushButton *noButton = msgBox.addButton(QObject::tr("нет"), QMessageBox::ActionRole);

                msgBox.setDefaultButton(yesButton);
                msgBox.exec();

                if (msgBox.clickedButton() == yesButton)
                {

                    QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
                    Save_Result_Path(savefile, pathSize);
                }
                else if (msgBox.clickedButton() == noButton)
                {

                }
             }

          }
        return pathSize;
  }






};
#endif // LAB3_H
