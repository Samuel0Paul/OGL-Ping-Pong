#pragma once
#include "Camera.h"


namespace mylib
{
    class OrthoCamera :
        public mylib::Camera
    {
    public:
        OrthoCamera() = default;
        OrthoCamera(const mylib::Camera& camera);
        virtual ~OrthoCamera();

        glm::mat4 getProjection() override;

    protected:
        float left, right, top, bottom;
    };

}
