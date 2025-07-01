#pragma once
#include <vector>
#include "math/Vec.h"
#include "rendering/Vertex.h"

inline void computeTangentsAndBitangents(std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices) {
    // 1. Initialiser
    for (auto & v : vertices) {
        v.tangent = Vec3(0.0f, 0.0f, 0.0f);
        v.bitangent = Vec3(0.0f, 0.0f, 0.0f);
    }

    // 2. Calculer par triangle
    for (size_t i = 0; i < indices.size(); i += 3) {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];

        const Vec3 & pos0 = vertices[i0].position;
        const Vec3 & pos1 = vertices[i1].position;
        const Vec3 & pos2 = vertices[i2].position;

        const Vec2 & uv0 = vertices[i0].texCoords;
        const Vec2 & uv1 = vertices[i1].texCoords;
        const Vec2 & uv2 = vertices[i2].texCoords;

        Vec3 edge1 = pos1 - pos0;
        Vec3 edge2 = pos2 - pos0;

        Vec2 deltaUV1 = uv1 - uv0;
        Vec2 deltaUV2 = uv2 - uv0;

        float denom = (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
        float f = (denom == 0.0f) ? 0.0f : 1.0f / denom;

        Vec3 tangent{
            f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
            f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
            f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)
        };

        Vec3 bitangent{
            f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x),
            f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y),
            f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z)
        };

        vertices[i0].tangent += tangent;
        vertices[i1].tangent += tangent;
        vertices[i2].tangent += tangent;

        vertices[i0].bitangent += bitangent;
        vertices[i1].bitangent += bitangent;
        vertices[i2].bitangent += bitangent;
    }

    // Une étape de normalisation
    for (auto & v : vertices) {
        v.tangent = v.tangent.normalized();
        v.bitangent = v.bitangent.normalized();
    }
}