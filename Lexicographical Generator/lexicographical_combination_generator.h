//
// Created by thiagofsr on 14/05/18.
//

#ifndef TRAVELLERSALESMAN_LEXICOGRAPHICAL_COMBINATION_GENERATOR_H
#define TRAVELLERSALESMAN_LEXICOGRAPHICAL_COMBINATION_GENERATOR_H


#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

class lexicographical_combination_generator {
public:
    lexicographical_combination_generator(size_t set_size,
                                          size_t combination_size);
    bool increment();
    size_t get_set_size()                      { return m_set_size; }
    size_t get_combination_size()              { return m_combination_size; }
    size_t get_combination_index(size_t index) { return m_indices[index]; }
    template<typename Iter>
    void print( Iter begin);
private:
    size_t              m_set_size;
    size_t              m_combination_size;
    std::vector<size_t> m_indices;

    void check_arguments(size_t set_size, size_t combination_size);
};






#endif //TRAVELLERSALESMAN_LEXICOGRAPHICAL_COMBINATION_GENERATOR_H
