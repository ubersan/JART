#include <Eigen/Core>
#include "RayTracer/Scene.h"

using namespace Eigen;

int main(int argc, char **argv)
{    
    auto scene = Scene();
    scene.AddSphere(Vector3f(2.f, 2.f, -10.f), 1.f);
    scene.Render(); 

    return 0;
}
