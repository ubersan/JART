#pragma once

#include <vector>

#include "Camera.h"
#include "ITraceable.h"
#include "ImagePlane.h"

class Scene
{
public:
    Scene(const Camera& camera, const std::vector<ITraceable>& sceneObjects);

    ImagePlane Render();
private:

    Camera _camera;
    std::vector<ITraceable> _sceneObjects;
};