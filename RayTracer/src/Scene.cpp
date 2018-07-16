#include "Scene.h"
#include "Direction.h"

#include <iostream>
using namespace std;

Scene::Scene(const Camera& camera, const vector<ITraceable*>& sceneObjects)
    : _camera(camera), _sceneObjects(sceneObjects)
{
}

ImagePlane Scene::Render()
{
    auto pixelSize = _camera.GetPixelSize();
    auto topLeft = _camera.GetTopLeftPixelPosition();

    for (auto row = 0; row < _camera.Rows(); ++row)
    {
        for (auto column = 0; column < _camera.Columns(); ++column)
        {     
            auto const currentPixel = topLeft + Position{pixelSize * row, -pixelSize * column, 0.f};
            auto offsetVector = currentPixel - _camera.GetPosition();
            auto direction = Direction{offsetVector.X(), offsetVector.Y(), offsetVector.Z()};

            auto pixel = Trace(_camera.GetPosition(), direction);

            _camera.SetPixel(row, column, pixel);
        }
    }

    return _camera.GetImagePlane();
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