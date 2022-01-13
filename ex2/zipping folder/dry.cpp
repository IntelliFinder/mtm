#include <iostream>
#include <vector>
#include <memory>


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
/**part A**/

/**part B**/
class A {
public:
    std::vector<std::shared_ptr<int>> values;
    void add(int x) {
        std::shared_ptr<int> p(new int(x));
        values.push_back(p);
    }
    ~A() =default;
};
int main() {
    A a, sliced;
    a.add(0); a.add(1); a.add(2); a.add(3); a.add(4); a.add(5);
    sliced.values = slice(a.values, 1, 1, 4);
    *(sliced.values[0]) = 800;
    std::cout << *(a.values[1]) << std::endl;
    return 0;
}

/*
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
}*/