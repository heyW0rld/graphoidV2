#ifndef TASK8_H
#define TASK8_H
#include "graph.h"

void graphUnion(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphIntersection(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphSubtraction(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphImplication(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphCoimplication(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphXor(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphEquivalence(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphShefferStroke(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

void graphPirseArrow(const QVector<QVector<int>> &adjA, const QVector<QVector<int>> &adjB, QVector<QVector<int>> &adjC);

Graph binaryOperationsOnGraphs(int operation_index, Graph &gA, Graph &gB, QVector<QVector<int>> &adjC);

#endif // TASK8_H
