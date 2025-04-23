#ifndef RDATAGEN_EXTRA_HPP
#define RDATAGEN_EXTRA_HPP

#pragma once

#include <array>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

namespace RDataGen{
    /**
     * @brief Prints the vector to cout styled as "{n,n,n}" where n are numbers
     * 
     * @param targetVector What is supposed to be printed
     */
    template<typename T>
    void CoutVectorSet(std::vector<T>& targetVector){
        for (size_t i = 0; i < targetVector.size(); i++)
        {
            if (i == 0)
            {
                std::cout << "{" << targetVector[i] << ",";
            }
            else if(i == targetVector.size() - 1){
                std::cout << targetVector[i] << "}";
            }
            else{
                std::cout << targetVector[i] << ",";
            }
        }
        printf("\n");
    }
}

#endif //RDATAGEN_EXTRA_HPP