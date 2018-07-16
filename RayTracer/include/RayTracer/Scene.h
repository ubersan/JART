#pragma once

#include <vector>
#include <memory>

#include "Camera.h"
#include "ITraceable.h"
#include "ImagePlane.h"
#include "Pixel.h"
#include "Position.h"
#include "Direction.h"

class Scene
{
public:
    Scene(const Camera& camera);

    void AddSphere(const Position& center, float radius);

    ImagePlane Render();
    Pixel Trace(const Position& origin, const Direction& direction) const;
private:

    Camera _camera;
    std::vector<std::unique_ptr<ITraceable>> _sceneObjects;
};