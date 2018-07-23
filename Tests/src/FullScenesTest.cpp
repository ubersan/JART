#include <gtest/gtest.h>

#include "RayTracer/Scene.h"
#include <Eigen/Core>

#include <vector>
#include <fstream>
#include <string>
#include <experimental/filesystem>
#include <algorithm>
#include <memory>

using namespace std;
using namespace Eigen;

// There is not default ctor for scene, thus we need a pointer
unique_ptr<Scene> scene;

string testName;
vector<char> expectedValues;
vector<char> actualValues;

void Given_Scene_Small_Moved_White_Sphere();
void Given_Centered_Red_Sphere_With_Directional_Light();
void Given_Centered_Sphere_With_Shadow_On_Plane();
void Given_Two_Spheres_Self_Shadowing();
void Given_PointLight_On_Sphere_And_Plane();
void Given_PointLight_Two_Spheres_Self_Shadowing();
void Given_PointLight_InBetween_Two_Spheres();
void Given_Two_DirectionalLights_On_Single_Sphere();
void Given_Three_PointLights_Onto_Plane_In_Row();
void Given_Three_PointLights_OnPlane_InTriangle_MixingTogether();
void Given_Single_Sphere_And_Plane_With_Background_SkyBlue();
void Given_Mirror_Plane_Single_Sphere();
void Given_Mirror_Bounded_Plane_With_Three_Spheres();
void Given_Mirror_Planes_Against_Each_Other_No_Infinite_Recursion();
void Given_Mirror_Sphere_On_Plane_With_Diffuse_Shadowing_Sphere();
void Given_Two_Triangles_Different_Angles_To_Light_And_Camera();

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

TEST(Full_Scene, Centered_Red_Sphere_With_Directional_Light)
{
    Given_Centered_Red_Sphere_With_Directional_Light();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Centered_Sphere_With_Shadow_On_Plane)
{
    Given_Centered_Sphere_With_Shadow_On_Plane();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Two_Spheres_Self_Shadowing)
{
    Given_Two_Spheres_Self_Shadowing();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, PointLight_On_Sphere_And_Plane)
{
    Given_PointLight_On_Sphere_And_Plane();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, PointLight_Two_Spheres_Self_Shadowing)
{
    Given_PointLight_Two_Spheres_Self_Shadowing();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, PointLight_InBetween_Two_Spheres)
{
    Given_PointLight_InBetween_Two_Spheres();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Two_DirectionalLights_On_Single_Sphere)
{
    Given_Two_DirectionalLights_On_Single_Sphere();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Three_PointLights_Onto_Plane_In_Row)
{
    Given_Three_PointLights_Onto_Plane_In_Row();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Three_PointLights_OnPlane_InTriangle_MixingTogether)
{
    Given_Three_PointLights_OnPlane_InTriangle_MixingTogether();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Single_Sphere_And_Plane_With_Background_SkyBlue)
{
    Given_Single_Sphere_And_Plane_With_Background_SkyBlue();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Mirror_Plane_Single_Sphere)
{
    Given_Mirror_Plane_Single_Sphere();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Mirror_Bounded_Plane_With_Three_Spheres)
{
    Given_Mirror_Bounded_Plane_With_Three_Spheres();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Mirror_Planes_Against_Each_Other_No_Infinite_Recursion)
{
    Given_Mirror_Planes_Against_Each_Other_No_Infinite_Recursion();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Mirror_Sphere_On_Plane_With_Diffuse_Shadowing_Sphere)
{
    Given_Mirror_Sphere_On_Plane_With_Diffuse_Shadowing_Sphere();
    When_Render();
    Then_ImagesMatch();
}

TEST(Full_Scene, Two_Triangles_Different_Angles_To_Light_And_Camera)
{
    Given_Two_Triangles_Different_Angles_To_Light_And_Camera();
    When_Render();
    Then_ImagesMatch();
}

void Given_Two_Triangles_Different_Angles_To_Light_And_Camera()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddTriangle(Vector3f{2.5f, 0.f, -10.f}, Vector3f{-0.5f, 1.f, -10.f}, Vector3f{-1.5f, 0.5f, -10.f}, Material::DIFFUSE);
    scene->AddTriangle(Vector3f{1.5f, -1.f, -10.f}, Vector3f{-1.5f, 0.25f, -10.f}, Vector3f{-0.5f, -0.5f, -7.f}, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{0.f, 0.f, -1.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
}

void Given_Mirror_Sphere_On_Plane_With_Diffuse_Shadowing_Sphere()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddSphere(Vector3f{0.f, -0.3f, -10.f}, 1.f, Material::MIRROR);
    scene->AddSphere(Vector3f{-1.f, 1.f, -9.f}, 0.5f, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
    scene->SetBackground(Vector3f{0.36, 0.52f, 0.8f});
}

void Given_Mirror_Planes_Against_Each_Other_No_Infinite_Recursion()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddPlane(Vector3f{0.f, 0.f, -10.f}, Vector3f{0.f, 0.f, 1.f}, Vector3f{1.f, 0.f, 0.f}, 2.f, 2.f, Material::MIRROR);
    scene->AddPlane(Vector3f{0.f, 0.f, 10.f}, Vector3f{0.f, 0.f, -1.f}, Vector3f{-1.f, 0.f, 0.f}, 2.f, 2.f, Material::MIRROR);
    scene->AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
    scene->SetBackground(Vector3f{0.36, 0.52f, 0.8f});   
}

void Given_Mirror_Bounded_Plane_With_Three_Spheres()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddPlane(Vector3f{0.f, -1.5f, -10.f}, Vector3f{0.f, 1.f, 0.f}, Vector3f{1.f, 0.f, 0.f}, 6.f, 15.5f, Material::MIRROR);
    scene->AddSphere(Vector3f{1.5f, -0.3f, -10.f}, 0.5f, Material::DIFFUSE);
    scene->AddSphere(Vector3f{0.f, -0.5f, -7.f}, 1.f, Material::DIFFUSE);
    scene->AddSphere(Vector3f{-3.f, -0.3f, -13.f}, 1.f, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
    scene->SetBackground(Vector3f{0.36, 0.52f, 0.8f});
    scene->SetCamera(Vector3f{1.f, 0.f, 0.f}, Vector3f{0.f, -0.45f, -1.f}.normalized(), Vector3f{0.f, 6.5f, 10.f});
}

void Given_Mirror_Plane_Single_Sphere()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::MIRROR);
    scene->AddSphere(Vector3f{0.f, -0.3f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
    scene->SetBackground(Vector3f{0.36, 0.52f, 0.8f});
    scene->SetCamera(Vector3f{1.f, 0.f, 0.f}, Vector3f{0.f, -0.45f, -1.f}.normalized(), Vector3f{0.f, 8.f, 10.f});
}

void Given_Single_Sphere_And_Plane_With_Background_SkyBlue()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 1.f, 1.f});
    scene->SetBackground(Vector3f{0.36, 0.52f, 0.8f});
}

void Given_Three_PointLights_OnPlane_InTriangle_MixingTogether()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);

    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddPointLight(Vector3f{0.f, -1.f, -10.f - sqrtf(5.f)/16.f}, 3.25f, Vector3f{1.f, 0.f, 0.f});
    scene->AddPointLight(Vector3f{-0.125f, -1.f, -10.f + sqrtf(5.f)/16.f}, 3.25f, Vector3f{0.f, 1.f, 0.f});
    scene->AddPointLight(Vector3f{0.125f, -1.f, -10.f + sqrtf(5.f)/16.f}, 3.25f, Vector3f{0.f, 0.f, 1.f});
    scene->SetCamera(Vector3f{1.f, 0.f, 0.f}, Vector3f{0.f, -1.f, 0.f}.normalized(), Vector3f{0.f, 2.5f, -10.f});
}

void Given_Three_PointLights_Onto_Plane_In_Row()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddPointLight(Vector3f{-1.f, -1.f, -10.f}, 5.f, Vector3f{1.f, 0.f, 0.f});
    scene->AddPointLight(Vector3f{0.f, -1.f, -10.f}, 5.f, Vector3f{0.f, 1.f, 0.f});
    scene->AddPointLight(Vector3f{1.f, -1.f, -10.f}, 5.f, Vector3f{0.f, 0.f, 1.f});
}

void Given_Two_DirectionalLights_On_Single_Sphere()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{1.f, -1.f, 0.f}.normalized(), 1.f, Vector3f{1.f, 0.f, 0.f});
    scene->AddDirectionalLight(Vector3f{-1.f, -1.f, 0.f}.normalized(), 1.f, Vector3f{0.f, 0.f, 1.f});
}

void Given_PointLight_Two_Spheres_Self_Shadowing()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddSphere(Vector3f{-1.f, 1.f, -9.25f}, 0.25f, Material::DIFFUSE);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddPointLight(Vector3f{-3.f, 5.f, -10.f}, 250.f, Vector3f{1.f, 1.f, 1.f});
}

void Given_PointLight_On_Sphere_And_Plane()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddPointLight(Vector3f{0.f, 5.f, -10.f}, 250.f, Vector3f{1.f, 1.f, 1.f});
}

void Given_Two_Spheres_Self_Shadowing()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddSphere(Vector3f{1.f, 1.f, -9.25f}, 0.25f, Material::DIFFUSE);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{-0.5f, -1.f, 0.f}.normalized(), 1.f, Vector3f{1.f, 1.f, 1.f});
}

void Given_Scene_Small_Moved_White_Sphere()
{
    auto resultDirectory = Setup_TestEnvironment();
    
    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->SetCamera(Vector3f{1.f, 0.f, 0.f}, Vector3f{0.f, 0.f, -1.f}, Vector3f{0.f, 0.f, 10.f});
    scene->AddSphere(Vector3f(2.f, 2.f, -10.f), 1.f, Material::DIFFUSE);
}

void Given_Centered_Red_Sphere_With_Directional_Light()
{
    auto resultDirectory = Setup_TestEnvironment();

    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{0.f, -1.f, 0.f}, 1.f, Vector3f{1.f, 0.f, 0.f});
}

void Given_Centered_Sphere_With_Shadow_On_Plane()
{
    auto resultDirectory = Setup_TestEnvironment();

    scene = make_unique<Scene>(640, 480, 30, resultDirectory);

    scene->AddSphere(Vector3f{0.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddDirectionalLight(Vector3f{-0.5f, -1.f, 0.f}.normalized(), 1.f, Vector3f{1.f, 1.f, 1.f});
}

void Given_PointLight_InBetween_Two_Spheres()
{
    auto resultDirectory = Setup_TestEnvironment();

    scene = make_unique<Scene>(640, 480, 30, resultDirectory);
    scene->AddSphere(Vector3f{-2.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddSphere(Vector3f{2.f, 0.f, -10.f}, 1.f, Material::DIFFUSE);
    scene->AddPlane(Vector3f{0.f, -1.5f, 0.f}, Vector3f{0.f, 1.f, 0.f}, Material::DIFFUSE);
    scene->AddPointLight(Vector3f{0.f, 0.f, -10.f}, 10.f, Vector3f{1.f, 1.f, 1.f});
}

void When_Render()
{
    scene->Render();
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
    EXPECT_TRUE(experimental::filesystem::v1::exists(filename));

    ifstream inputExpected{filename, ios::in | ios::binary};
    return vector<char>((istreambuf_iterator<char>(inputExpected)), istreambuf_iterator<char>());
}