#include <array>
#include <../include/RDataGen/vgen.hpp>
#include <../include/RDataGen/extra.hpp>

using namespace RDataGen;

int main(int argc, char** argv ){
    std::array<long, 9> arr = {1,5566789809,3,5,6,7,8,9,0};
    std::vector<long> test2 = RandomVectorSpecific<long>(arr,4294967295/4,16);
    std::vector<long> test4 = RandomVectorSpecific<long>(arr,10);
    std::cout << test2.size() << "\n";
    std::cout << test4.size() << "\n";
    //CoutVectorSet(test2);
    return 0;
}  