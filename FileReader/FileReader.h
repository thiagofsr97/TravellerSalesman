//
// Created by thiagofsr on 13/05/18.
//

#ifndef TRAVELLERSALESMAN_FILEREADER_H
#define TRAVELLERSALESMAN_FILEREADER_H


#include <fstream>
#include <iostream>
#include "../Graph/Graph.h"

class FileReader {
private:
    std::fstream *inputFile;

public:
    FileReader(const std::string& pathFile);
    ~FileReader();
    Graph* createGraph();




};


#endif //TRAVELLERSALESMAN_FILEREADER_H
