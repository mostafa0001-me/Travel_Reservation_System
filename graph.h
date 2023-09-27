#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include<list>
#include<QMainWindow>
using namespace std;

class Graph
{
    int V = 5;
    list<int> *adj;
    int shortPath[10];

public:
    int index;
    Graph();
    void addEdge(int v, int w, int weight);
    int* findShortestPath(int s, int d);
    int* printShortestPath(int parent[], int s, int d);
};
#endif // GRAPH_H
