#pragma once

#include "stdafx.h"

#include "App.h"
#include "Shader.h"

namespace mylib
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct Texture
    {
        GLuint id;
        std::string type;
        aiString path;
    };

    class Mesh
    {
    public:
        //! mesh data
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        Mesh(
            std::vector<Vertex> vertices,
            std::vector<GLuint> indices,
            std::vector<Texture> textures);
        ~Mesh();

        void draw(mylib::Shader& shader);


    private:
        //! render data
        GLuint VAO{ 0 }, VBO{ 0 }, EBO{ 0 };

        void setupMesh();
    };
}

