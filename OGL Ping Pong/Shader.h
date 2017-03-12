#pragma once

#include "stdafx.h"

namespace mylib
{
    class Shader
    {
    public:
        GLuint program;

        Shader();
        Shader(std::initializer_list<std::pair<std::string, GLenum>> shader_objs);
        ~Shader();
        
        void use();
    };
}

