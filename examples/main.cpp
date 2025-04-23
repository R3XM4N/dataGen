#include <array>
#include <iostream>
#include <../include/RDataGen/vgen.hpp>
#include <../include/RDataGen/agen.hpp>
#include <../include/RDataGen/extra.hpp>

using namespace RDataGen;

int main(int argc, char** argv ){
    //vecor with specific values and of size_t max members
    //std::array<int, 9> arr = {1,5569809,3,5,6,7,8,9,0};
    //std::vector<int> test2 = RandomVectorSpecific<int>(arr,4294967295,14);
    
    //std::vector<long> test4 = RandomVectorSpecific<long>(arr,10);
    //std::cout << test2.size() << "\n";
    
    //c array* of size_t max members
    //long* test5 = new long[4294967295];
    //FillArrayRange<long>(test5, 4294967295, -__INT_MAX__-1,__INT_MAX__, 14);
    //delete[] test5;
    
    //std::cout << test4.size() << "\n";
    //CoutVectorSet(test2);
    return 0;
}  