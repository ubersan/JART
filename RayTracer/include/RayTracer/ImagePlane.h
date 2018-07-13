#pragma once

#include <vector>

#include "Pixel.h"

class ImagePlane
{
public:
    ImagePlane(int widht, int height);

    std::vector<unsigned char> GetPixelsInRGBAFormat() const;

    int Width() const;
    int Height() const;

private:
    unsigned char* GetDataPointer() const;

    int _width;
    int _height;

    std::vector<Pixel> _pixels;
};