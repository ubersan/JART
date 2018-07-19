#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include <fstream>
#include <iostream>

#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

float clampToUnitInterval(float value)
{
    return max(0.f, min(1.f, value));
}

Vector3f reflect(const Vector3f& incidentDirection, const Vector3f& normal)
{
    return incidentDirection - 2.f*normal.dot(incidentDirection)*normal;
}

Scene::Scene(int width, int height, float fov, const string& resultDirectory /* = "." */)
    : _width(width), _height(height), _fov(fov), _background(Vector3f::Zero()), _resultDirectory(resultDirectory)
{
    _cameraToWorld = Matrix4f::Identity();

    // By convention the camera looks along the negative z-axis.
    _cameraToWorld(2, 2) = -1.f;
}

void Scene::AddSphere(const Vector3f& center, float radius, Material material)
{
    _sceneObjects.push_back(make_unique<Sphere>(center, radius, material));
}

void Scene::AddDirectionalLight(const Vector3f& direction, float intensity, const Vector3f& color)
{
    _lights.push_back(make_unique<DirectionalLight>(direction, intensity, color));
}

void Scene::AddPointLight(const Vector3f& center, float intensity, const Vector3f& color)
{
    _lights.push_back(make_unique<PointLight>(center, intensity, color));
}

void Scene::AddPlane(const Eigen::Vector3f& pointOnPlane, const Eigen::Vector3f& normal, Material material)
{
    _sceneObjects.push_back(make_unique<Plane>(pointOnPlane, normal, material));
}

void Scene::AddPlane(const Eigen::Vector3f& center, const Eigen::Vector3f& normal, const Eigen::Vector3f& widthDirection, float totalWidth, float totalHeight, Material material)
{
    _sceneObjects.push_back(make_unique<Plane>(center, normal, widthDirection, totalWidth, totalHeight, material));
}

void Scene::SetBackground(const Eigen::Vector3f& background)
{
    _background = background;
}

void Scene::SetCamera(const Vector3f& right, const Vector3f lookAt, const Vector3f& position)
{
    auto up = right.cross(lookAt);

    _cameraToWorld << right.x(), right.y(), right.z(), 0,
                    up.x(), up.y(), up.z(), 0,
                    lookAt.x(), lookAt.y(), lookAt.z(), 0,
                    position.x(), position.y(), position.z(), 1;
}

tuple<bool, float, IIntersectable*> Scene::Trace(const Vector3f& origin, const Vector3f& direction, const vector<unique_ptr<IIntersectable>>& sceneObjects, float maxHitDistance /* = numeric_limits<float>::max() */)
{
    // In case of a shadow ray trace with a point light, we want to ignore all intersections, larger than the distance from the hitPoint to the light. This can be set via this parameter.
    auto tNear = maxHitDistance;
    IIntersectable* hitObject = nullptr;

    for (const auto& sceneObject : sceneObjects) {
        if (const auto [success, t] = sceneObject->Intersect(origin, direction); success && t < tNear) {
            hitObject = sceneObject.get();
            tNear = t;
        }
    }

    return make_tuple(hitObject != nullptr, tNear, hitObject);
}

Vector3f Scene::CastRay(const Vector3f& origin, const Vector3f& direction, const vector<unique_ptr<IIntersectable>>& sceneObjects)
{
    Vector3f hitColor = _background;

    // when no lights are present in the scene, we just do flat shading for debuggin.
    auto shadingIsEnabled = _lights.size() > 0;

    if (auto [success, t, hitObject] = Trace(origin, direction, sceneObjects); success)
    {
        hitColor = Vector3f(0.f, 0.f, 0.f);

        if (!shadingIsEnabled)
        {
            hitColor = Vector3f::Ones();
        }
        else
        {
            auto hitPoint = origin + t*direction;
            auto normal = hitObject->GetNormalAt(hitPoint);
            
            switch (hitObject->material)
            {
            case Material::DIFFUSE:
                for (const auto& light : _lights)
                {
                    auto toLight = light->GetToLightDirection(hitPoint);

                    // shadow ray
                    auto [isInShadow, tShadow, shadowHitObject] = Trace(hitPoint + normal*1e-4, toLight, sceneObjects, light->GetMaximalHitDistance(hitPoint));
                    auto isVisible = isInShadow ? 0.f : 1.f;

                    hitColor += isVisible * (light->GetContributionAccordingToDistance(hitPoint) * max(0.f, normal.dot(toLight)));
                }
                break;
            case Material::MIRROR:
                auto reflectionDirection = reflect(_cameraToWorld.row(2).leftCols(3), normal);
                hitColor += 0.8f * CastRay(hitPoint + normal*1e-4, reflectionDirection, sceneObjects);
                break;
            }
        }
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
            
            auto direction = (cameraToWorldBasis * Vector3f(x, y, 1)).normalized();     
            *(pixelIter++) = CastRay(origin, direction, _sceneObjects);
        }
    }

    exportToFile(pixels);
}