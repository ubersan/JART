#include "Scene.h"
using namespace std;

Scene::Scene(const Camera& camera, const vector<ITraceable>& sceneObjects)
    : _camera(camera), _sceneObjects(sceneObjects)
{
}

ImagePlane Scene::Render()
{
    return ImagePlane(900, 600);
}