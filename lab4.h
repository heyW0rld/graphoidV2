#ifndef LAB4_H
#define LAB4_H
#include "graph.h"
#include "edge.h"
#include <QVector>
#include <QQueue>
#include <QStack>
#include <QDebug>
#include <algorithm>
#include <qalgorithms.h>
#include "lab3.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include"saving.h"
#include "mainwindow.h"
#include "saving.h"
#include <string>
#include <QMessageBox>
#include <QObject>
#include "task.h"

class lab4
{
private:
    static const int MAX_VALUE = 2147483644;
public:

    static QMap<vertex_smpt, int> Eccentricity(Graph &graph)
    {
        int src = 0;
        QVector<QVector<int>> matrix =  lab3::FloydWarshall(graph, src);


        QList<vertex_smpt> vertices = graph.getVertexAsKeys().toList();
        QMap<vertex_smpt, int> result;
        QVector<int> sumMatrixString(matrix.count(), 0);

        for(int i = 0; i < matrix.count(); i++)
        {
            int eccentricity = *std::max_element(matrix[i].constBegin(), matrix[i].constEnd());
            if (eccentricity == 2147483644 || eccentricity == 0)
            {
                continue;
            }
            result.insert(vertices[i], eccentricity);
            qDebug() << vertices[i]->getName() << "Ecccentricity: " << eccentricity;
        }

        QVector<int> values = result.values().toVector();

        for (int i = 0; i < values.count(); i++)
        {
            qDebug() << values[i];
        }

          QVector<int> vectorSepeney = VectorStepeney(graph);
          QString stepenStr = "";

          for(int i = 0; i < vectorSepeney.count(); i++)
          {
              qDebug() << "Vector Stepeney" << vectorSepeney[i];
              stepenStr.append(QString::number(vectorSepeney[i]));
              stepenStr.append(" ");
          }


        int diametr = *std::max_element(values.constBegin(), values.constEnd());

        qDebug() << "Diametr " << diametr << endl;

        int radius = *std::min_element(values.constBegin(), values.constEnd());

        qDebug() << "Radius " << radius << endl;

        QMessageBox::about(nullptr, "Результат", "Радиус: " + QString::number(radius) + "\n" +
                           "Диаметр: " + QString::number(diametr) + "\n" +
                           "Вектор степеней: " + stepenStr);


        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setTextFormat(Qt::RichText);
        //msgBox.setText("Все несохраненные данные будут утеряны!");
        msgBox.setInformativeText("Желаете сохранить результаты?");
        QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
        QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
        msgBox.setDefaultButton(yesButton);
        msgBox.exec();

        if (msgBox.clickedButton() == yesButton)
        {
            //QVector<QVector<QString>> vec;
            QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
            QVector<QString> InVec;
            Save_Isomorphism_Result(savefile,radius, diametr, vectorSepeney);

        }



        QVector<QVector<int>> matrixInc = getIncMatrix(graph);

        for(int i = 0;  i < matrixInc.count(); i++)
        {
            for(int j =0; j < matrixInc[i].count(); j++)
            {
                qDebug() << matrixInc[i][j] << " ";
            }
            qDebug() << endl;
        }

        //Чтобы найти радиус :наименший из эксентреситетоов
        //Диаметр наибольший из эксентрисететов
        //Вектор степеней графа :сколько вершины инцедентно ребер, получить список цифор и отсортировать его и куда нибудь записать.
        //Есть мапа (от вершины к списку ребер которым ога инцедентна) нужно для каждой вершинки посчитать кол-во элементов в списке который лежжит в мапе по этой вершинке
        //ВСе эти кол-ва эелементов положить в вект отсортировать по убыванию и все это вектор степенй вершин.
        //Вектор степеней верщин :
   return result;
    }

     static QVector<int> VectorStepeney(Graph& graph)
     {
         int i = 0;
         QVector<int> result(graph.getVertexAsKeys().count());
         for(auto ver:graph.getVertexAsKeys())
         {
             result[i] = graph[ver].count();
             for(auto v: graph.getVertexAsKeys())
             {
                 for(auto ed:graph[v])
                 {
                     if(ed->getVertex() == ver)
                     {
                         ++result[i];
                     }
                 }
             }


             ++i;
         }


         std::sort(result.begin(), result.end(), [](int first, int last){return first > last;});
                 return result;
     }

     void Save_Diametr(const QString &str_name ,QString Diametr){
         QFile file(str_name);
         if(file.exists() || file.open(QIODevice::WriteOnly )){
              file.open(QIODevice::WriteOnly);
              file.write("Diametr:");
              file.write(Diametr.toUtf8().constData());
              file.write("\r\n");
              file.close();
         }
     }


};
#endif // LAB4_H
