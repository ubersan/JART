#include <Eigen/Core>
#include "RayTracer/Scene.h"

using namespace Eigen;

int main(int argc, char **argv)
{    
    auto scene = Scene(640, 480, 30);

    scene.AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f});
    
    scene.AddPointLight(Vector3f{0.f, -1.f, -10.f - sqrtf(5.f)/16.f}, 3.25f, Vector3f{1.f, 0.f, 0.f});
    scene.AddPointLight(Vector3f{-0.125f, -1.f, -10.f + sqrtf(5.f)/16.f}, 3.25f, Vector3f{0.f, 1.f, 0.f});
    scene.AddPointLight(Vector3f{0.125f, -1.f, -10.f + sqrtf(5.f)/16.f}, 3.25f, Vector3f{0.f, 0.f, 1.f});
    
    scene.SetCamera(Vector3f{1.f, 0.f, 0.f}, Vector3f{0.f, -1.f, 0.f}.normalized(), Vector3f{0.f, 2.5f, -10.f});

    scene.Render();

    return 0;
}
