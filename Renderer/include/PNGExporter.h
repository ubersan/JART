#pragma once

#include <vector>
#include "RayTracer/ImagePlane.h"

class PNGExporter
{
public:
    static void Export(const std::vector<unsigned char>& imageData, int width, int height);
    static void Export(const ImagePlane& imagePlane);
};