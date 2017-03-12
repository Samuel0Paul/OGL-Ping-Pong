#include "stdafx.h"
#include "Mesh.h"

mylib::Mesh::Mesh(
    std::vector<Vertex> vertices, 
    std::vector<GLuint> indices, 
    std::vector<Texture> textures
) :
    vertices(vertices),
    indices(indices),
    textures(textures)
{
    this->setupMesh();
}

mylib::Mesh::~Mesh()
{
}

//! draw() renders the mesh onto app window
///
///	assumes sampler2D naming conventions as follows:
///		diffuse textures:	texture_diffuseN
///		speculat textures:	texture_specularN
///		where N: [0, MAX_TEXTURE_UNITS]
///
void mylib::Mesh::draw(mylib::Shader & shader)
{
    GLuint diffuseNr{ 1 }, specularNr{ 1 };
    for (GLuint i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);		// activate *_textureN
        std::string number;						// *_texture<"N">
        std::string name = textures[i].type;	// <"*_texture">N
        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
        }

        glUniform1f(
            glGetUniformLocation(
                shader.program,
                // material.<"*_textureN">
                ("material." + name + number).c_str()),
            static_cast<float>(i));
#ifdef _DEBUG
        //std::clog << "texture: " << ("material." + name + number).c_str()
        //<< std::endl;
#endif // _DEBUG

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,
        static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void mylib::Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(*(vertices.data())),
        vertices.data(),
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(*(indices.data())),
        indices.data(),
        GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3,
        GL_FLOAT, GL_FALSE, sizeof(Vertex), ML_BUFFER_OFFSET(0));
    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3,
        GL_FLOAT, GL_FALSE, sizeof(Vertex),
        ML_BUFFER_OFFSET(offsetof(Vertex, normal)));
    // Vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2,
        GL_FLOAT, GL_FALSE, sizeof(Vertex),
        ML_BUFFER_OFFSET(offsetof(Vertex, texCoords)));
    glBindVertexArray(0);
}
