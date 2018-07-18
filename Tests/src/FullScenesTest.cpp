#include <gtest/gtest.h>

#include "RayTracer/Scene.h"
#include <Eigen/Core>

#include <vector>
#include <fstream>
#include <string>
#include <experimental/filesystem>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace Eigen;

Scene scene;
string testName;
vector<char> expectedValues;
vector<char> actualValues;

void Given_Scene_Small_Moved_White_Sphere();

void When_Render();
void Then_ImagesMatch();

string Setup_TestEnvironment();
vector<char> ParseFile(const string& filename);

TEST(Full_Scene, Small_Moved_White_Sphere)
{
    Given_Scene_Small_Moved_White_Sphere();
    When_Render();
    Then_ImagesMatch();
}

void Given_Scene_Small_Moved_White_Sphere()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = Scene(resultDirectory);
    scene.AddSphere(Vector3f(2.f, 2.f, -10.f), 1.f);
}

void When_Render()
{
    scene.Render();
}

void Then_ImagesMatch()
{
    expectedValues = ParseFile("../Tests/ground_truths/" + testName + ".ppm");
    actualValues = ParseFile("./Tests/" + testName + "/out.ppm");

    EXPECT_EQ(
        mismatch(expectedValues.begin(), expectedValues.end(), actualValues.begin()).first,
        // mismatch returns the end of the iterator when all values match
        expectedValues.end());
}

string Setup_TestEnvironment()
{
    testName = string(::testing::UnitTest::GetInstance()->current_test_info()->name());
    auto resultDirectory = "Tests/" + testName;
    experimental::filesystem::v1::create_directories(resultDirectory);

    return resultDirectory;
}

vector<char> ParseFile(const string& filename)
{
    ifstream inputExpected{filename, ios::in | ios::binary};
    return vector<char>((istreambuf_iterator<char>(inputExpected)), istreambuf_iterator<char>());
}