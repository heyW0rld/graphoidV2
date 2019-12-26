#include "tas15.h"
#include <QColor>
#include<QMessageBox>
Graph lab15(Graph gr,QVector<QString> v1,QVector<QString> v2){
    bool dual = true;
    QVector<QString> vec;
    auto all_vertex = gr.getVertexAsKeys();

    for(auto v : all_vertex){
        if(v2.contains(v->getName()))
        v->setColor(Qt:: magenta);
    }

    for (auto ver1: all_vertex) {
        if(v1.contains(ver1->getName())){
          for (auto edge1: gr.vertexAt(ver1)) {
              if(v1.contains(edge1->getVertex()->getName()))
                dual = false;
              qDebug()<<ver1->getName();
              qDebug()<<edge1->getVertex()->getName();
              if(!vec.contains(ver1->getName())){
                  vec.append(ver1->getName());
              }
              if(!vec.contains(edge1->getVertex()->getName())){
                  vec.append(edge1->getVertex()->getName());
              }
          }
        }
    }
    for (auto ver1: all_vertex) {
        if(v2.contains(ver1->getName())){
          for (auto edge1: gr.vertexAt(ver1)) {
              if(v2.contains(edge1->getVertex()->getName()))
                dual = false;
              qDebug()<<ver1->getName();
              qDebug()<<edge1->getVertex()->getName();
              if(!vec.contains(ver1->getName())){
                  vec.append(ver1->getName());
              }
              if(!vec.contains(edge1->getVertex()->getName())){
                  vec.append(edge1->getVertex()->getName());
              }
          }
        }
    }
    for(auto v : v1){
        if(!vec.contains(v)){
            dual = false;
        }
    }
    for(auto v : v2){
        if(!vec.contains(v)){
            dual = false;
        }
    }
    if(!dual){
        QMessageBox msgBox;
        msgBox.setText("недвудольный.");
        msgBox.exec();
        return gr;
    }
//zadacha
    Graph graph;
    int k = 0;
    int n=0;



    while(vec.size()>1 ){
        n++;
        qDebug()<<"1";
        for(auto v : all_vertex)
        {qDebug()<<"2";
            if(vec.contains(v->getName())){
                if(gr.vertexAt(v).size()==1)
                {qDebug()<<"3";
                    for (auto edge : gr.vertexAt(v))
                    {qDebug()<<"4";
                        qDebug()<<v->getName();
                        qDebug()<<edge->getVertex()->getName();bool ok = true;
                        for(auto versh : graph.getVertexAsKeys()){
                            if(versh->getName() == v->getName() || versh->getName() ==edge->getVertex()->getName())
                                ok=false;
                        }
                        if(ok){
                        vertex_smpt v1(new Vertex(v->getName(), (1+k)%200+ rand()%200,(1+k)%200+rand()%200));
                        v1->setColor(Qt::red);
                        graph.insert(v1, QList<edge_smpt>());
                        vertex_smpt v2(new Vertex(edge->getVertex()->getName(), (2+k)%200+ rand()%200,(2+k)%200+rand()%200));
                        v2->setColor(Qt::magenta);
                        graph.insert(v2, QList<edge_smpt>());
                        edge_smpt edge1 = edge_smpt(new Edge(v1, v2, 1));
                        graph[v1].append(edge1);
                        qDebug()<<vec;
                        vec.erase(std::remove(vec.begin(), vec.end(), v->getName()), vec.end());
                        vec.erase(std::remove(vec.begin(), vec.end(), edge->getVertex()->getName()), vec.end());
                        qDebug()<<vec;
                        }
                    }
                }
            }
        }
        qDebug()<<"5";
        QVector<int> sizeVec;
        for(auto v : all_vertex)
        {   if(vec.contains(v->getName()) &&gr.vertexAt(v).size()!=0)
                sizeVec.append(gr.vertexAt(v).size());
        }
        if(sizeVec.size()==0)
            break;
        qDebug()<<"6";
        bool stop = false;
        qDebug()<<sizeVec;
        qSort(sizeVec);
        qDebug()<<sizeVec;
        qDebug()<<"7";
        if(vec.size()>0){
            qDebug()<<"8";
        for(auto v:all_vertex){
            qDebug()<<"9";
            if(vec.contains(v->getName())){
                qDebug()<<"10";
                if(sizeVec.size()>0){
                if(gr.vertexAt(v).size()==sizeVec.last())
                {qDebug()<<"11";
                    for (auto edge : gr.vertexAt(v))
                    {qDebug()<<"12";
                        bool ok = true;
                        for(auto versh : graph.getVertexAsKeys()){
                            if(versh->getName() == v->getName() || versh->getName() ==edge->getVertex()->getName())
                                ok=false;
                        }
                        if(ok){
                        vertex_smpt v1(new Vertex(v->getName(), (1+k)%200+ rand()%200,(1+k)%200+rand()%200));
                        v1->setColor(Qt::red);
                        graph.insert(v1, QList<edge_smpt>());
                        vertex_smpt v2(new Vertex(edge->getVertex()->getName(), (2+k)%200+ rand()%200,(2+k)%200+rand()%200));
                        v2->setColor(Qt::magenta);
                        graph.insert(v2, QList<edge_smpt>());
                        edge_smpt edge1 = edge_smpt(new Edge(v1, v2, 1));
                        graph[v1].append(edge1);
                        vec.erase(std::remove(vec.begin(), vec.end(), v->getName()), vec.end());
                        vec.erase(std::remove(vec.begin(), vec.end(), edge->getVertex()->getName()), vec.end());
                        stop = true;
                        break;
                        }
                    }
                }
                }
            }
            if(stop)
                break;
        }
        }
        qDebug()<<"inWhile";
        if(n>15)
            break;
    }
    if(graph.getVertexAsKeys().size() == (v1.size()+v2.size()))
    {   qDebug()<<graph.getVertexAsKeys().size() ;
        qDebug()<<gr.getVertexAsKeys().size();
        return graph;
    }else{
        qDebug()<<graph.getVertexAsKeys().size() ;
                qDebug()<<gr.getVertexAsKeys().size();
//        QMessageBox msgBox;
//        msgBox.setText("задача не может быть решена.");
//        msgBox.exec();
        return graph;
    }

}







