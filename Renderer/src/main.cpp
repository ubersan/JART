#include <Eigen/Core>

#include "RayTracer/Scene.h"
#include "RayTracer/Material.h"

using namespace Eigen;

int main(int argc, char **argv)
{    
    auto scene = Scene(640, 480, 30);

    scene.AddPlane(Vector3f{0.f, -1.5f, -10.f}, Vector3f{0.f, 1.f, 0.f}, Vector3f{1.f, 0.f, 0.f}, 6.f, 15.5f, Material::MIRROR);
    scene.AddSphere(Vector3f{1.5f, -0.3f, -10.f}, 0.5f, Material::DIFFUSE);
    scene.AddSphere(Vector3f{0.f, -0.5f, -7.f}, 1.f, Material::DIFFUSE);
    scene.AddSphere(Vector3f{-3.f, -0.3f, -13.f}, 1.f, Material::DIFFUSE);

    scene.AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
    scene.SetBackground(Vector3f{0.36, 0.52f, 0.8f});
    scene.SetCamera(Vector3f{1.f, 0.f, 0.f}, Vector3f{0.f, -0.45f, -1.f}.normalized(), Vector3f{0.f, 6.5f, 10.f});

    scene.Render();

    return 0;
}