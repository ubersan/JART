#pragma once

#include <vector>

#include "Camera.h"
#include "ITraceable.h"
#include "ImagePlane.h"
#include "Pixel.h"

class Scene
{
public:
    Scene(const Camera& camera, const std::vector<ITraceable*>& sceneObjects);

    const ImagePlane& Render();
    Pixel Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const;
private:

    Camera _camera;
    std::vector<ITraceable*> _sceneObjects;
    ImagePlane _imagePlane;
};