#include <gtest/gtest.h>

#include "RayTracer/Scene.h"
#include <Eigen/Core>

#include <vector>
#include <fstream>
#include <string>
#include <experimental/filesystem>

using namespace std;
using namespace Eigen;

TEST(Full_Scene, Small_Moved_White_Sphere)
{
    ifstream ifs{"../../Tests/ground_truths/small_moved_white_sphere.ppm", ios::in | ios::binary};
    vector<char> expectedValues(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

    auto testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    auto resultDirectory = "Tests/" + string(testName);
    experimental::filesystem::v1::create_directories(resultDirectory);
    
    auto scene = Scene(resultDirectory);
    scene.AddSphere(Vector3f(2.f, 2.f, -10.f), 1.f);
    scene.Render();

    // TODO: Compare the two ppm's...

    EXPECT_EQ(10*2, 20);
}