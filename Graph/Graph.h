
#ifndef TRAVELLERSALESMAN_GRAPH_H
#define TRAVELLERSALESMAN_GRAPH_H


#include <vector>
#include <array>
#include "../Node/Node.h"
class Graph {
private:
    typedef std::pair<std::vector<int>,int> mapping;
    std::vector<Node*> nodes;
    int *array;
    int *dpMatrix;
    mapping* dpMatrix_;

    int matrixSize;
    int dpMatrixSize;
    int GetIndex(int u, int v);
public:
    Graph(int matrixSize,int arraySize);
    ~Graph();
    void addNode(Node* node);
    Node* getNode(int identifier);
    std::vector<Node*> getAllNodes();
    void setWeightMatrix( int u, int v,int weight);
    void addWeightMatrix(int i,int weight);
    int getWeigth(int u , int v);
    int getDPValue(int i, int sizeS,int offset);
    int getDPValue(int i, int sizeS,std::vector<int> vertices);
    void setDPValue(int i,int index,std::vector<int>vertices,int value);
    void setDPValue(int i, int sizeS, int offset,int value);
    void showDPMatrix();
    void showMatrix();
    void showNeighbors();



};


#endif //TRAVELLERSALESMAN_GRAPH_H
