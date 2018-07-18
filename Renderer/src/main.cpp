#include <Eigen/Core>
#include "RayTracer/Scene.h"

using namespace Eigen;

int main(int argc, char **argv)
{    
    auto scene = Scene(640, 480, 30);

    scene.AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f});
    scene.AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f);

    scene.AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
    scene.SetBackground(Vector3f{0.36, 0.52f, 0.8f});

    scene.Render();

    return 0;
}
