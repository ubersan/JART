#include "PNGExporter.h"

#include "lodepng.h"

#include <iostream>
using namespace std;

void PNGExporter::Export(const std::vector<unsigned char>& imageData, int width, int height)
{
    if (imageData.size() != width*height*4)
    {
        // Each pixel is represented by 4 bytes, 1 byte for each R, G, B and A.
        throw runtime_error("Wrong image dimensions given the number of pixels");
    }

    auto error = lodepng::encode("test.png", imageData, width, height);
    
    if (error != 0)
    {
        cerr << "Image export failed with error number " << error << endl;
    }
}