#pragma once

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "base/Vertex.h"
#include "base/Texture.h"
#include "base/PlaneBoundingVolume.h"

// Classe qui sera utilisée pour représenter un objet dans l'espace 3D.
class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;
    AABB getBoundingBox() const;

private:
    GLuint VAO, VBO, EBO;
    GLsizei indexCount;

    void setupMesh();
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
