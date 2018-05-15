#include <iostream>
#include <cmath>
#include "Graph.h"

unsigned long long choose(unsigned long long n, unsigned long long k) {
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

void Graph::addNode(Node *node) {
    nodes.push_back(node);
}

int Graph::GetIndex( int u, int v) {

    return ((matrixSize*u) + v);

}

Node *Graph::getNode(int identifier) {
    for(auto v: nodes){
        if(v->getIdentifier() == identifier){
            return v;
        }
    }
    return nullptr;
}

std::vector<Node*> Graph::getAllNodes() {
    return this->nodes;
}



int Graph::getWeigth( int u,  int v) {

    //::cout << "====== index======" << GetIndex(u,v) <<std::endl;
    return array[GetIndex(u,v)];
}


void Graph::setWeightMatrix( int u, int v,int weight) {
    int index = GetIndex(u,v);
    array[index] = weight;
}
void Graph::addWeightMatrix(int i, int weight){
    array[i] = weight;
}

Graph::Graph(int matrixSize, int arraySize) {
    this->matrixSize = matrixSize;
    this->array = new int[arraySize]();
    int size = matrixSize-1;
    this->dpMatrixSize = size;
    for(int s = 1;s < matrixSize;s++){
        this->dpMatrixSize+=((choose(size-1,s)) * size);
    }
    this->dpMatrixSize++; //last combination possible
    this->dpMatrix_= new mapping[dpMatrixSize];
    this->dpMatrix = new int[dpMatrixSize]();


}

Graph::~Graph() {
    //dealing with deallocationf of memorys
    delete[] this->array;
    delete[] this->dpMatrix;
    for(auto node:nodes){
        delete node;
    }
};



void Graph::showMatrix(){
    for(int i = 0;i<matrixSize;i++){
        for(int j = 0; j < matrixSize;j++){
            std::cout << getWeigth(i,j) << " ";

        }
        std::cout << std::endl;
    }

}

void Graph::showDPMatrix(){
    for(int i = 0;i<dpMatrixSize;i++){

        std::cout << "vertices: ";
        for(auto v: dpMatrix_[i].first){
            std::cout << v << " ";
        }
        std::cout << "\n";

        std::cout << dpMatrix_[i].second << std::endl;
    }

}

void Graph::showNeighbors() {

    for(auto u:nodes){
        std::cout << "Neighbors of " << u->getIdentifier() << " :";
        for(auto v:nodes.at(u->getIdentifier())->getNeighbors()){
            std::cout << v->getIdentifier() << " ";

        }
        std::cout << std::endl;
    }

}

void Graph::setDPValue(int i,int index,std::vector<int>vertices,int value) {



        vertices.insert(vertices.begin(),i);
        this->dpMatrix_[index]=mapping(vertices,value);


}



void Graph::setDPValue(int i, int sizeS, int offset,int value) {
   // std::cout << "\nSetting value: \n";
    int index;
    if(sizeS == 0){
        index = i -1;
        this->dpMatrix[i-1] = value;
    }
    else if(sizeS == matrixSize -1){
        index = dpMatrixSize -1;
        this->dpMatrix[dpMatrixSize-1] = value; //last element
    }
    else {
        int off = (matrixSize -1); // jumping values when |s| = 0
        if(sizeS > 1){
            off += (matrixSize-1) *choose(matrixSize - 2, sizeS-1); //jumping according to number of combinations possible in which |S|

        }

        off += (offset - 1); //selecting the element of the combination selected
        this->dpMatrix[off] = value;
        if(value == 15){
            std::cout <<"Value " <<off <<"\n";
        }

        index = off;
    }

   // std::cout << "index: " << index << " Value " << value <<"\n\n";
}

int Graph::getDPValue(int i, int sizeS,std::vector<int> vertices) {
    if(sizeS == 0){

        return this->dpMatrix_[i-1].second;
    }
    else if(sizeS == matrixSize -1){

        return this->dpMatrix_[dpMatrixSize-1].second; //last element
    }
    else {
        int count = sizeS;
        int off = 0;
        while(count--){
            off+= (matrixSize-1) *choose(matrixSize - 2, count);
        }


        for(int i = 0;i<choose(matrixSize-2,sizeS)*(matrixSize-1);i++){
           // std::cout << "Comparing 1: ";
//            for(auto v:vertices){
//                std::cout << v << " ";
//            }

///
   //         std::cout << std::endl;
            if(vertices == dpMatrix_[off + i].first) {
                return dpMatrix_[off + i].second;
            }
        }
        std::cout << "Not found" << std::endl;
        return -1;
    }
}

int Graph::getDPValue(int i, int sizeS, int offset) {
   // std::cout << "\ngetting value: \n";
    int index;
    if(sizeS == 0){
        index = i -1;
        //std::cout << "index: " << index << " Value " << dpMatrix[index] <<"\n\n";
        return this->dpMatrix[offset-1];
    }
    else if(sizeS == matrixSize -1){
        index = dpMatrixSize -1;
        //std::cout << "index: " << index << " Value " << dpMatrix[index] <<"\n\n";

        return this->dpMatrix[dpMatrixSize-1]; //last element
    }
    else {
        int off = (matrixSize -1); // jumping values when |s| = 0
        if(sizeS > 1){
            off += (matrixSize-1) *choose(matrixSize - 2, sizeS-1); //jumping according to number of combinations possible in which |S|

        }

        off += (offset - 1); //selecting the element of the combination selected
        index = off;
        //std::cout << "index: " << index << " Value " << dpMatrix[index] <<"\n\n";
        return this->dpMatrix[off];


    }
}
