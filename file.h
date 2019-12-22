#ifndef FILE_H
#define FILE_H
#include <QLayout>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <graph.h>

Graph parseAdjFile(const QString &str_name);
Graph parseIncFile(const QString &str_name);
Graph parseEdgesFile(const QString &str_name , Graph gr);
Graph parseVertexFile(const QString &str_name);



#endif // FILE_H
