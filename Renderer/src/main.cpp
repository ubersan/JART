#include <iostream>
#include <vector>
using namespace std;

#include "RayTracer/Camera.h"
#include "RayTracer/Scene.h"
#include "RayTracer/Sphere.h"
#include "RayTracer/Position.h"
#include "RayTracer/Direction.h"
#include "RayTracer/ImagePlane.h"
#include "ImageIO/ImageIO.h"

int main(int argc, char** argv)
{
    auto camera = Camera{Position{0.f, 0.f, 10.f}, Direction{0.f, 0.f, -1.f}, Direction{0.f, 1.f, 0.f}};

    auto s = new Sphere();
    auto scene = Scene(camera, {s});
    
    auto imagePlane = scene.Render();
    
    ImageIO::Export(imagePlane);

    return 0;
}