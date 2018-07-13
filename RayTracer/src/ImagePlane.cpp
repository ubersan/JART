#include "ImagePlane.h"

using namespace std;

ImagePlane::ImagePlane(int width, int height)
    : _width(width), _height(height), _pixels(vector<Pixel>(width*height, Pixel::Red()))
{
}

vector<unsigned char> ImagePlane::GetPixelsInRGBAFormat() const
{
    auto rawDataStart = GetDataPointer();
    auto rawDataEnd = GetDataPointer() + (_width*_height*4);
    vector<unsigned char> rgba(rawDataStart, rawDataEnd);

    return rgba;
}

int ImagePlane::Width() const
{
    return _width;
}

int ImagePlane::Height() const
{
    return _height;
}

unsigned char* ImagePlane::GetDataPointer() const
{
    return (unsigned char*)_pixels.data();
}