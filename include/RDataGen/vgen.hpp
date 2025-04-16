#ifndef RDATAGEN_VGEN_HPP
#define RDATAGEN_VGEN_HPP

#pragma once

#include <array>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

namespace RDataGen{
    /**
     * @brief Function that returns a vector of a selected size filled with numbers from array
     * 
     * @tparam T Datatype to be used for array and returned vector
     * @param numers Takes a reference to an array with which numbers are to be used in the returned vector
     * @param len Sets the ammount of members the returned std::vector should have
     * 
     * @return std::vector<T>
     */
    template<typename T, std::size_t N>
    std::vector<T> RandomFillVector(std::array<T, N>& numbers,size_t len){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        std::uniform_int_distribution<int> randRange(0, N);
    
        std::vector<T> temp;
        temp.reserve(len);
        for (size_t i = 0; i < len; i++)
        {
            temp.push_back(numbers[randRange(generator)]);
        }
        temp.shrink_to_fit();
        return temp;
    }
    namespace detail{
        /**
         * @brief Assistant function for multithreaded version of RandomFillVector, it handles the multithreaded generation of the vector by 
         * handling locking resources and assigning what chunks will certain threads generate not meant to be used by the user
         * 
         * @param numers Takes a reference to an array with which numbers are to be used in the returned vector
         * @param len The length of the desired vector 
         * @param dest Reference vector where the final data is going to be stored
         * @param mutex Mutex reference needed so all the cores know if they can acces destination vector
         */
        template<typename T, std::size_t N>
        void FRTAssist(std::array<T, N>& numbers,size_t len, std::vector<T>& dest, std::mutex& mutex){
            std::vector<T> temp = RandomFillVector(numbers,len);
            {
                std::lock_guard<std::mutex> lock(mutex);
                for (size_t i = 0; i < temp.size(); i++)
                {
                    dest.push_back(temp[i]);
                }
            }
        }
    }
    /**
     * @brief Function that returns a vector of a selected size filled with numbers from array with the use of multithreading
     * 
     * @tparam T Datatype to be used for array and returned vector
     * @param numers Takes a reference to an array with which numbers are to be used in the returned vector
     * @param len Sets the ammount of members the returned std::vector should have
     * @param tCount Ammount of threads to run the function on
     * @return std::vector<T> 
     */
    template<typename T, std::size_t N>
    std::vector<T> RandomFillVectorThreaded(std::array<T, N>& numbers,size_t len, int tCount){
        if (tCount > len) tCount = len;
        int clen = len/tCount;
    
        std::vector<T> temp;
        temp.reserve(len);
        
        std::vector<std::thread> threads;
        std::mutex mutex;
        if (tCount > 0)
        {
            for (size_t i = 0; i < tCount - 1; i++)
            {
                threads.emplace_back(std::thread(detail::FRTAssist<T, N>, std::ref(numbers), clen, std::ref(temp), std::ref(mutex)));
                len = len - clen;
            }
            threads.emplace_back(std::thread(detail::FRTAssist<T, N>, std::ref(numbers), len, std::ref(temp), std::ref(mutex)));
        }
        for (size_t i = 0; i < tCount; i++)
        {
            threads[i].join();
        }
        temp.shrink_to_fit();
        return temp;
    }
    /**
     * @brief Prints the vector to cout styled as "{n,n,n}" where n are numbers
     * 
     * @param targetVector What is supposed to be printed
     */
    template<typename T>
    void CoutVectorSet(std::vector<T>& targetVector){
        for (size_t i = 0; i < targetVector.size(); i++)
        {
            if (i == 1)
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

#endif //RDATAGEN_VGEN_HPP