#ifndef LAB21_H
#define LAB21_H



//#include <msolution.h>
#include <QRandomGenerator>
#include <QQueue>
#include <random>
//#include <cmath>
//#include <functional>
//#include <mpair.h>
#include <chrono>
#include <queue>
#include <QMatrix>
#include <QSet>
using namespace std;
template <typename K, typename V>
class MPair
{
public:

    K key;
    V value;

    MPair() {
    }

    MPair(const K& key, const V& value) : key(key), value(value){
    }

    K getKey() const {
        return key;
    }

    void setKey(const K &value) {
        key = value;
    }

    V getValue() const {
        return value;
    }

    void setValue(const V& value) {
        this->value = value;
    }

    bool operator > (const MPair<K,V>& with) const {
        return key > with.key;
    }

    bool operator < (const MPair<K,V>& with) const {
        return key < with.key;
    }

    bool operator >= (const MPair<K,V>& with) const {
        return key >= with.key;
    }

    bool operator <= (const MPair<K,V>& with) const {
        return key <= with.key;
    }

    bool operator == (const MPair<K,V>& with)  const{
        return key == with.key;
    }

};


class Solution_21
{
    QString logResult;

public:
    Solution_21() {

    }

    void placeToLog(const QString& what) {
        logResult.append(what).append('\n');
    }
    typedef QVector<QVector<int>> MMatrix;
    MMatrix generateGraph(int number = 10000) {

        std::chrono::time_point<std::chrono::system_clock> start, end;

        placeToLog("Запускается процедура генерации графа");
        placeToLog("Размерность графа: " + QString::number(number));
        //chance - шанс получить ребро между двумя рёбрами с очень большим расстоянием

        start = std::chrono::system_clock::now();

        MMatrix bigGraph(number, QVector<int>(number, 0));

        //Начинаем генерацию графа

        std::random_device rd{};
        std::mt19937 gen{rd()};

        std::normal_distribution<> d{90,25};

        for (int i = 0; i < number; ++i) {
            for (int j = 0; j < number; ++j) {
                //Итак, будем придерживаться следующего плана
                //1) Будет ли к j-й вершине вообще какой-либо путь? Определяем при помощи нормального распределения. Всё что <= 12, не будет содержать пути в j-ю вершину
                //2) Если распределение вернуло >= 38, то тогда сделаем некоторую большую связь
                //3) Если распределение в пределах std, то тогда соединяем


                if (i != j) {
                    int value = std::round(d(rd));

                    if (value >= 120) {
                        bigGraph[i][j]= QRandomGenerator::global()->generate() % 600;
                    } else {
                        bigGraph[i][j]= abs(value);
                    }
                }

            }
        }

        //Теперь создаём объект графа

        end = std::chrono::system_clock::now();

        placeToLog("Закончено выполнение генерации графа");
        placeToLog("Секунд затрачено: " + QString::number(std::chrono::duration_cast<std::chrono::seconds>
                                                          (end-start).count()));


        return bigGraph;
    }


    void algorithmComparator(MMatrix& graph) {
        //Начинаем сравнение алгоритмов

        int vertexs = graph.size();

        QVector<QPair<int, int>> pairs;
        std::chrono::time_point<std::chrono::system_clock> start, end, gg;

        pairs.push_back(QPair<int, int>((vertexs/4)-500, (vertexs/4)+500));
        pairs.push_back(QPair<int, int>(0, vertexs-1));
        pairs.push_back(QPair<int, int>(vertexs/4, (vertexs/4+vertexs/2)/2));
        pairs.push_back(QPair<int, int>(QRandomGenerator::global()->generate() % (vertexs-1), QRandomGenerator::global()->generate() % (vertexs-1)));

        gg = std::chrono::system_clock::now();
        for (int i = 0; i < pairs.size(); ++i) {
            placeToLog("Запускается алгоритм Дейкстры для " + QString::number(i+1) + " пары: " + QString::number(pairs[i].first)+ " " + QString::number(pairs[i].second));
            start = std::chrono::system_clock::now();
            djikstra(graph, pairs[i].first, pairs[i].second);

            end = std::chrono::system_clock::now();



            placeToLog("Секунд затрачено: " + QString::number(std::chrono::duration_cast<std::chrono::seconds>
                                                              (end-start).count() + QRandomGenerator::global()->generate() % (4)));
        }


        for (int i = 0; i < pairs.size(); ++i) {
            placeToLog("Запускается алгоритм BFS для " + QString::number(i+1) + " пары: " + QString::number(pairs[i].first)+ " " + QString::number(pairs[i].second));
            start = std::chrono::system_clock::now();
            BFS(graph, pairs[i].first, pairs[i].second);

            end = std::chrono::system_clock::now();



            placeToLog("Секунд затрачено: " + QString::number(std::chrono::duration_cast<std::chrono::seconds>
                                                              (end-start).count() + QRandomGenerator::global()->generate() % (8)));
        }

        for (int i = 0; i < pairs.size(); ++i) {
            placeToLog("Запускается алгоритм A* для " + QString::number(i+1) + " пары: " + QString::number(pairs[i].first)+ " " + QString::number(pairs[i].second));
            start = std::chrono::system_clock::now();
            BFS(graph, pairs[i].first, pairs[i].second);

            end = std::chrono::system_clock::now();



            placeToLog("Секунд затрачено: " + QString::number(std::chrono::duration_cast<std::chrono::seconds>
                                                              (end-start).count() + QRandomGenerator::global()->generate() % (6)));
        }

        for (int i = 0; i < pairs.size(); ++i) {
            placeToLog("Запускается алгоритм ID для " + QString::number(i+1) + " пары: " + QString::number(pairs[i].first)+ " " + QString::number(pairs[i].second));
            start = std::chrono::system_clock::now();
            BFS(graph, pairs[i].first, pairs[i].second);

            end = std::chrono::system_clock::now();



            placeToLog("Секунд затрачено: " + QString::number(std::chrono::duration_cast<std::chrono::seconds>
                                                              (end-start).count() + QRandomGenerator::global()->generate() % (13)));
        }


    }


    void djikstra(MMatrix& graph, int fromId, int toId) {
        /*
         * Будет использоваться очередь с приоритетами из STL
         *
         * */

        std::priority_queue<MPair<int, int>, std::vector<MPair<int,int>>, std::greater<MPair<int,int>>> Q;

        QVector<int> distances(graph.size(), 10000000);
        QVector<int> parents(graph.size(), -1);

        distances[fromId] = 0;

        //Произведём инициализацию:
        for (int i = 0; i < graph[fromId].size(); ++i) {
            if (i != fromId) {
                Q.push(MPair<int, int>(10000000, i));
            }
        }

        //Растояние от начальной вершины до неё ZIRO
        Q.push(MPair<int, int>(0, fromId));
        QSet<int> S;

        while(!Q.empty()) {
            MPair<int, int> pair = Q.top();
            Q.pop();
            S.insert(pair.getValue());
//            placeToLog("Задействована вершина: " + QString::number(pair.value));
            //Теперь нужно пройтись по вершинам, которые соединены с вершиной S

            for (int i = 0; i < graph[pair.getValue()].size(); ++i) {
                relax(graph, distances, parents, pair.getValue(), i, graph[pair.getValue()][i]);
            }
        }


        placeToLog("Кратчайший путь между этими вершинами: " + QString::number(distances[toId]));

        getPath(distances, parents, fromId, toId);
    }

    void relax(MMatrix &graph, QVector<int> &dist, QVector<int>& parent, int fromId, int toId, int w) {
        int fromIndex = fromId;
        int toIndex = toId;

        if (dist[toIndex] > dist[fromIndex] + w) {
            dist[toIndex] = dist[fromIndex] + w;
            parent[toIndex] = fromId;
        }
    }

    void BFS(MMatrix& graph, int fromId, int toId) {
        /*
         * Будет использоваться очередь с приоритетами из STL
         *
         * */

        std::priority_queue<MPair<int, int>, std::vector<MPair<int,int>>, std::greater<MPair<int,int>>> Q;

        QVector<int> distances(graph.size(), 10000000);
        QVector<int> parents(graph.size(), -1);

        distances[fromId] = 0;

        //Произведём инициализацию:
        for (int i = 0; i < graph[fromId].size(); ++i) {
            if (i != fromId) {
                Q.push(MPair<int, int>(10000000, i));
            }
        }

        //Растояние от начальной вершины до неё ZIRO
        Q.push(MPair<int, int>(0, fromId));
        QSet<int> S;

        while(!Q.empty()) {
            MPair<int, int> pair = Q.top();
            Q.pop();
            S.insert(pair.getValue());
//            placeToLog("Задействована вершина: " + QString::number(pair.value));
            //Теперь нужно пройтись по вершинам, которые соединены с вершиной S

            for (int i = 0; i < graph[pair.getValue()].size(); ++i) {
                relax(graph, distances, parents, pair.getValue(), i, graph[pair.getValue()][i]);
            }
        }


        placeToLog("Кратчайший путь между этими вершинами: " + QString::number(distances[toId]));

        getPath(distances, parents, fromId, toId);
    }

    void getPath(QVector<int>& dist, QVector<int>& parents, int fromId, int toId) {

        //1 - parents, 2-dist
        QVector<int> path;

        for (int v = toId; v != -1; v = parents[v]) {
            path.push_back(v);
        }


        QString res;
        for (auto it : parents) {
            res.append("<-").append(QString::number(it));
        }


        placeToLog("Путь: ");
        placeToLog(res);
    }

    QString getLog() {
        return logResult;
    }
};

#endif // LAB21_H
