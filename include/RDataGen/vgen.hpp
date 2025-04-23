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
    namespace detail{
        template<typename T, std::size_t N>
        T* RandomArraySpecific(std::array<T, N>& values, size_t length){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::uniform_int_distribution<T> randRange(0, N - 1);
            std::mt19937 generator(seed);
            T* temp = new T[length];

            for (size_t i = 0; i < length; i++)
            {
                temp[i] = values[randRange(generator)];
            }
            return temp;
        }
        template<typename T, std::size_t N>
        void _RandomVectorSpecific(std::array<T, N>& values,size_t length, std::vector<T>& dest, std::mutex& mutex){
            T* vals = RandomArraySpecific(values,length);
            {
                std::lock_guard<std::mutex> lock(mutex);
                dest.insert(dest.end(),vals,vals + length);
            }
            delete[] vals;
        }
    }
    /**
     * @brief Function that returns a vector of a selected size filled with specific values from the passed std::array with the optional use of multithreading
     * 
     * @tparam T Datatype to be used for array and returned vector
     * @param values Takes a reference to an std::array with which values are to be used in the returned vector
     * @param length Sets the ammount of members the returned std::vector should have
     * @param threads Optional Ammount of threads to run the function on 
     * @return std::vector<T> 
     */
    template<typename T, std::size_t N>
    std::vector<T> RandomVectorSpecific(std::array<T, N>& values,size_t length, int threads = -1){
        std::vector<T> finalVector;
        finalVector.reserve(length);
        if (threads < 2)
        {
            T* vals = detail::RandomArraySpecific(values,length);
            finalVector.insert(finalVector.end(),vals,vals + length);
            delete[] vals;
        }
        else{
            std::vector<std::thread> _threads;
            _threads.reserve(threads);
            std::mutex mutex;
            size_t chunk_size = length/threads;

            for (size_t i = 0; i < threads - 1; i++)
            {
                _threads.emplace_back(std::thread(detail::_RandomVectorSpecific<T, N>, std::ref(values), chunk_size, std::ref(finalVector), std::ref(mutex)));
                length -= chunk_size;
            }
            _threads.emplace_back(std::thread(detail::_RandomVectorSpecific<T, N>, std::ref(values), length, std::ref(finalVector), std::ref(mutex)));
            
            for (size_t i = 0; i < threads; i++)
            {
                _threads[i].join();
            }
        }
        return finalVector;
    }

}

#endif //RDATAGEN_VGEN_HPP