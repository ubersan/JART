#include <iostream>
#include <vector>
using namespace std;

#include "RayTracer/Camera.h"
#include "RayTracer/Scene.h"
#include "RayTracer/Sphere.h"
#include "RayTracer/ImagePlane.h"
#include "PNGExporter.h"

int main(int argc, char** argv)
{
    auto camera = Camera();

    auto s = Sphere();
    auto scene = Scene(camera, {s});
    auto imagePlane = scene.Render();

    PNGExporter::Export(imagePlane);

    return 0;
}