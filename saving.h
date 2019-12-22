#ifndef SAVING_H
#define SAVING_H

#include <QLayout>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <graph.h>
#include <QTableWidget>



void SaveVertexGraph(const QString &str_name ,Graph gr);
void SaveAdjmatrix(const QString &str_name ,QVector<QVector<QString>> vec);
void SaveIncmatrix(const QString &str_name ,Graph gr);
void SaveEdges(const QString &str_name,  Graph gr);
void Save_Isomorphism_Result(const QString &str_name ,int Diametr, int Radius, QVector<int> vectorStepeney);
void Save_Result_Path(const QString &str_name , QVector<int> Path);
void Save_Result_Path_amount(const QString &str_name , int Path);


QVector<QVector<int>> getIncMatrix(Graph gr);
//Graph lab9(QVector<QVector<int>> matrix);

#endif // SAVING_H
