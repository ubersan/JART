#pragma once

#include <vector>
#include <string>

#include "RayTracer/ImagePlane.h"

class ImageIO
{
public:
    static void Export(const std::vector<unsigned char>& imageData, int width, int height);
    static void Export(const ImagePlane& imagePlane);
    static ImagePlane Import(const std::string& filename);
};