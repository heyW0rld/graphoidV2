#include "file.h"
#include <QDebug>
#include "graph.h"
#include <QMessageBox>
#include <cmath>

using namespace std;

Graph  parseAdjFile(const QString &str_name){
//    в данном случае работаем с матрицей смежности, она квадратная
    Graph pure_graph;
    QVector<QVector<QString>> vec;
    QFile file(str_name);
    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return pure_graph;
    }

    int col_count = 0;
    int row_count = 0;
    char check = true;
    QVector<QVector<QString>> vc;

    while(!file.atEnd()){
        QString str = file.readLine().trimmed();
        str= str.mid(0,str.indexOf("%"));
        str = str.trimmed();

        if(str.isEmpty())
            continue;

        row_count++;
        QStringList s_list = str.split(" ");

//        Элементов в строке больше или меньше чем нужно
        if(col_count != 0 && col_count != s_list.size()){//---
//            qDebug() << "Error in matrix row " + QString::number(row_count) + " : Row contains too many or too few element!";
//            qDebug() << col_count;
//            qDebug() << s_list.size();
            file.close();
            check = false;
            QMessageBox msgBox;
            msgBox.setText("Ошибка в матрице.");
            msgBox.exec();
            return pure_graph;
        }
        else {
            col_count = s_list.size();
        }

        QVector<QString> v;
        bool ok;
//        проверка на допустимые значения
        for(QString s : s_list){//---
//            qDebug() << s;
            s.toInt(&ok);
            if(ok){
                v.append(s);
            }
            if(!ok){
//                qDebug() << "Error in matrix row " + QString::number(row_count) +" : Matrix content incorrect value!";
                check = false;
                QMessageBox msgBox;
                msgBox.setText("Ошибка в матрице.");
                msgBox.exec();
                return pure_graph;
            }
        }
        vc.append(v);
    }
//    Проверка на квадратность матрицы(обязательное условие)
    if(row_count != col_count){
//        qDebug() << "Error: Adjacency matrix is not square!";
        file.close();
        check = false;
        QMessageBox msgBox;
        msgBox.setText("Ошибка в матрице.");
        msgBox.exec();
        return pure_graph;
    }

//    создание нового графа
    Graph graph;
//    создаю вершины для нового графа, количество вершин  считается по размеру графа
    for(int i=0;i<vc.size();i++){

//        создание вершины с умным указателем вершина - (название вершины, координата по x, координата по y)
        vertex_smpt v(new Vertex("Ver" + QString::number(i), (1+i)%200+ rand()%200,(1+i)%200+rand()%200));
//        установка цвета вершины
        v->setColor(Qt::green);
//        добавление вершины со списком ребер, относящихся к ней, в общую структуру графа
        graph.insert(v, QList<edge_smpt>());
    }
//    создание ребер
//    получаю список вершин
       QSet<vertex_smpt> set_vert = graph.getVertexAsKeys();
//       прохожу по матрице, матрица инцидентности квадратная
        for(int i = 0 ;i <vc.size();i++){
            for(int j = 0; j<vc.size();j++){
//                если не ноль, начинаем отрисовку ребер
                if(vc[i][j] !="0"){
//                    проверка: петля или нет
                    if(i==j){
//                        обработка петли
//                        создание ребра сразу с умным указателем, ребро создается с данными:(откуда, куда, вес ребра), тк в данном случае i = j, они
//                        указывают на одну и ту же вершину, то есть ребро из вершины само в себя
                        edge_smpt edge = edge_smpt(new Edge(set_vert.toList().at(i), set_vert.toList().at(j), vc[i][j].toInt()));
//                        тк есть проблема, что начинает лагать, когда петля отрисовывается ровно на вершине, отбрасываем его в немного сторону
                        edge->setPoint(set_vert.toList().at(i)->getPoint().x(), set_vert.toList().at(i)->getPoint().y() - VER_RADIUS > 0
                                       ? set_vert.toList().at(i)->getPoint().y() - VER_RADIUS : set_vert.toList().at(i)->getPoint().y() + VER_RADIUS);
//                        добавление ребра в список, который привязан к вершине
                        graph[set_vert.toList().at(i)].append(edge);
                    }else {
//                     создание ребра между двумя вершинами(откуда, куда и вес)
                      edge_smpt edge = edge_smpt(new Edge(set_vert.toList().at(i),set_vert.toList().at(j), vc[i][j].toInt()));
//                      отрисовка стрелки на ребре, тк ребро направленно, то стрелка одна
                      edge->setVecEnd(true);
//                      добавление ребра в список
                      graph[set_vert.toList().at(i)].append(edge);
                    }
                }
            }
        }

        for(auto v: graph.getVertexAsKeys()){
//            qDebug()<<v->getName();
            for(auto e:graph[v]){
//                qDebug()<< e->getWeight();
            }
        }
    if(!check){
        QMessageBox msgBox;
        msgBox.setText("Ошибка в матрице.");
        msgBox.exec();
        return pure_graph;
    }
    file.close();
    return graph;
}
//нужна проверка матрицы, чтобы в одном столбце не более 2 чисел
Graph  parseIncFile(const QString &str_name){
//    Работаем с матрицей инцидентности
//    каждая строка данной матрицы описывает ребро
//    ребро не может быть инцедентно более чем двум вершинам(одна из проверок)
//    матрица не квадратная на количество строк можно вообще забить(но кол-во столбцов везде одинаково
    QFile file(str_name);
    Graph pure_graph;
    QVector<QVector<QString>> vec;
    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        qDebug() << "Error in input file!";
        return pure_graph;
    }
    char check = true;
    int col_count = 0;
    int row_count = 0;
    QVector<QVector<QString>> vc;

    while(!file.atEnd()){
        QString str = file.readLine().trimmed();//удаляю /n и пробелы спереди(если есть)

        str= str.mid(0,str.indexOf("%"));
        str = str.trimmed();

        if(str.isEmpty())
            continue;

        row_count++;
        QStringList s_list = str.split(" ");

//        Элементов в строке больше или меньше чем нужно
        if(col_count != 0 && col_count != s_list.size()){//---
//            qDebug() << "Error in matrix row " + QString::number(row_count) + " : Row contains too many or too few element!";
//            qDebug() << col_count;
//            qDebug() << s_list.size();
            check = false;
            file.close();
            return pure_graph;
        }
        else {
            col_count = s_list.size();
        }

        QVector<QString> v;
        bool ok;
//        проверка на допустимые значения
        for(QString s : s_list){//---
//            qDebug() << s;
            s.toInt(&ok);
            if(ok)
            v.append(s);
            if(!ok){
//                qDebug() << "Error in matrix row " + QString::number(row_count) +" : Matrix content incorrect value!";
                check = false;
                QMessageBox msgBox;
                msgBox.setText("Ошибка в матрице.");
                msgBox.exec();
                return pure_graph;
            }
        }
        vc.append(v);
    }

    QVector<int>  VecForCheck;
    for(int i = 0 ;i <col_count;i++){
        for(int j = 0; j<row_count;j++){
            if(vc[j][i] !="0"){
                VecForCheck.append(j);
            }
        }
//        qDebug()<<VecForCheck;
        if(VecForCheck.size()==2){
            if(abs(vc[VecForCheck.at(0)][i].toInt()) != abs(vc[VecForCheck.at(1)][i].toInt())){
//                qDebug()<<vc[VecForCheck.at(0)][i] ;
//                qDebug()<<vc[VecForCheck.at(1)][i];
                check = false;
//                qDebug()<<"ошибка в матрице";
                QMessageBox msgBox;
                msgBox.setText("Ошибка в матрице.");
                msgBox.exec();
                return pure_graph;
            }
        }
        if(VecForCheck.size()>2){
            check = false;
//            qDebug()<<"ошибка в матрице";
            QMessageBox msgBox;
            msgBox.setText("Ошибка в матрице.");
            msgBox.exec();
            return pure_graph;
        }
        VecForCheck.clear();
    }

    Graph graph;
    for(int i=0;i<row_count;i++){
        vertex_smpt v(new Vertex("Ver" + QString::number(i), (1+i)%200+ rand()%200,(i)%200+rand()%200));
        v->setColor(Qt::green);
        graph.insert(v, QList<edge_smpt>());
    }

    QVector<int>  vec1;
    QSet<vertex_smpt> set_vert = graph.getVertexAsKeys();
        for(int i = 0 ;i <col_count;i++){
            for(int j = 0; j<row_count;j++){
//                qDebug()<<"проход по матрице";
//                qDebug()<<vc[j][i];

                if(vc[j][i] !="0"){
                    vec1.append(j);
                    if(vec1.size() ==2){
//                    qDebug()<<j;

                    if(vc[vec1.at(0)][i].toInt() < 0){
                    edge_smpt  edge = edge_smpt(new Edge(set_vert.toList().at(vec1.at(1)),set_vert.toList().at(vec1.at(0)), vc[vec1.at(1)][i].toInt()));
                         edge->setVecEnd(true);
                         graph[set_vert.toList().at(vec1.at(1))].append(edge);
//                         qDebug()<<vc[vec1.at(0)][i];
//                         qDebug()<<vc[vec1.at(1)][i];
                    }else if(vc[vec1.at(1)][i].toInt() < 0 ){
                         edge_smpt edge = edge_smpt(new Edge(set_vert.toList().at(vec1.at(0)),set_vert.toList().at(vec1.at(1)), vc[vec1.at(0)][i].toInt()));
                         edge->setVecEnd(true);
                         graph[set_vert.toList().at(vec1.at(0))].append(edge);
//                         qDebug()<<vc[vec1.at(0)][i];
//                         qDebug()<<vc[vec1.at(1)][i];
                    }else{
                        edge_smpt edge = edge_smpt(new Edge(set_vert.toList().at(vec1.at(1)),set_vert.toList().at(vec1.at(0)), vc[vec1.at(0)][i].toInt()));
                        edge->setVecSrc(true);
                        edge->setVecEnd(true);
//                        qDebug()<<vc[vec1.at(0)][i];
//                        qDebug()<<vc[vec1.at(1)][i];
                        graph[set_vert.toList().at(vec1.at(1))].append(edge);
                    }
                    }
                }
            }
//            qDebug()<<vec1;
            vec1.clear();
        }

    if(!check){
        QMessageBox msgBox;
        msgBox.setText("Ошибка в матрице.");
        msgBox.exec();
        return pure_graph;
    }
    file.close();
    qDebug()<<"ge";
    return graph;
}

Graph parseEdgesFile(const QString &str_name , Graph gr){
    Graph pure_graph;
    Graph GraphUpdate;

    QFile file(str_name);
    QVector<QVector<QString>> vec;
    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        qDebug() << "Error in input file!";
        return pure_graph;
    }
    QString AllStr;
    while(!file.atEnd()){
    QString str = file.readLine().trimmed();
    str= str.mid(0,str.indexOf("%"));
    str = str.replace( " ", "" ).trimmed();
    AllStr +=str;
    }
    if(AllStr.startsWith("Edges{") && (AllStr.endsWith(")}") || AllStr.endsWith("),}"))){
        AllStr = AllStr.mid(AllStr.indexOf("{")+1,(AllStr.indexOf("}"))).trimmed();
        if(AllStr.contains("),}"))
            AllStr.remove("),}");
        else
            AllStr = AllStr.remove(")}");
        AllStr = AllStr.replace("(",",");
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Ошибка в записи.");
        msgBox.exec();
        return pure_graph;
    }
    QStringList s_list = AllStr.split("),");
    QList<QList<QString>> ListOfAllEdges;
    for(int i = 0 ; i<s_list.size(); ++i){
        QStringList ListOneEdge = s_list[i].split(",");
        if(ListOneEdge.size() == 5){

            if(ListOneEdge[0].toInt() >= 0 && ListOneEdge[1].toInt() >-1 && ListOneEdge[4].toInt()){
               ListOfAllEdges.append(ListOneEdge);
            }else{
                QMessageBox msgBox;
                msgBox.setText("Ошибка в записи ребра.");
                msgBox.exec();
                return pure_graph;
            }
        }else{
            QMessageBox msgBox;
            msgBox.setText("Ошибка в записи.");
            msgBox.exec();
            return pure_graph;
        }
    }
    GraphUpdate = gr;
//    qDebug()<<ListOfAllEdges;
    bool firstEdge = false, secondEdge = false;
    vertex_smpt v1,v2;
    int Read=0;
    QSet<vertex_smpt> VerList = GraphUpdate.getVertexAsKeys();
    for(int i = 0; i<ListOfAllEdges.size();++i){
        for(int j = 0; j<VerList.size(); j++){
//            qDebug()<<j;
//            qDebug()<<VerList.toList()[j]->getName();
//            qDebug()<<"ver" + QString::number(ListOfAllEdges[i][2]);
            if(VerList.toList()[j]->getName() == ( ListOfAllEdges[i][2])){
               firstEdge = true;
               v1 =VerList.toList()[j];
//               qDebug()<<"нашел первую";
            }
//            qDebug()<<VerList.toList()[i]->getName();
//            qDebug()<<ListOfAllEdges[i][3];
            if(VerList.toList()[j]->getName() == ( ListOfAllEdges[i][3])){
               secondEdge = true;
               v2 =VerList.toList()[j];
//               qDebug()<<"нашел вторую";
            }
        }
        if(firstEdge && secondEdge){
           if(ListOfAllEdges[i][1].toInt() > 0){
               if(v1->getName() == v2->getName()){
                   edge_smpt edge = edge_smpt(new Edge(v1, v2, ListOfAllEdges[i][1].toInt()));
                   edge->setPoint(v1->getPoint().x(), v2->getPoint().y() - VER_RADIUS > 0
                                  ? v1->getPoint().y() - VER_RADIUS : v2->getPoint().y() + VER_RADIUS);
                   GraphUpdate[v1].append(edge);
               }else
               {
                edge_smpt edge = edge_smpt(new Edge(v1,v2, ListOfAllEdges[i][1].toInt()));
                edge->setVecEnd(true);
                if(ListOfAllEdges[i][4] == "-1")
                    edge->setVecSrc(true);
                GraphUpdate[v1].append(edge);
               }
           }
           firstEdge = false;
           secondEdge = false;
           Read++;
        }

    }
    QMessageBox msgBox;
    if(Read !=ListOfAllEdges.size())
        msgBox.setText("Было нарисовано "+ QString::number(Read) + " из " + QString::number(ListOfAllEdges.size()));
    if(Read == ListOfAllEdges.size())
        msgBox.setText("Было нарисовано "+ QString::number(Read) + " из " + QString::number(ListOfAllEdges.size()));
    msgBox.exec();
    file.close();
    return GraphUpdate;
}

//список рёбер вершин вида Edges{i(a, k, l, d), . . .},
//где i — номер ребра, a — вес ребра, k и l — номера или имена вершин,
//d — может быть 1, если ребро направленное, и 1 в другом
//случае;


Graph parseVertexFile(const QString &str_name){
    Graph pure_graph;
    QList<QList<QString>> ListOfAllVertex;

    QFile file(str_name);
    QVector<QVector<QString>> vec;
    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        qDebug() << "Error in input file!";
        return pure_graph;
    }
    QString AllStr;
    while(!file.atEnd()){
    QString str = file.readLine().trimmed();
    str= str.mid(0,str.indexOf("%"));
    str = str.replace( " ", "" ).trimmed();

    AllStr +=str;
    }
//    qDebug()<<AllStr;
    if(AllStr.contains("(") || AllStr.contains(")")){
    if(AllStr.startsWith("Vertex{") && AllStr.endsWith("}")){
    AllStr = AllStr.mid(AllStr.indexOf("{")+1,(AllStr.indexOf("}"))).trimmed();
    AllStr = AllStr.remove(")}");
    AllStr = AllStr.replace("(",",");
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Ошибка в записи.");
        msgBox.exec();
        return pure_graph;
    }

//    qDebug()<<AllStr;
    QStringList s_list = AllStr.split("),");
//    qDebug()<<s_list;
    bool ok1,ok2;
    for(int i = 0 ; i<s_list.size(); ++i){
        QStringList ListOneVer = s_list[i].split(",");
//        qDebug()<<ListOneVer;
        if(ListOneVer.size() == 3){
             ListOneVer[1].toInt(&ok1);
             ListOneVer[2].toInt(&ok2);
             if(ok1 && ok2){
                 ListOfAllVertex.append(ListOneVer);
             }else{
                 QMessageBox msgBox;
                 msgBox.setText("Ошибка в записи вершины.");
                 msgBox.exec();
                 return pure_graph;
             }
        }else{
            QMessageBox msgBox;
            msgBox.setText("Ошибка в записи.");
            msgBox.exec();
            return pure_graph;
        }
    }

    for(int i = 0; i < ListOfAllVertex.size(); i++){
            vertex_smpt v(new Vertex( ListOfAllVertex[i][0], ListOfAllVertex[i][1].toInt(),ListOfAllVertex[i][2].toInt()));
            v->setColor(Qt::green);
            pure_graph.insert(v, QList<edge_smpt>());
        }
    }
    else{
        if(AllStr.startsWith("Vertex{") && AllStr.endsWith("}")){
        AllStr = AllStr.mid(AllStr.indexOf("{")+1,(AllStr.indexOf("}"))).trimmed();
        AllStr = AllStr.remove("}");
        }else{
            QMessageBox msgBox;
            msgBox.setText("Ошибка в записи.");
            msgBox.exec();
            return pure_graph;
        }
        QList<QString> ListNameVer;
        QStringList s_list = AllStr.split(",");
        for(int i = 0; i<s_list.size();++i){
                ListNameVer.append(s_list[i]);
        }
        for(int i = 0; i < ListNameVer.size(); i++){
                vertex_smpt v(new Vertex(ListNameVer[i], rand()%200,rand()%200));
                v->setColor(Qt::green);
                pure_graph.insert(v, QList<edge_smpt>());
        }
    }
    file.close();
    return pure_graph;
}
