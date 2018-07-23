#include <Eigen/Core>

#include "RayTracer/Scene.h"
#include "RayTracer/Material.h"

using namespace Eigen;

int main(int argc, char **argv)
{    
    auto scene = Scene(640, 480, 30);

    scene.AddTriangle(Vector3f{2.5f, 0.f, -10.f}, Vector3f{-0.5f, 1.f, -10.f}, Vector3f{-1.5f, 0.5f, -10.f}, Material::DIFFUSE);
    scene.AddTriangle(Vector3f{1.5f, -1.f, -10.f}, Vector3f{-1.5f, 0.25f, -10.f}, Vector3f{-0.5f, -0.5f, -7.f}, Material::DIFFUSE);
    scene.AddDirectionalLight(Vector3f{0.f, 0.f, -1.f}, 1.f, Vector3f{1.f, 1.f, 1.f});

    scene.Render();

    return 0;
}