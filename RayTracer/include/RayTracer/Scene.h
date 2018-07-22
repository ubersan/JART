#pragma once

#include <vector>
#include <memory>
#include <vector>
#include <string>

#include "IIntersectable.h"
#include "ILight.h"

#include <tuple>
#include <Eigen/Core>

class Scene
{
public:
    Scene(int width, int height, float fov, const std::string& resultDirectory = ".");
    
    void Render();

    void AddSphere(const Eigen::Vector3f& center, float radius, Material material);
    void AddPlane(const Eigen::Vector3f& pointOnPlane, const Eigen::Vector3f& normal, Material material);
    void AddPlane(const Eigen::Vector3f& pointOnPlane, const Eigen::Vector3f& normal, const Eigen::Vector3f& widthDirection, float width, float height, Material material);
    void AddTriangle(const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& c, Material material);

    void AddDirectionalLight(const Eigen::Vector3f& direction, float intensity, const Eigen::Vector3f& color);
    void AddPointLight(const Eigen::Vector3f& center, float intensity, const Eigen::Vector3f& color);
    
    void SetBackground(const Eigen::Vector3f& background);
    void SetCamera(const Eigen::Vector3f& right, const Eigen::Vector3f lookAt, const Eigen::Vector3f& position);

private:
    std::tuple<bool, float, IIntersectable*> Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, const std::vector<std::unique_ptr<IIntersectable>>& sceneObjects, float maxHitDistance = std::numeric_limits<float>::max());
    Eigen::Vector3f CastRay(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, const std::vector<std::unique_ptr<IIntersectable>>& sceneObjects, int depth);
    void exportToFile(const std::vector<Eigen::Vector3f>& pixels);
    
    int _width;
    int _height;
    float _fov;
    Eigen::Matrix4f _cameraToWorld;
    Eigen::Vector3f _background;

    std::string _resultDirectory;

    std::vector<std::unique_ptr<IIntersectable>> _sceneObjects;
    std::vector<std::unique_ptr<ILight>> _lights;
};