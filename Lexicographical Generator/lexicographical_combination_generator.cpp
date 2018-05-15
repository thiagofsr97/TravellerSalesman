//
// Created by thiagofsr on 14/05/18.
//

#include "lexicographical_combination_generator.h"
lexicographical_combination_generator::
lexicographical_combination_generator(size_t set_size, size_t combination_size)
{
    check_arguments(set_size, combination_size);
    m_set_size = set_size;
    m_combination_size = combination_size;

    for (size_t index = 0; index < m_combination_size; ++index)
    {
        m_indices.push_back(index);
    }
}

void lexicographical_combination_generator::
check_arguments(size_t set_size, size_t combination_size)
{
    if (combination_size > set_size)
    {
        std::stringstream ss;
        ss << "combination_size("
           << combination_size
           << ") > set_size("
           << set_size
           << ")";
        throw std::runtime_error{ss.str()};
    }

    if (set_size == 0)
    {
        std::stringstream ss;
        ss << "set_size is zero";
        throw std::runtime_error{ss.str()};
    }
}

bool lexicographical_combination_generator::increment()
{
    if (m_indices[m_combination_size - 1] < m_set_size - 1)
    {
        m_indices[m_combination_size - 1]++;
        return true;
    }

    for (int i = (int)(m_combination_size - 2); i >= 0; --i)
    {
        if (m_indices[i] < m_indices[i + 1] - 1)
        {
            m_indices[i]++;

            for (int j = i + 1; j < m_combination_size; ++j)
            {
                m_indices[j] = m_indices[j - 1] + 1;
            }

            return true;
        }
    }

    return false;
}

template<typename Iter>
void lexicographical_combination_generator::print( Iter begin) {
    for (size_t i = 0; i < get_combination_size(); ++i)
    {
        std::cout << get_combination_index(i);
    }

    std::cout << ": ";

    for (size_t i = 0; i < get_combination_size(); ++i)
    {
        auto iter = begin;
        std::advance(iter, get_combination_index(i));
        std::cout << *iter;
    }

    std::cout << "\n";
}



