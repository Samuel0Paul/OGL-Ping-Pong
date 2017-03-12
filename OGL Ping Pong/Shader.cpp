#include "stdafx.h"
#include "Shader.h"



namespace mylib
{
    Shader::Shader()
    {
    }

    Shader::Shader(std::initializer_list<std::pair<std::string, GLenum>> shader_objs)
    {
        std::ifstream fs;
        std::stringstream ss;
        std::string src;
        const GLchar* shader_src{nullptr};
        GLuint shader_id{0};
        std::vector<GLuint> shader_ids;

        GLint success{0};
        GLchar infoLog[512];

        fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            this->program = glCreateProgram();

#ifndef _NDEBUG
            std::clog << "LOG: shader program id: " << this->program << std::endl;
#endif
            for (const auto& shaderobj: shader_objs) {
                fs.open(shaderobj.first);
                ss << fs.rdbuf();
                fs.close();
                src = ss.str();
                shader_src = src.c_str();
#ifndef _NDEBUG
                std::clog << "GLchar** shader_src: " << shader_src << std::endl;
#endif
                shader_id = glCreateShader(shaderobj.second);
                shader_ids.push_back(shader_id);
                glShaderSource(shader_id, 1, &shader_src, NULL);
                glCompileShader(shader_id);
                glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
                    std::cerr << "ERROR: (" << __PRETTY_FUNCTION__ << ") "
                        << "shader compilation error, Log:\n" << infoLog << std::endl;
                    throw std::runtime_error("shader compilation error");
                }

                glAttachShader(this->program, shader_id);
                ss.str(std::string());
            }

            glLinkProgram(this->program);
            glGetProgramiv(this->program, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(this->program, 512, NULL, infoLog);
                std::cerr << "ERROR: (" << __PRETTY_FUNCTION__ << ") "
                    << "shader prog linker error, Log:\n" << infoLog << std::endl;
                throw std::runtime_error("shader prog linker error");
            }

            // delete shader objs in Gdev
            for (GLuint x: shader_ids) {
                glDeleteShader(x);
            }

        } catch (std::ifstream::failure e) {
            std::cerr << "ERROR: (" << __PRETTY_FUNCTION__ << ") file not read successfully"
                << ", e.what(): " << e.what() << std::endl;
            throw std::runtime_error("GLSL file not read successfully");
        }
    }


    Shader::~Shader()
    {
    }

}

void mylib::Shader::use()
{
    glUseProgram(this->program);
}
