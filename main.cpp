#include <iostream>
#include <FileReader.h>
#include <algorithm>
#include <regex>
#include <functional>

#define MIN(a,b) return a<b?a:b

unsigned long long combinations(unsigned long long n, unsigned long long k) {
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


template <typename Iterator>
Iterator find_next_increase_position(Iterator begin, Iterator combination_end, Iterator end);

template <typename Iterator>
bool next_combination(Iterator begin, Iterator end, unsigned k) {
    const auto combination_end = begin+k;
    const auto next_move = find_next_increase_position(begin, combination_end, end);
    if (next_move == end) return false;
    const auto previous_value = *next_move;
    std::inplace_merge(next_move, combination_end, end);
    const auto next_rotation =
            std::rotate(next_move, std::upper_bound(next_move, end, previous_value), end);
    std::rotate(combination_end, next_rotation, end);
    return true;
}

template <typename Iterator>
Iterator find_next_increase_position(Iterator begin, Iterator combination_end, Iterator end) {
    auto pos = std::upper_bound(std::reverse_iterator<Iterator>(combination_end),
                                std::reverse_iterator<Iterator>(begin),
                                *--end,
                                std::greater<typename Iterator::value_type>());
    if (pos.base() == begin)
        return ++end;
    return --pos.base();
}

int tsp(Graph* graph){
    std::vector<int> vertices;
    std::vector<int> verticesGet;
    int numberOfCombinations;
    int numberOfCombinationsInternal;

    //source is always 0
    //setting values when |S| = 0
    Node* current;
    int index = 0;
    int sizeS;
    int count;
    int selected;
    int matrixSize  = graph->getAllNodes().size();
    for(int i = 1; i < matrixSize;++i){
        graph->setDPValue(i,index++,vertices,graph->getWeigth(i,0));
    }

    for(sizeS = 1;sizeS<matrixSize-1;++sizeS){
        numberOfCombinations = combinations(matrixSize-2,sizeS);
        numberOfCombinationsInternal = combinations(sizeS,sizeS-1);


        for(int i = 1;i<matrixSize;++i){
            current = graph->getNode(i);
            auto neighbors = current->getNeighbors();


            for (int j = 0; j < neighbors.size(); j++) {
                if (neighbors.at(j)->getIdentifier() == 0) {
                    neighbors.erase(neighbors.begin() + j);
                }
            }
            int countCombination = 1;

            do{
                int minValue = INT_MAX;
                std::cout << "Viznhos: ";
                auto neighborsCpy = neighbors;

                selected = 0;


                count = 1;
                do{

                    verticesGet.push_back(neighborsCpy[selected]->getIdentifier());
                    for(int j = 0; j < sizeS;j++){
                        if(neighborsCpy[j]->getIdentifier()!=verticesGet.front())
                            verticesGet.push_back(neighborsCpy[j]->getIdentifier());
                    }

                    std::cout << current->getIdentifier() << " ";
                    for(auto v:verticesGet){
                        std::cout << v << " ";
                    }
                    std::cout << "\n\n";
                    int value = graph->getWeigth(current->getIdentifier(),neighborsCpy[selected]->getIdentifier()) + graph->getDPValue(neighborsCpy[selected]->getIdentifier(),sizeS-1,verticesGet);
                    std::cout << "Value " <<value << "\n";

                    if(value < minValue)
                        minValue = value;
                    selected++;
                    verticesGet.clear();


                }while(count++ < numberOfCombinationsInternal);


                for(int j = 0; j < sizeS;j++){
                    vertices.push_back(neighbors[j]->getIdentifier());
                }



                graph->setDPValue(current->getIdentifier(),index++,vertices,minValue);
                vertices.clear();



            }while(countCombination++ < numberOfCombinations && next_combination(neighbors.begin(),neighbors.end(),sizeS));
        }
    }

    sizeS = matrixSize -1;
    count =1;
    numberOfCombinationsInternal = combinations(matrixSize-1,sizeS-1);



    current = graph->getNode(0);
    auto neighbors = current->getNeighbors();
    int minValue = INT_MAX;
    for(auto v:neighbors){
        vertices.push_back(v->getIdentifier());
    };
    selected = 0;
    do{
        verticesGet.push_back(neighbors[selected]->getIdentifier());
        for(int i =0; i<neighbors.size();i++){
            if(neighbors[i]->getIdentifier() != neighbors[selected]->getIdentifier()){
                verticesGet.push_back(neighbors[i]->getIdentifier());
            }
        }

        int value = graph->getWeigth(current->getIdentifier(), neighbors[selected]->getIdentifier()) +
                    graph->getDPValue(neighbors[selected]->getIdentifier(), sizeS - 1, verticesGet);
        selected++;
        if (value < minValue) {
            minValue = value;
        }
        verticesGet.clear();


    }while(count++ < numberOfCombinationsInternal);
    graph->setDPValue(current->getIdentifier(),index++,vertices,minValue);








}


int main(int argc, char**argv) {
//    if(argc < 2){
//        std::cout<< "Missing or wrong arguments.\n";
//        exit(1);
//    }
    FileReader fileReader("../instancias_PCV/test.txt");
    Graph *graph = fileReader.createGraph();
    tsp(graph);
    //graph->showMatrix();
    graph->showDPMatrix();



    return 0;
}