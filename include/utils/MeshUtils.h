#pragma once
#include <vector>
#include "base/Vertex.h"

inline void computeTangentsAndBitangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    for (size_t i = 0; i < indices.size(); i += 3) {
        Vertex& v0 = vertices[indices[i]];
        Vertex& v1 = vertices[indices[i + 1]];
        Vertex& v2 = vertices[indices[i + 2]];

        Vec3 pos1 = v0.position;
        Vec3 pos2 = v1.position;
        Vec3 pos3 = v2.position;

        Vec2 uv1 = v0.texCoords;
        Vec2 uv2 = v1.texCoords;
        Vec2 uv3 = v2.texCoords;

        Vec3 edge1 = pos2 - pos1;
        Vec3 edge2 = pos3 - pos1;
        Vec2 deltaUV1 = uv2 - uv1;
        Vec2 deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        Vec3 tangent, bitangent;

        tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

        bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

        // Ajout aux 3 sommets (moyenne si partagés)
        v0.tangent += tangent;
        v1.tangent += tangent;
        v2.tangent += tangent;

        v0.bitangent += bitangent;
        v1.bitangent += bitangent;
        v2.bitangent += bitangent;
    }

    // Normalisation finale (si sommets partagés)
    for (auto& vertex : vertices) {
        vertex.tangent = vertex.tangent.normalized();
        vertex.bitangent = vertex.bitangent.normalized();
    }
}