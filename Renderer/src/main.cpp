#include <Eigen/Core>
#include "RayTracer/Scene.h"

using namespace Eigen;

int main(int argc, char **argv)
{    
    auto scene = Scene(640, 480, 30);

    scene.AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f);
    scene.AddSphere(Vector3f{1.f, 1.f, -9.25f}, 0.25f);
    scene.AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f});
    
    scene.AddDirectionalLight(Vector3f{-0.5f, -1.f, 0.f}.normalized(), 1.f, Vector3f{1.f, 1.f, 1.f});
    
    scene.Render();

    return 0;
}
