#pragma once

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "rendering/Vertex.h"
#include "rendering/GestionTextures/Texture.h"
#include "math/PlaneBoundingVolume.h"

// Classe qui sera utilisée pour représenter un objet dans l'espace 3D.
class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;
    AABB getBoundingBox() const;

    inline std::vector<Vertex> getVertices() const{ return m_vertices;}
    inline const std::vector<unsigned int> & getIndices() const { return m_indices; }

private:
    GLuint m_VAO, m_VBO, m_EBO;
    GLsizei m_indexCount;

    void setupMesh();
    
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};
