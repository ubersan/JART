#include "ImageIO/ImageIO.h"
#include "ImageIO/lodepng.h"

#include <iostream>
using namespace std;

void ImageIO::Export(const ImagePlane& imagePlane)
{
    auto pixelsInRGBAFormat = imagePlane.GetPixelsInRGBAFormat();

    Export(pixelsInRGBAFormat, imagePlane.Columns(), imagePlane.Rows());
}

void ImageIO::Export(const std::vector<unsigned char>& imageData, int columns, int rows)
{
    if (imageData.size() != columns*rows*4)
    {
        // Each pixel is represented by 4 bytes, 1 byte for each R, G, B and A.
        throw runtime_error("Wrong image dimensions given the number of pixels");
    }

    auto error = lodepng::encode("test.png", imageData, columns, rows);
    
    if (error != 0)
    {
        cerr << "Image export failed with error number " << error << endl;
    }
}

ImagePlane ImageIO::Import(const std::string& filename)
{
    vector<unsigned char> imageData;
    unsigned int columns, rows;

    auto error = lodepng::decode(imageData, columns, rows, filename);
    
    if (error != 0)
    {
        cerr << "Image import failed with error number " << error << endl;
    }

    return ImagePlane(columns, rows, imageData);
}