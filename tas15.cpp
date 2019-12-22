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


    for(auto v : all_vertex){
        if(auto edge1: gr.vertexAt(v)){

        }
    }


    return gr;
}
