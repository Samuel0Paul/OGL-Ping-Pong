#include "stdafx.h"
#include "OrthoCamera.h"



mylib::OrthoCamera::OrthoCamera(const mylib::Camera & camera) :
    mylib::Camera(camera)
{
    isOrtho = true;

    left = -static_cast<float>(windowWidth) / 2;
    bottom = -static_cast<float>(windowHeight) / 2;
    top = static_cast<float>(windowHeight) / 2;
    right = static_cast<float>(windowWidth) / 2;
}


mylib::OrthoCamera::~OrthoCamera()
{
}

glm::mat4 mylib::OrthoCamera::getProjection()
{
    return glm::ortho(left, right, bottom, top, 0.1f, 100.0f);
}
