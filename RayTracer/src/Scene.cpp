#include "Scene.h"
#include "Sphere.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace Eigen;

float clampToUnitInterval(float value)
{
    return max(0.f, min(1.f, value));
}

Scene::Scene(const string& resultDirectory /* = "." */)
    : _width(640), _height(480), _fov(30), _resultDirectory(resultDirectory)
{
    _cameraToWorld << 1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 10, 1;
}

void Scene::AddSphere(const Vector3f& center, float radius)
{
    _sceneObjects.push_back(make_unique<Sphere>(center, radius));
}

tuple<bool, float, IIntersectable*> Scene::Trace(const Vector3f& origin, const Vector3f& direction, const vector<unique_ptr<IIntersectable>>& sceneObjects)
{
    auto tNear = numeric_limits<float>::max();
    IIntersectable* hitObject = nullptr;

    for (const auto& sceneObject : sceneObjects) {
        if (auto [success, t] = sceneObject->Intersect(origin, direction); success && t < tNear) {
            hitObject = sceneObject.get();
            tNear = t;
        }
    }

    return make_tuple(hitObject != nullptr, tNear, hitObject);
}

Vector3f Scene::CastRay(const Vector3f& origin, const Vector3f& direction, const vector<unique_ptr<IIntersectable>>& sceneObjects)
{
    Vector3f hitColor = Vector3f::Zero();

    if (auto [success, t, hitObject] = Trace(origin, direction, sceneObjects); success)
    {
        // Dummy calculation to remove warnings.
        if (hitObject != nullptr)
        {
            hitColor *= t;
        }

        hitColor = Vector3f(1.f, 1.f, 1.f);
    }

    return hitColor;
}

void Scene::exportToFile(const vector<Vector3f>& pixels)
{
    ofstream ofs{_resultDirectory + "/out.ppm", ios::out | ios::binary};
    ofs << "P6" << endl
        << _width << " " << _height << endl
        << "255" << endl;
        
    for (auto i = 0; i < _height * _width; ++i) {
        auto mapped = (pixels[i].unaryExpr(ptr_fun(clampToUnitInterval)) * 255).cast<char>();
        ofs << mapped.x() << mapped.y() << mapped.z();
    }
}

void Scene::Render()
{
    auto pixels = vector<Vector3f>(_width * _height);
    auto scale = tanf((_fov * 0.5f * M_PI / 180.0f));
    auto aspectRatio = _width / (float)_height;

    auto cameraToWorldBasis = _cameraToWorld.topLeftCorner<3, 3>();
    auto origin = cameraToWorldBasis*Vector3f::Zero() + _cameraToWorld.row(3).leftCols<3>().transpose();
    auto pixelIter = pixels.begin();
    for (auto row = 0; row < _height; ++row) {
        for (auto col = 0; col < _width; ++col) {
            auto x = (2 * (col + 0.5f) / (float)_width - 1) * scale;
            auto y = (1 - 2 * (row + 0.5f) / (float)_height) * scale / aspectRatio;
            
            auto direction = (cameraToWorldBasis * Vector3f(x, y, -1)).normalized();       
            *(pixelIter++) = CastRay(origin, direction, _sceneObjects);
        }
    }

    exportToFile(pixels);
}