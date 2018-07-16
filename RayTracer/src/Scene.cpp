#include "Scene.h"
#include <iostream>
using namespace std;

Scene::Scene(const Camera& camera, const vector<ITraceable*>& sceneObjects)
    : _camera(camera), _sceneObjects(sceneObjects), _imagePlane(ImagePlane{900, 600, camera.GetPosition() - Eigen::Vector3f{0.f, 0.f, 1.f}})
{
}

const ImagePlane& Scene::Render()
{
    // Assumption: ImagePlane is 1 unit away from the camera
    // With a FOV of 45 degrees this yields an imagePlane height
    // of 2 units and a corresponding width according to the pixel
    // ratio between widht and height
    auto pixelSize = 2.f / _imagePlane.Rows();
    auto imagePlaneWidth = pixelSize * _imagePlane.Columns();

    auto topLeftCenterX = -pixelSize * _imagePlane.Rows() / 2 + (pixelSize / 2.f);
    auto topLeftCenterY = pixelSize * _imagePlane.Columns() / 2 - (pixelSize / 2.f); 

    auto topLeft = Eigen::Vector3f(topLeftCenterX, topLeftCenterY, _camera.GetPosition().z() - 1.f);

    for (auto row = 0; row < _imagePlane.Rows(); ++row)
    {
        for (auto column = 0; column < _imagePlane.Columns(); ++column)
        {
            
            auto currentPixel = topLeft + Eigen::Vector3f(pixelSize * row, -pixelSize * column, 0.f);
            auto direction = (currentPixel - _camera.GetPosition()).normalized();

            auto pixel = Trace(_camera.GetPosition(), direction);

            _imagePlane.SetPixel(row, column, pixel);
        }
    }

    return _imagePlane;
}

Pixel Scene::Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const
{
    auto pixel = Pixel::Black();

    for (auto const& sceneObject : _sceneObjects)
    {
        pixel = sceneObject->Trace(origin, direction)
            ? Pixel::Red()
            : Pixel::Black();            
    }

    return pixel;
}