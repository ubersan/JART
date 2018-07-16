#include "PNGExporter.h"

#include "lodepng.h"

#include <iostream>
using namespace std;

void PNGExporter::Export(const ImagePlane& imagePlane)
{
    auto pixelsInRGBAFormat = imagePlane.GetPixelsInRGBAFormat();

    Export(pixelsInRGBAFormat, imagePlane.Columns(), imagePlane.Rows());
}

void PNGExporter::Export(const std::vector<unsigned char>& imageData, int columns, int rows)
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