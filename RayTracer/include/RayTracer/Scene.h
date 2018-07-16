#pragma once

#include <vector>

#include "Camera.h"
#include "ITraceable.h"
#include "ImagePlane.h"
#include "Pixel.h"
#include "Position.h"
#include "Direction.h"

class Scene
{
public:
    Scene(const Camera& camera, const std::vector<ITraceable*>& sceneObjects);

    ImagePlane Render();
    Pixel Trace(const Position& origin, const Direction& direction) const;
private:

    Camera _camera;
    std::vector<ITraceable*> _sceneObjects;
};