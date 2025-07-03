#pragma once

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "rendering/Vertex.h"
#include "rendering/Texture.h"
#include "math/PlaneBoundingVolume.h"

// Classe qui sera utilisée pour représenter un objet dans l'espace 3D.
class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;
    AABB getBoundingBox() const;

    inline std::vector<Vertex> getVertices() const{ return vertices;}

private:
    GLuint VAO, VBO, EBO;
    GLsizei indexCount;

    void setupMesh();
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
