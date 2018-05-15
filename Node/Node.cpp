#include <iostream>
#include "Node.h"

Node::Node( int const &id) {
    this->identifier  = id;
    this->visited = false;
    this->weight = INT_MAX; //the algorithms requires this property to be initialized with infinity value
    this->predecessorId = -1;
    this->rank = 0;
}

void Node::addNeighbor(Node *node) {
    this->neighbors.push_back(node);

}

std::vector<Node*> Node::getNeighbors() {
    return this->neighbors;
}

int Node::getIdentifier() {
    return this->identifier;
}

bool Node::beenVisited() {
    return this->visited;
}

void Node::switchState(){
    this->visited = true;
}

int Node::getWeight() {
    return this->weight;
}

void Node::setWeight(int weight) {
    this->weight = weight;

}


void Node::clearSettings() {
    this->weight = INT_MAX;
    this->visited = false;
    this->rank = 0;
}

void Node::setPredecessorId(int id) {
    this->predecessorId = id;

}
int Node::getPredecessorId() {
    return this->predecessorId;
}

int Node::getRank() {
    return this->rank;
}

void Node::setRank(int rank) {
    this->rank = rank;
}

bool Node::operator<(Node& other) {
    return this->identifier < other.identifier;
}
