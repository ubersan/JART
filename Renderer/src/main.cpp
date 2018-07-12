#include <iostream>
#include <vector>
using namespace std;

#include "RayTracer/Sphere.h"
#include "lodepng.h"

int main(int argc, char** argv)
{
    auto s = Sphere();
    cout << "hey" << endl;

    auto width = 300;
    auto height = 300;
    auto imageData = vector<unsigned char>(width*height*4, 255);
    auto error = lodepng::encode("test.png", imageData, width, height);
    cout << "error = " << error << endl;

    return 0;
}