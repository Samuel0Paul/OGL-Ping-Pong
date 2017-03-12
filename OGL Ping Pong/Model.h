#pragma once

#include "stdafx.h"

#include "Mesh.h"
#include "Shader.h"

namespace mylib
{
    static GLint TextureFromFile(const char* path, std::string directory);

    class Model
    {
    public:
        Model();
        Model(const GLchar* path);
        ~Model();

        void draw(Shader shader);

    private:
        //! model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(
            aiMaterial* mat,
            aiTextureType type, 
            std::string typeName);

    };

}
