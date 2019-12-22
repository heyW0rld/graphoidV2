#ifndef TASK5_H
#define TASK5_H
#include"graph.h"
#include"saving.h"
#include "mainwindow.h"
#include "task.h"
#include"edge.h"
#include"lab4.h"

class lab5
{
public:
   static bool Isomorphism(Graph &graph1, Graph &graph2)
   {
       QVector<QVector<int>> matrixGraph1 = getIncMatrix(graph1);
       QVector<QVector<int>> matrixGraph2 = getIncMatrix(graph2);
       QVector<int> count_Edges1 = lab4::VectorStepeney(graph1);
       QVector<int> count_Edges2 = lab4::VectorStepeney(graph2);



        if(count_Edges1.count() != count_Edges2.count())
        {
            QMessageBox::about(nullptr, "Изоморфность", "Графы изоморфны слабо!\n");
            return false;
        } else if
                (matrixGraph1.count() != matrixGraph2.count())
            {
                QMessageBox::about(nullptr, "Изоморфность", "Графы изоморфны слабо!\n");
                    return false;
            } else if (matrixGraph1.count() == 0)
                    {
                        return true;
                    }else
            {
                    for (int i = 0; i < matrixGraph1.count(); i++)
            {
                if (matrixGraph1[i].count() != matrixGraph2[i].count())
                {
                    QMessageBox::about(nullptr, "Изоморфность", "Графы изоморфны слабо!\n");
                    return false;
                }
            }

            if (matrixGraph1[0].count() == 0)
            {
                return true;
            }

            for(int i  = 0; i < matrixGraph1.size(); i++)
            {
                    for(int j = 0; j < matrixGraph1[0].size(); j++)
                    {

                        if(matrixGraph1[i][j] < 0)
                        {
                            matrixGraph1[i][j] = -1;
                        }

                if(matrixGraph1[i][j] > 0)
                {
                    matrixGraph1[i][j] = 1;
                }
                if(matrixGraph2[i][j] < 0)
                {
                    matrixGraph2[i][j] = -1;
                }

                if(matrixGraph2[i][j] > 0)
                {
                    matrixGraph2[i][j] = 1;
                }


            }

       }

       // создание всех перестановок (по строкам)
       QList<int> notMoved;
       for (int i = 0; i < matrixGraph1.count(); i++)
       {
           notMoved.append(i);
       }
       QList<QVector<QVector<int>>> lineReplacements;
       LineReplacements(matrixGraph1, notMoved, QList<int>(), lineReplacements);

       //Нужно написать метод который во одном из графов
       //скпоироваь два графа в нвоые переменные
       //Нужно в одном из графов написать все возможныне перестанвоки вершин местами, для каждой из перестановок построить матрицы смежности затем для первого и второго
       //на весь ребер забить и просто сравнить матрицы заменить все положителньне цифры единицами и отрицательными и если для хотя бы одной перестановки матрицы найдутя равные матриц то
       //графы изоморфны

       //Мапа от вершинки к списке ребер которым она инцеденрно (для каждо вершины нужно точно определить ее индекс ее строки в матрице
       //Мапа - пара ключ хначения ключ -смарпт поинетр на вершниу - ключ список ребере инцелентных вершине
       //Матрица инцеддентнси: прохожу по всем вершинам для каждой берем ребра, и для каждоой вершине нужно проставить для каждогои ребра еденичку
       //Как протий по мапе

       for (int i = 0; i < lineReplacements.count(); i++)
       {
           notMoved.clear();
           for (int j = 0; j < matrixGraph1[0].count(); j++)
           {
               notMoved.append(j);
           }
           // создание перестановок по столбцам для текущей перестановки по строкам
           QList<QVector<QVector<int>>> columnReplacements;
           ColumnReplacements(lineReplacements[i], notMoved, QList<int>(), columnReplacements);
           for (int j = 0; j < columnReplacements.count(); j++)
           {
               if (Isomorphism_Inner(matrixGraph2, columnReplacements[j]))
               {
                   QString message;
                   message = "Графы изоморфны.";
                   QMessageBox::information(nullptr, "Изоморфизм", message);
                   return true;
               }
           }
       }
       QString message;

       message = "Графы не изоморфны.";

       QMessageBox::information(nullptr, "Изоморфизм", message);
       return false;
     }
   }

private:

   static void LineReplacements(QVector<QVector<int>> matrixEnd, QList<int> notMoved, QList<int> moved, QList<QVector<QVector<int>>> &result)
   {
       if (notMoved.count() == 0)
       {
           QVector<QVector<int>> mixedLines(matrixEnd.count());
           for (int i = 0; i < mixedLines.count(); i++)
           {
               mixedLines[i] = QVector<int>(matrixEnd[moved[i]]);
           }
           result.append(mixedLines);
           return;
       }
       for (int i = 0; i < notMoved.count(); i++)
       {
           QList<int> notMovedCopy(notMoved);
           QList<int> movedCopy(moved);
           movedCopy.append(notMovedCopy.at(i));
           notMovedCopy.removeAt(i);
           LineReplacements(matrixEnd, notMovedCopy, movedCopy, result);
       }
   }

   static void ColumnReplacements(QVector<QVector<int>> matrixEnd, QList<int> notMoved, QList<int> moved, QList<QVector<QVector<int>>> &result)
   {
       if (notMoved.count() == 0)
       {
           QVector<QVector<int>> mixedColumns(matrixEnd.count());
           for (int i = 0; i < mixedColumns.count(); i++)
           {
               mixedColumns[i] = QVector<int>(matrixEnd[i].count());
           }
           for (int i = 0; i < matrixEnd.count(); i++)
           {
               for (int j = 0; j < moved.count(); j++)
               {
                   mixedColumns[i][j] = matrixEnd[i][moved[j]];
               }
           }
           result.append(mixedColumns);
           return;
       }
       for (int i = 0; i < notMoved.count(); i++)
       {
           QList<int> notMovedCopy(notMoved);
           QList<int> movedCopy(moved);
           movedCopy.append(notMovedCopy.at(i));
           notMovedCopy.removeAt(i);
           ColumnReplacements(matrixEnd, notMovedCopy, movedCopy, result);
       }
   }

   //static  метод который =будет делать все возможные перестановки реьер местами , у i-ого одного ребра и у i-ого друго должны соответствовать вершины
   static bool Isomorphism_Inner(QVector<QVector<int>>& matrixGraph1, QVector<QVector<int>>& matrixGraph2)
   {
       for (int i = 0; i < matrixGraph1.count(); i++)
       {
           for (int j = 0; j < matrixGraph1[i].count(); j++)
           {
               if (matrixGraph1[i][j] != matrixGraph2[i][j])
               {
                   return false;
               }
           }
       }
       return true;
   }

};
#endif // TASK5_H
