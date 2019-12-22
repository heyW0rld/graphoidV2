#include "tas15.h"
#include <QColor>

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
    if(!dual)
        return gr;

//zadacha
    Graph graph;
    int k = 0;




    while(vec.size()>0){
        for(auto v : all_vertex)
        {
            if(vec.contains(v->getName())){
                if(gr.vertexAt(v).size()==1)
                {
                    for (auto edge : gr.vertexAt(v))
                    {
                        vertex_smpt v1(new Vertex(v->getName(), (1+k)%200+ rand()%200,(1+k)%200+rand()%200));
                        v1->setColor(Qt::black);
                        graph.insert(v1, QList<edge_smpt>());
                        vertex_smpt v2(new Vertex(edge->getVertex()->getName(), (2+k)%200+ rand()%200,(2+k)%200+rand()%200));
                        v2->setColor(Qt::magenta);
                        graph.insert(v2, QList<edge_smpt>());
                        edge_smpt edge1 = edge_smpt(new Edge(v1, v2, 1));
                        graph[v1].append(edge);
                        vec.erase(std::remove(vec.begin(), vec.end(), v->getName()), vec.end());
                        vec.erase(std::remove(vec.begin(), vec.end(), edge->getVertex()->getName()), vec.end());
                    }
                }
            }
        }
        QVector<int> sizeVec;
        QList<int>vec;
        for(auto v : all_vertex)
        {
            sizeVec.append(gr.vertexAt(v).size());
        }
        qSort(sizeVec);
    }


    return graph;
}







