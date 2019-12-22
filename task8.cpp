#include "task8.h"
#include "task.h"

//Обьединение графов
void graphUnion(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjA[i][j] != 0 || adjB[i][j] != 0)
                adjC[i][j] = 1;
        }
    }
}

//Пересечение графов
void graphIntersection(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjA[i][j] != 0 && adjB[i][j] != 0)
                adjC[i][j] = 1;
        }
    }
}
//вычтание графа B из графа A
void graphSubtraction(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjA[i][j] != 0 && adjB[i][j] != 0)
                adjC[i][j] = 0;
            else{
                if(adjA[i][j] != 0)
                    adjC[i][j] = 1;
            }
        }
    }
}
//импликация A -> B
void graphImplication(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjA[i][j] != 0 && adjB[i][j] == 0)
                adjC[i][j] = 0;
            else
                adjC[i][j] = 1;
        }
    }
}
//коимпликация графа !(A -> B)
void graphCoimplication(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjA[i][j] != 0 && adjB[i][j] == 0)
                adjC[i][j] = 1;
            else
                adjC[i][j] = 0;
        }
    }
}

//исключающее или
void graphXor(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if((adjA[i][j] != 0 && adjB[i][j] != 0) || (adjA[i][j] == 0 && adjB[i][j] == 0))
                adjC[i][j] = 0;
            else
                adjC[i][j] = 1;
        }
    }
}

//эквивалентность
void graphEquivalence(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if((adjA[i][j] != 0 && adjB[i][j] != 0) || (adjA[i][j] == 0 && adjB[i][j] == 0))
                adjC[i][j] = 1;
            else
                adjC[i][j] = 0;
        }
    }
}

//штрих Шеффера
void graphShefferStroke(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjA[i][j] != 0 && adjB[i][j] != 0)
                adjC[i][j] = 0;
            else
                adjC[i][j] = 1;
        }
    }
}

//стрелка Пирса
void graphPirseArrow(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC)
{
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjA[i][j] == 0 && adjB[i][j] == 0)
                adjC[i][j] = 1;
            else
                adjC[i][j] = 0;
        }
    }
}

Graph binaryOperationsOnGraphs(int operation_index, Graph &gA, Graph &gB, QVector<QVector<int>> &adjC)
{
    auto adjA = gA.toAdjacencyMatrix(compare);
    auto adjB = gB.toAdjacencyMatrix(compare);
    int size = adjA.size();
    for(int i=0; i<adjA.size(); i++){
        for(int j=0;j<adjA.size(); j++){
            if(i==j){
                adjA[i][j]=0;
            }
        }
    }
    for(int i=0; i<adjB.size(); i++){
        for(int j=0;j<adjB.size(); j++){
            if(i==j){
                adjB[i][j]=0;
            }
        }
    }

    adjC.resize(size);
    for(int i = 0; i < size; ++i)
        adjC[i].resize(size);

    switch(operation_index)
    {
        case 0:
            graphUnion(adjA, adjB, adjC);
        break;

        case 1:
            graphIntersection(adjA, adjB, adjC);
        break;

        case 2:
            graphSubtraction(adjA, adjB, adjC);
        break;

        case 3:
            graphSubtraction(adjB, adjA, adjC);
        break;

        case 4:
            graphImplication(adjA, adjB, adjC);
        break;

        case 5:
            graphImplication(adjB, adjA, adjC);
        break;

        case 6:
            graphCoimplication(adjA, adjB, adjC);
        break;

        case 7:
            graphCoimplication(adjB, adjA, adjC);
        break;

        case 8:
            graphXor(adjA, adjB, adjC);
        break;

        case 9:
            graphEquivalence(adjA, adjB, adjC);
        break;

        case 10:
            graphShefferStroke(adjA, adjB, adjC);
        break;

        case 11:
            graphPirseArrow(adjA, adjB, adjC);
        break;
    }

    Graph g;
    int count = 0;
    auto gr_list = gA.getVertexAsKeys().toList();
    std::sort(gr_list.begin(), gr_list.end(), compare);
    for(auto ver : gr_list){
        if(count >= size)
            break;
        else{
            vertex_smpt v(new Vertex("Ver" + QString::number(count), ver->getPoint()));
            v->setColor(Qt::green);
            g.insert(v, QList<edge_smpt>());
        }
        ++count;
    }

    return g;
}
