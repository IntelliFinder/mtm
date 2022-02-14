#include <iostream>
using std::cout;
using std::endl;
class Count{
    private:
        void UpdateBuildInfo(){
                                 int i =0 ;
                                 n = NumCountObjs + i;
                                 NumCountObjs++; }
        static int NumCountObjs;
        int i, n;
    public:
        Count() { i=10; UpdateBuildInfo(); }
        Count(Count *C) { i = C->i + 1; UpdateBuildInfo(); }
        Count(Count C) { i = C.i + 2; UpdateBuildInfo();  }
        //static Count(int i) { this.i = i; UpdateBuildInfo(); }
        int CompareBuildCount(Count C) { return n - C.n; }
        static GetNumObjs() { return NumCountObjs; }
        int getN() const { return n;}
};

int Count::NumCountObjs=0;


int main() {
    Count C0;
    cout << Count::GetNumObjs() << endl;
    cout << C0.getN() << endl;
    cout <<endl;
    Count C1(C0);
    cout << Count::GetNumObjs() << endl;
    cout << C1.getN() << endl;
    cout <<endl;
    Count C2(&C1);
    cout << Count::GetNumObjs() << endl;
    cout << C2.getN() << endl;
    cout <<endl;
    Count C3(C2);
    cout << Count::GetNumObjs() << endl;
    cout << C3.getN() << endl;

    cout << endl;
    cout << C1.CompareBuildCount(C3) <<endl;
    cout << Count::GetNumObjs() << endl;


    return 0;
}



