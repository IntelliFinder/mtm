#include <iostream>
#include <vector>


class BadInput: public std::exception {};

bool isInRangeStart(const int num,const int vectorSize){
    return num < vectorSize && num >= 0;
}
bool isInRangeStop(const int num,const int vectorSize) {
    return num <= vectorSize && num >= 0;
}
template <class T>
std::vector<T> slice(std::vector<T> vec, int start, int step, int stop) {
    if(!isInRangeStart(start, vec.size()) || !isInRangeStop(stop,vec.size())){
        throw BadInput();
    }
    if (step <= 0){
        throw BadInput();
    }
    std::vector<T> ans;
    for(int i = start; i<stop;i+=step){
        ans.push_back(vec[i]);
    }
    return ans;
}

int main() {
    // this syntax initializes a vector with values a,b,c,d,e
    std::vector<char> vec1 {'a', 'b', 'c', 'd', 'e'};
// returns vector with values a,c
    std::vector<char> vec_sliced = slice(vec1, 0, 2, 4);
    for (int i = 0; i < 2; ++i) {
        std::cout<<vec_sliced[i]<<",";
    }
    std::cout<<std::endl;
// returns vector with values b,c,d,e
    std::vector<char> vec_sliced2 = slice(vec1, 1, 1, 5);
    for (int i = 0; i < 4; ++i) {
        std::cout<<vec_sliced2[i]<<",";
    }
    return 0;
}