//
// Created by thiagofsr on 13/05/18.
//

#ifndef TRAVELLERSALESMAN_NODE_H
#define TRAVELLERSALESMAN_NODE_H

#include <string>
#include <map>
#include <climits>
#include <vector>

class Node {
private:
    int identifier;
    bool visited;
    int weight;
    int predecessorId;
    int rank;
    std::vector<Node*> neighbors;
public:
    Node(const int& id);

    void addNeighbor(Node* node);
    std::vector<Node*> getNeighbors();
    int getIdentifier();
    bool beenVisited();
    void switchState();
    int getWeight();
    int getRank();
    void setRank(int rank);
    void setWeight(int weight);
    void setPredecessorId(int id);
    int getPredecessorId();
    void clearSettings();
    bool operator <(Node& other);
};

#endif //TRAVELLERSALESMAN_NODE_H
