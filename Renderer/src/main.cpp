#include <Eigen/Core>
#include "RayTracer/Scene.h"

int main(int argc, char **argv)
{    
    auto scene = Scene();
    scene.AddSphere(Eigen::Vector3f(2.f, 2.f, -10.f), 1.f);
    scene.Render();

    return 0;
}
