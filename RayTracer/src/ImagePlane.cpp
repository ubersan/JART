#include "ImagePlane.h"
#include <iostream>
using namespace std;

ImagePlane::ImagePlane(int columns, int rows, const Position& position)
    : _columns(columns), _rows(rows), _position(position), _pixels(vector<Pixel>(columns*rows, Pixel::Black()))
{
}

ImagePlane::ImagePlane(int columns, int rows, const std::vector<unsigned char> imageData)
    : ImagePlane(columns, rows, Position{0.f, 0.f, 0.f})
{
    for (auto i = 0; i < imageData.size(); i += 4)
    {
        auto r = imageData[i];
        auto g = imageData[i + 1];
        auto b = imageData[i + 2];

        _pixels[i/4] = Pixel{r, g, b};
    }
}

vector<unsigned char> ImagePlane::GetPixelsInRGBAFormat() const
{
    auto rawDataStart = GetDataPointer();
    auto rawDataEnd = GetDataPointer() + (_columns*_rows*4);

    return vector<unsigned char>(rawDataStart, rawDataEnd);
}

int ImagePlane::Columns() const
{
    return _columns;
}

int ImagePlane::Rows() const
{
    return _rows;
}

void ImagePlane::SetPixel(int row, int column, const Pixel& pixel)
{
    _pixels[row*_columns + column] = pixel;
}

 Pixel ImagePlane::GetPixel(int row, int column) const
 {
     return _pixels[row*_columns + column];
 }

unsigned char* ImagePlane::GetDataPointer() const
{
    return (unsigned char*)_pixels.data();
}