#include "Scene.h"
#include "Direction.h"

#include <iostream>
using namespace std;

Scene::Scene(const Camera& camera, const vector<ITraceable*>& sceneObjects)
    : _camera(camera), _sceneObjects(sceneObjects), _imagePlane(ImagePlane{900, 600, camera.GetPosition() - Position{0.f, 0.f, 1.f}})
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

    auto topLeft = Position{topLeftCenterX, topLeftCenterY, _camera.GetPosition().Z() - 1.f};

    for (auto row = 0; row < _imagePlane.Rows(); ++row)
    {
        for (auto column = 0; column < _imagePlane.Columns(); ++column)
        {
            
            auto const currentPixel = topLeft + Position{pixelSize * row, -pixelSize * column, 0.f};
            auto offsetVector = currentPixel - _camera.GetPosition();
            auto direction = Direction{offsetVector.X(), offsetVector.Y(), offsetVector.Z()};

            auto pixel = Trace(_camera.GetPosition(), direction);

            _imagePlane.SetPixel(row, column, pixel);
        }
    }

    return _imagePlane;
}

Pixel Scene::Trace(const Position& origin, const Direction& direction) const
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