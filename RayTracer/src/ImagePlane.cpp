#include "ImagePlane.h"

using namespace std;

ImagePlane::ImagePlane(int columns, int rows, const Eigen::Vector3f& position)
    : _columns(columns), _rows(rows), _position(position), _pixels(vector<Pixel>(columns*rows, Pixel::Red()))
{
}

vector<unsigned char> ImagePlane::GetPixelsInRGBAFormat() const
{
    auto rawDataStart = GetDataPointer();
    auto rawDataEnd = GetDataPointer() + (_columns*_rows*4);
    vector<unsigned char> rgba(rawDataStart, rawDataEnd);

    return rgba;
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

unsigned char* ImagePlane::GetDataPointer() const
{
    return (unsigned char*)_pixels.data();
}