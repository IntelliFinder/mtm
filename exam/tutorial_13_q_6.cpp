#include <iostream>
using namespace std;

template<class T>
class A {
public:
A() { cout << "A::A()" << endl;	}
A(const A& a) : i(a.i) { cout << "A::A(A&)" << endl; }
private:
T i;
};

template<class T>
class B {
public:
    A<T> a;
    B(const A<T>& aa) : a(aa) { cout << "B::B(A)" << endl; }
    B(const B& b) :	a(b.a) { cout << "B::B(B&)" << endl; }

};

class C: public B<int> {
public:
    C(const A<int>& aa) : B<int> (aa) , a(aa) {
        cout << "C::C(A aa)" << endl; }
    ~C() { cout << "C::~C()" << endl; }
    A<int> a;
};


int main() {
    cout << "--1--" << endl;
    A<int> a;
    cout << "--2--" << endl;
    A<double> a1;
    cout<<"modified" << endl;
    A<int> aa(a);
    cout<<"--post initialization__" << endl;
    B<int> bbb(aa);
    cout << "--3--" << endl;
    B<int> b(a);
    cout << "--4--" << endl;
    B<int> b1(b);
    cout << "--5--" << endl;
    C c(a);
    cout << "--6--" << endl;
    B<int>& b2 = c;
    cout << "--7--" << endl;
    return 0;
}



