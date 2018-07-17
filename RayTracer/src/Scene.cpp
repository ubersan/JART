#include "Scene.h"
#include "Sphere.h"
#include <fstream>
#include <iostream>

float clamp(float value)
{
    return std::max(0.f, std::min(1.f, value));
}

Scene::Scene()
    : _width(640), _height(480), _fov(30)
{
    _cameraToWorld << 1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 10, 1;
}

void Scene::AddSphere(const Eigen::Vector3f& center, float radius)
{
    _sceneObjects.push_back(std::make_unique<Sphere>(center, radius));
}

std::tuple<bool, float, IIntersectable*> Scene::Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, const std::vector<std::unique_ptr<IIntersectable>>& sceneObjects)
{
    const float kInfinity = std::numeric_limits<float>::max();
    auto tNear = kInfinity;
    IIntersectable* hitObject = nullptr;

    for (const auto& sceneObject : sceneObjects) {
        if (auto [success, t] = sceneObject->Intersect(origin, direction); success && t < tNear) {
            hitObject = sceneObject.get();
            tNear = t;
        }
    }

    return std::make_tuple(hitObject != nullptr, tNear, hitObject);
}

Eigen::Vector3f Scene::CastRay(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, const std::vector<std::unique_ptr<IIntersectable>>& sceneObjects)
{
    Eigen::Vector3f hitColor = Eigen::Vector3f::Zero();

    if (auto [success, t, hitObject] = Trace(origin, direction, sceneObjects); success)
    {
        // Dummy calculation to remove warnings.
        if (hitObject != nullptr)
        {
            hitColor *= t;
        }

        hitColor = Eigen::Vector3f(1.f, 1.f, 1.f);
    }

    return hitColor;
}

void Scene::exportToFile(const std::vector<Eigen::Vector3f>& pixels)
{
    std::ofstream ofs{"./out.ppm", std::ios::out | std::ios::binary};
    ofs << "P6" << std::endl
        << _width << " " << _height << std::endl
        << "255" << std::endl;
        
    for (auto i = 0; i < _height * _width; ++i) {
        auto mapped = (pixels[i].unaryExpr(std::ptr_fun(clamp)) * 255).cast<char>();
        ofs << mapped.x() << mapped.y() << mapped.z();
    }
}

void Scene::Render()
{
    auto pixels = std::vector<Eigen::Vector3f>(_width * _height);
    auto scale = tanf((_fov * 0.5f * M_PI / 180.0f));
    auto aspectRatio = _width / (float)_height;

    auto cameraToWorldBasis = _cameraToWorld.topLeftCorner<3, 3>();
    auto origin = cameraToWorldBasis*Eigen::Vector3f::Zero() + _cameraToWorld.row(3).leftCols<3>().transpose();
    auto pixelIter = pixels.begin();
    for (auto row = 0; row < _height; ++row) {
        for (auto col = 0; col < _width; ++col) {
            auto x = (2 * (col + 0.5f) / (float)_width - 1) * scale;
            auto y = (1 - 2 * (row + 0.5f) / (float)_height) * scale / aspectRatio;
            
            auto direction = (cameraToWorldBasis * Eigen::Vector3f(x, y, -1)).normalized();       
            *(pixelIter++) = CastRay(origin, direction, _sceneObjects);
        }
    }

    exportToFile(pixels);
}