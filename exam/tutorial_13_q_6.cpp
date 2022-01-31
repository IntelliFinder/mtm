#include <iostream>
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
    A* a = new B();
    a->f();
    return 0;
}
