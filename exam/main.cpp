#include <iostream>
#include <list>
#include <vector>
using namespace std;
/**
class A{
    public:
        virtual void f(){
            cout << "1"<< endl;
        };
};
**/
class A{
    public:
        void f(){
          cout<<"1"<<endl;
        };
};


class B : public A{
    public:
        void f(){
          cout<<"2"<<endl;
        };
};

int main() {
    vector<int> l = {1 , 2 ,3};
    int val = l.back();
    l.pop_back();
    cout << val << "\n";
    cout << l.back() << "\n";
    return 0;
}
