#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Vertex.h"

// Class that'll be used to represent a set of objects in the 3d space.
class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;

private:
    GLuint VAO, VBO, EBO;
    GLsizei indexCount;

    void setupMesh();
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
