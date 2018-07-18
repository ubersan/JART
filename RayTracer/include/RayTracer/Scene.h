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
    void AddSphere(const Eigen::Vector3f& center, float radius);
    void AddDirectionalLight(const Eigen::Vector3f& direction, float intensity, const Eigen::Vector3f& color);
    void AddPointLight(const Eigen::Vector3f& center, float intensity, const Eigen::Vector3f& color);
    void SetCamera(const Eigen::Vector3f& right, const Eigen::Vector3f& up, const Eigen::Vector3f lookAt, const Eigen::Vector3f& position);

private:
    std::tuple<bool, float, IIntersectable*> Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, const std::vector<std::unique_ptr<IIntersectable>>& sceneObjects);
    Eigen::Vector3f CastRay(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, const std::vector<std::unique_ptr<IIntersectable>>& sceneObjects);
    void exportToFile(const std::vector<Eigen::Vector3f>& pixels);
    
    int _width;
    int _height;
    float _fov;
    Eigen::Matrix4f _cameraToWorld;

    std::string _resultDirectory;

    std::vector<std::unique_ptr<IIntersectable>> _sceneObjects;
    std::vector<std::unique_ptr<ILight>> _lights;
};