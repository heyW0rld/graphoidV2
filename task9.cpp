//#include "task9.h"

//#include <QMessageBox>

////#include BOOST_TT_HAS_OPERATOR_HPP_INCLUDED

//#include <boost/graph/adjacency_list.hpp>

//#include <boost/graph/properties.hpp>

//#include <boost/graph/graph_traits.hpp>

//#include <boost/property_map/property_map.hpp>

//#include <boost/ref.hpp>

//#include <vector>

//#include <boost/property_map/property_map.hpp>

//#include "planar_dual.h"

//#include <boost/tuple/tuple.hpp>

//#include <boost/graph/property_maps/container_property_map.hpp>

//#include <boost/graph/boyer_myrvold_planar_test.hpp>

//#include <boost/graph/is_kuratowski_subgraph.hpp>

//#ifndef Q_MOC_RUN
//#include <boost/graph/planar_detail/boyer_myrvold_impl.hpp>
// //#include <boost/graph/is_kuratowski_subgraph.hpp>
//#endif

//using namespace boost;
//using namespace std;

//Graph lab9(Graph gr, QVector < QVector < int >> matrix) {
////проверка на плоскость, между ребрами ищется общая точка
////смежные ребра не учитываются, тк они рисуются из одной точки и их легко перерисовать плоско
//  bool plosk = true;
//  auto all_vertex = gr.getVertexAsKeys();
//  for (auto ver1: all_vertex) {
//    for (auto ver2: all_vertex) {
//      if (ver1->getName() != ver2->getName()) {
//        for (auto edge1: gr.vertexAt(ver1)) {
//          for (auto edge2: gr.vertexAt(ver2)) {
//            //1
//            //откуда
//            qDebug() << ver1->getName();
//            qDebug() << edge1->getVertex()->getName();
//            qDebug() << ver2->getName();
//            qDebug() << edge2->getVertex()->getName();
//            QPoint p = ver1->getPoint();
//            int x1 = p.x();
//            int y1 = p.y();
//            //середина
//            int x2 = edge1->getPoint().x();
//            int y2 = edge1->getPoint().y();
//            //куда
//            QPoint p1 = edge1->getVertex()->getPoint();
//            int x = p1.x();
//            int y = p1.y();
//            //2
//            //откуда
//            QPoint p2 = ver2->getPoint();
//            int x3 = p2.x();
//            int y3 = p2.y();
//            //середина
//            int x4 = edge2->getPoint().x();
//            int y4 = edge2->getPoint().y();
//            //куда
//            QPoint p3 = edge2->getVertex()->getPoint();
//            int xx = p3.x();
//            int yy = p3.y();
//            if (edge1->getVertex()->getName() != ver2->getName() &&
//              ver1->getName() != edge2->getVertex()->getName() &&
//              edge1->getVertex()->getName() != edge2->getVertex()->getName()) {
//              double Ua, Ub, numerator_a, numerator_b, denominator;
//              //1.1
//              denominator = (y4 - y3) * (x1 - x2) - (x4 - x3) * (y1 - y2);
//              if (denominator == 0.0) {
//                if ((x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1) == 0 && (x1 * y2 - x2 * y1) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y2 - y1) == 0) {
//                  qDebug() << "Отрезки пересекаются";
//                  plosk = false;
//                } else qDebug() << "Отрезки не пересекаются";
//              } else {
//                numerator_a = (x4 - x2) * (y4 - y3) - (x4 - x3) * (y4 - y2);
//                numerator_b = (x1 - x2) * (y4 - y2) - (x4 - x2) * (y1 - y2);
//                Ua = numerator_a / denominator;
//                Ub = numerator_b / denominator;

//                if ((Ua >= 0.0 && Ua <= 1.0 && Ub >= 0.0 && Ub <= 1.0 ? true : false)) {
//                  qDebug() << "пересечение";
//                  plosk = false;
//                }
//              }
//              //2.1
//              denominator = (y4 - y3) * (x2 - x) - (x4 - x3) * (y2 - y);
//              if (denominator == 0.0) {
//                if ((x2 * y - x * y2) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x - x2) == 0 && (x2 * y - x * y2) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y - y2) == 0) {
//                  qDebug() << "Отрезки пересекаются";
//                  plosk = false;
//                } else qDebug() << "Отрезки не пересекаются";
//              } else {
//                numerator_a = (x4 - x) * (y4 - y3) - (x4 - x3) * (y4 - y);
//                numerator_b = (x2 - x) * (y4 - y) - (x4 - x) * (y2 - y);
//                Ua = numerator_a / denominator;
//                Ub = numerator_b / denominator;

//                if ((Ua >= 0.0 && Ua <= 1.0 && Ub >= 0.0 && Ub <= 1.0 ? true : false)) {
//                  qDebug() << "пересечение";
//                  plosk = false;
//                }
//              }
//              //1.2
//              denominator = (yy - y4) * (x1 - x2) - (xx - x4) * (y1 - y2);
//              if (denominator == 0.0) {
//                if ((x1 * y2 - x2 * y1) * (xx - x4) - (x4 * yy - xx * y4) * (x2 - x1) == 0 && (x1 * y2 - x2 * y1) * (yy - y4) - (x4 * yy - xx * y4) * (y2 - y1) == 0) {
//                  qDebug() << "Отрезки пересекаются";
//                  plosk = false;
//                } else qDebug() << "Отрезки не пересекаются";
//              } else {
//                numerator_a = (xx - x2) * (yy - y4) - (xx - x4) * (yy - y2);
//                numerator_b = (x1 - x2) * (yy - y2) - (xx - x2) * (y1 - y2);
//                Ua = numerator_a / denominator;
//                Ub = numerator_b / denominator;

//                if ((Ua >= 0.0 && Ua <= 1.0 && Ub >= 0.0 && Ub <= 1.0 ? true : false)) {
//                  qDebug() << "пересечение";
//                  plosk = false;
//                }
//              }
//              //2.2
//              denominator = (yy - y4) * (x2 - x) - (xx - x4) * (y2 - y);
//              if (denominator == 0.0) {
//                if ((x2 * y - x * y2) * (xx - x4) - (x4 * yy - xx * y4) * (x - x2) == 0 && (x2 * y - x * y2) * (yy - y4) - (xx * yy - xx * y4) * (y - y2) == 0) {
//                  qDebug() << "Отрезки пересекаются";
//                  plosk = false;
//                } else qDebug() << "Отрезки не пересекаются";
//              } else {
//                numerator_a = (xx - x) * (yy - y4) - (xx - x4) * (yy - y);
//                numerator_b = (x2 - x) * (yy - y) - (xx - x) * (y2 - y);
//                Ua = numerator_a / denominator;
//                Ub = numerator_b / denominator;

//                if ((Ua >= 0.0 && Ua <= 1.0 && Ub >= 0.0 && Ub <= 1.0 ? true : false)) {
//                  qDebug() << "пересечение";
//                  plosk = false;
//                }
//              }
//            }
//          }
//        }
//      }
//    }
//  }

//  if (plosk) {
//    QMessageBox msgBox;
//    msgBox.setText("граф плоский");
//    msgBox.exec();
//  } else {
//    QMessageBox msgBox;
//    msgBox.setText("граф не плоский");
//    msgBox.exec();
//  }
//    //определяется планарность по теореме куратовского к5 и к3.3
//  bool ok = false;
//  typedef adjacency_list
//    <
//    vecS,
//    vecS,
//    undirectedS,
//    property < vertex_index_t, int > ,
//    property < edge_index_t, int >
//    >
//    graph;

//  graph g(matrix.size());

//  for (int i = 0; i < matrix.size(); ++i) {
//    for (int j = i; j < matrix.size(); ++j) {
//      if (matrix[i][j] != 0) {
//        add_edge(i, j, g);
//      }
//    }
//  }

//  property_map < graph, edge_index_t > ::type e_index = get(edge_index, g);
//  graph_traits < graph > ::edges_size_type edge_count = 0;
//  graph_traits < graph > ::edge_iterator ei, ei_end;
//  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
//    put(e_index, * ei, edge_count++);

//  // Test for planarity - we know it is not planar, we just want to
//  // compute the kuratowski subgraph as a side-effect
//  typedef std::vector < graph_traits < graph > ::edge_descriptor >
//    kuratowski_edges_t;
//  kuratowski_edges_t kuratowski_edges;
//  if (boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
//      boyer_myrvold_params::kuratowski_subgraph =
//      std::back_inserter(kuratowski_edges)
//    )) {
//    qDebug() << "Input graph is planar";
//    QMessageBox msgBox;
//    msgBox.setText("граф планарный");
//    msgBox.exec();
//    ok = true;
//  } else {
//    qDebug() << "Input graph is not planar";

//    qDebug() << "Edges in the Kuratowski subgraph: ";
//    kuratowski_edges_t::iterator ki, ki_end;
//    ki_end = kuratowski_edges.end();
//    qDebug() << "Is a kuratowski subgraph? ";
//    if (is_kuratowski_subgraph(g, kuratowski_edges.begin(), kuratowski_edges.end()))
//      qDebug() << "Yes.";
//    else
//      qDebug() << "No.";
//    QMessageBox msgBox;
//    msgBox.setText("граф непланарный");
//    msgBox.exec();
//  }
//  //строится двойственный граф для планарного

//  Graph grap;
//  if (ok) {
//    graph dual_g;
////через planar_dual строится сам граф, а точнее беру ребра из этого графа и рисую в наш граф
//    // Compute the planar embedding - we know the input graph is planar,
//    // so we're ignoring the return value of the test
//    typedef std::vector < graph_traits < graph > ::edge_descriptor > vec_t;
//    std::vector < vec_t > embedding(num_vertices(g));
//    boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
//      boyer_myrvold_params::embedding = & embedding[0]
//    );

//    create_dual_graph(g, dual_g, & embedding[0]);
//    qDebug() << num_edges(dual_g);
//    qDebug() << num_vertices(dual_g);

//    QVector < QVector < int >> outvec;
//    //не лучшее заполнение, но пока так
//    for (int i = 0; i < num_vertices(dual_g); ++i) {
//      QVector < int > vec;
//      for (int j = 0; j < num_vertices(dual_g); ++j) {
//        vec.append(0);
//      }
//      outvec.append(vec);
//    }
//    //прохожу по ребрам из нового, устанавливаю вес 1 на каждое ребро
//    //здесь матрица смежности
//    for (auto e: dual_g.m_edges) {
//      if(e.m_source !=e.m_target){
//      outvec[e.m_source][e.m_target] = outvec[e.m_source][e.m_target]+1;}
//      outvec[e.m_target][e.m_source] = outvec[e.m_target][e.m_source]+1;
////      outvec[e.m_target][e.m_source]
//      qDebug() << "  ";
//      qDebug() << e.m_source;
//      qDebug() << e.m_target;
//      int k = (int) e.m_source;
//      qDebug() << k;
//    }
//    qDebug() << outvec;
//    //по матрице смежности стандартное построение графа
//    for (int i = 0; i < outvec.size(); i++) {
//      vertex_smpt v(new Vertex("Ver" + QString::number(i), (1 + i) % 200 + rand() % 200, (1 + i) % 200 + rand() % 200));
//      v->setColor(Qt::green);
//      grap.insert(v, QList < edge_smpt > ());
//    }
//    QSet < vertex_smpt > set_vert = grap.getVertexAsKeys();
//    for (int i = 0; i < outvec.size(); i++) {
//      for (int j = i; j < outvec.size(); j++) {
//        while(outvec[i][j] >0){
//        if (i!=j) {
//          edge_smpt edge = edge_smpt(new Edge(set_vert.toList().at(i), set_vert.toList().at(j), 1));
//          edge->setVecEnd(true);
//          edge->setVecSrc(true);
//          grap[set_vert.toList().at(i)].append(edge);
//          outvec[i][j]--;
//        }else{
//            edge_smpt edge = edge_smpt(new Edge(set_vert.toList().at(i), set_vert.toList().at(j), 1));
//            edge->setPoint(set_vert.toList().at(i)->getPoint().x(), set_vert.toList().at(i)->getPoint().y() - VER_RADIUS > 0
//                           ? set_vert.toList().at(i)->getPoint().y() - VER_RADIUS : set_vert.toList().at(i)->getPoint().y() + VER_RADIUS);
//            edge->setVecEnd(true);
//            edge->setVecSrc(true);
//            grap[set_vert.toList().at(i)].append(edge);
//            outvec[i][j]--;

//        }
//        }
//      }
//    }
//  }
//  return grap;
//}
