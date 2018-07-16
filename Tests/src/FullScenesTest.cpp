#include <gtest/gtest.h>

#include "RayTracer/Camera.h"
#include "RayTracer/Sphere.h"
#include "RayTracer/Scene.h"
#include "ImageIO/ImageIO.h"

void images_are_equal(const ImagePlane& expected, const ImagePlane& actual);

TEST(Single_red_Sphere, Full_Scene)
{
    auto camera = Camera();

    auto s = new Sphere();
    auto scene = Scene(camera, {s});
    auto actualImagePlane = scene.Render();

    auto expectedImagePlane = ImageIO::Import("/home/shuber/dev/RayTracer/Tests/ground_truths/single_red_sphere.png");

    images_are_equal(expectedImagePlane, actualImagePlane);
}

void images_are_equal(const ImagePlane& expected, const ImagePlane& actual)
{
    EXPECT_EQ(expected.Columns(), actual.Columns());
    EXPECT_EQ(expected.Rows(), actual.Rows());

    for (auto row = 0; row < actual.Rows(); ++row)
    {
        for (auto column = 0; column < actual.Columns(); ++column)
        {
            auto expectedPx = expected.GetPixel(row, column);
            auto actualPx = actual.GetPixel(row, column);

            EXPECT_EQ(expectedPx, actualPx);
        }
    }
}