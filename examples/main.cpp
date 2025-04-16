#include <array>
#include <../include/RDataGen/vgen.hpp>

using namespace RDataGen;

int main(int argc, char** argv ){
    std::array<long, 9> arr = {1,5566789809,3,5,6,7,8,9,0};
    //std::vector<long> test = RandomFillVector<long>(arr,__INT_MAX__);
    std::vector<long> test = RandomFillVectorThreaded<long>(arr,4294967295,16);
    CoutVectorSet(test);
    std::cout << test.size() << "\n";
    return 0;
}  