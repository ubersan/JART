#include <iostream>
using namespace std;

#include "RayTracer/Test.h"

int main(int argc, char** argv)
{
    cout << "hey rays!" << endl;
    auto t = Test();
    cout << t.f() << endl;
    
    return 0;
}