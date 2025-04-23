#ifndef RDATAGEN_AGEN_HPP
#define RDATAGEN_AGEN_HPP

#pragma once

//#include <array>
#include <chrono>
#include <ctime>
//#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <cstring>
#include <vector>


namespace RDataGen{
    namespace detail{
        template<typename T>
        T* RandomArrayRangeChunk(size_t length, T min_val, T max_val){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::uniform_int_distribution<T> randRange(min_val, max_val);
            std::mt19937 generator(seed);
            T* temp = new T[length];
            for (size_t i = 0; i < length; i++)
            {
                temp[i] = randRange(generator);
            }
            return temp;
        }
        template<typename T>
        void _FillArrayRange(T* dest, size_t length, T min_val, T max_val, size_t chunk_offset, std::mutex& mutex){
            T* vals = RandomArrayRangeChunk(length, min_val, max_val);
            {
                std::lock_guard<std::mutex> lock(mutex);
                std::memcpy(dest + chunk_offset, vals, length * sizeof(T));
            }
            delete[] vals;
        }
    }
    /**
     * @brief Fills an array with values within the min_val and max_val range with optional multithreading
     * 
     * @tparam T datatype of the array should be number
     * @param target_arr The array that is supposed to be filled with data
     * @param length The length of the array
     * @param min_val Lowest value to be generated
     * @param max_val Biggest value to be generated
     * @param threads Optional Ammount of threads to run the function on 
     */
    template<typename T>
    void FillArrayRange(T* target_arr, size_t length, T min_val, T max_val, int threads = -1){
        if (threads < 2)
        {
            T* vals = detail::RandomArrayRangeChunk(length, min_val, max_val);
            std::memcpy(target_arr, vals, length * sizeof(T));
            delete[] vals;
        }
        else{
            std::vector<std::thread> _threads;
            _threads.reserve(threads);
            std::mutex mutex;
            size_t chunk_size = length/threads;
            size_t offset = 0;
            for (size_t i = 0; i < threads - 1; i++)
            {
                _threads.emplace_back(std::thread(detail::_FillArrayRange<T>, target_arr, chunk_size, min_val, max_val, offset, std::ref(mutex)));
                offset += chunk_size;
                length -= chunk_size;
            }
            _threads.emplace_back(std::thread(detail::_FillArrayRange<T>, target_arr, length, min_val, max_val, offset, std::ref(mutex)));
            
            for (size_t i = 0; i < threads; i++)
            {
                _threads[i].join();
            }
        }
    }
}

#endif //RDATAGEN_AGEN_HPP