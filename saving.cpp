#include "saving.h"
#include <string>
#include <QMessageBox>


void SaveVertexGraph(const QString &str_name , Graph gr){
     QFile file(str_name);
     QSet<vertex_smpt> VerList = gr.getVertexAsKeys();
     if(file.exists() || file.open(QIODevice::WriteOnly )){
         file.open(QIODevice::WriteOnly);
         file.write("Vertex{");
         for(int i = 0; i<VerList.size();++i){
            QString nameVer = VerList.toList()[i]->getName();
            QString x = QString::number(VerList.toList()[i]->getPoint().x());
            QString y = QString::number(VerList.toList()[i]->getPoint().y());
            file.write(nameVer.toUtf8().constData());
            file.write("(");
            file.write(x.toUtf8().constData());
            file.write(",");
            file.write(y.toUtf8().constData());
            if(i<VerList.size()-1){
                file.write("),");
            }
            else{
                file.write(")");
            }
         }
         file.write("}");
         file.close();
         QMessageBox msgBox;
         msgBox.setText("Сохранение успешно завершено");
         msgBox.exec();
         file.close();
     }

}

void SaveAdjmatrix(const QString &str_name ,QVector<QVector<QString>> vec){
    QFile file(str_name);
    if(file.exists() || file.open(QIODevice::WriteOnly )){
         file.open(QIODevice::WriteOnly);
        for(int i =0; i < vec.size(); ++i){
            for(int j =0; j < vec.size(); ++j){
                file.write(vec[i][j].toUtf8().constData());
                file.write(" ");
            }
            file.write("\r\n");
        }
        file.close();
    }
}

QVector<QVector<int>> getIncMatrix(Graph gr){
    QVector<QVector<int>> vec;
    auto all_vertex = gr.getVertexAsKeys().toList();
    QStringList name_list;
    QList<QList<QString>> ListToFile;
    QList<QString> ListVer;
    QList<QList<QString>> ListAllEdges;

    for(auto ver : all_vertex){
        ListVer.append(ver->getName());
         QList<QString> ListOneEdge;
        for(auto edge : gr.vertexAt(ver)){
               ListOneEdge.append(edge->getVertex()->getName());
               ListOneEdge.append(ver->getName());

               ListOneEdge.append(QString::number(edge->getWeight()));
               if(ListOneEdge.size() ==3 && ListOneEdge[0] != ListOneEdge[1]){
                   if(edge->getVecEnd() &&edge->getVecSrc())
                       ListOneEdge.append("x");
                   ListAllEdges.append(ListOneEdge);
                   ListOneEdge.clear();
               }
       }
    }

    for(int i = 0; i< ListVer.size();i++){
        QVector<int> vec1;
        for(int j = 0; j<ListAllEdges.size();j++){

            if(ListAllEdges[j][1] == ListVer[i]){
                if(ListAllEdges[j].size() != 4){
                vec1.append(("-"+ListAllEdges[j][2]).toInt());
                }else{
                    vec1.append((ListAllEdges[j][2]).toInt());
                }

            }else if(ListAllEdges[j][0] == ListVer[i]){
                if(ListAllEdges[j].size() == 4){
                   vec1.append((ListAllEdges[j][2]).toInt());
                }else{
                vec1.append((ListAllEdges[j][2]).toInt());
                }

            }else{
                vec1.append(0);
            }
        }vec.append(vec1);
    }

    qDebug()<<vec;
    return vec;
}

void SaveIncmatrix(const QString &str_name ,Graph gr){
    QFile file(str_name);
    if(file.exists() || file.open(QIODevice::WriteOnly )){
         file.open(QIODevice::WriteOnly);
         auto all_vertex = gr.getVertexAsKeys().toList();
         QStringList name_list;
         QList<QList<QString>> ListToFile;
         QList<QString> ListVer;

         QList<QList<QString>> ListAllEdges;
         for(auto ver : all_vertex){
             ListVer.append(ver->getName());
              QList<QString> ListOneEdge;
             for(auto edge : gr.vertexAt(ver)){
                    ListOneEdge.append(edge->getVertex()->getName());
                    ListOneEdge.append(ver->getName());

                    ListOneEdge.append(QString::number(edge->getWeight()));
                    if(ListOneEdge.size() ==3 && ListOneEdge[0] != ListOneEdge[1]){
                        if(edge->getVecEnd() &&edge->getVecSrc())
                            ListOneEdge.append("x");
                        ListAllEdges.append(ListOneEdge);
                        ListOneEdge.clear();
                    }

            }
         }
         for(int i = 0; i< ListVer.size();i++){
             for(int j = 0; j<ListAllEdges.size();j++){
                 if(ListAllEdges[j][1] == ListVer[i]){
                     file.write((ListAllEdges[j][2]).toUtf8().constData());
                     file.write(" ");
                 }else if(ListAllEdges[j][0] == ListVer[i]){
                     if(ListAllEdges[j].size() == 4){
                         file.write((ListAllEdges[j][2]).toUtf8().constData());
                     }else{
                     file.write(("-"+ListAllEdges[j][2]).toUtf8().constData());
                     }
                     file.write(" ");
                 }else{
                     file.write("0 ");
                 }
             }
             file.write("\r\n");
         }
         file.close();
    }
}


void SaveEdges(const QString &str_name,  Graph gr){
    QFile file(str_name);
    if(file.exists() || file.open(QIODevice::WriteOnly )){
         file.open(QIODevice::WriteOnly);
         auto all_vertex = gr.getVertexAsKeys().toList();
         QStringList name_list;
         file.write("Edges{");
         int index = 0;
         for(auto ver : all_vertex){
             for(auto edge : gr.vertexAt(ver)){
                    file.write(QString::number(index).toUtf8().constData());
                    file.write("(");
                    file.write(QString::number(edge->getWeight()).toUtf8().constData());
                    file.write(",");
                    file.write(ver->getName().toUtf8().constData());
                    file.write(",");
                    file.write(edge->getVertex()->getName().toUtf8().constData());
                    file.write(",");
                    if(edge->getVecSrc() && edge->getVecEnd()){
                        file.write("-1");
                    }else{
                        file.write("1");
                    }

                    file.write("),");
//            qDebug() <<ver->getName();
//            qDebug()<<edge->getVertex()->getName();
             }
         }
         file.write("}");
        file.close();
    }
}

void Save_Isomorphism_Result(const QString &str_name ,int Diametr, int Radius, QVector<int> vectorStepeney)
{
    QFile file(str_name);
    if(file.exists() || file.open(QIODevice::WriteOnly ))
    {
         file.open(QIODevice::WriteOnly);
    }
    file.write((QString("1)Diametr: ") + QString::number(Diametr)).toStdString().c_str());
    file.write("\n");
    file.write((QString("2)Radius :") + QString::number(Radius)).toStdString().c_str());
    file.write("\n");
    for(int i = 0; i < vectorStepeney.count(); ++i)
    {
        file.write((QString("Vector Stepeney: ") + QString::number(vectorStepeney[i])).toStdString().c_str());
        file.write("\n");
    }


}

void Save_Result_Path(const QString &str_name , QVector<int> Path)
{
    QFile file(str_name);
    if(file.exists() || file.open(QIODevice::WriteOnly ))
    {
         file.open(QIODevice::WriteOnly);
    }

    for(int i = 0; i < Path.count(); ++i)
    {
        file.write((QString("Path: ") + QString::number(Path[i])).toStdString().c_str());
        file.write("\n");
    }
}

void Save_Result_Path_amount(const QString &str_name , int Path)
{
        QFile file(str_name);
        if(file.exists() || file.open(QIODevice::WriteOnly ))
        {
             file.open(QIODevice::WriteOnly);
        }

        file.write((QString("Расстояние: ") + QString::number(Path)).toStdString().c_str());
        file.write("\n");

}
