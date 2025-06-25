#pragma once
#include <vector>
#include <memory>
#include "engine/Mesh.h"


template<typename T = Mesh>
inline T createFloor(float size = 10.0f, float height = 0.0f, float red = 0.f, float green = 0.f, float blue = 0.f) {
    float half = size / 2.0f;

    std::vector<Vertex> vertices = {
        //position                normale      couleur                               texCoords
        {{-half, height, -half},  {0, 1, 0},   {red/255.f, green/255.f, blue/255.f}, {0.0f, 0.0f}},
        {{ half, height, -half},  {0, 1, 0},   {red/255.f, green/255.f, blue/255.f}, {1.0f, 0.0f}},
        {{ half, height,  half},  {0, 1, 0},   {red/255.f, green/255.f, blue/255.f}, {1.0f, 1.0f}},
        {{-half, height,  half},  {0, 1, 0},   {red/255.f, green/255.f, blue/255.f}, {0.0f, 1.0f}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    if constexpr (std::is_same_v<T, Mesh>) {
        return Mesh(vertices, indices);
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Mesh>>) {
        return std::make_shared<Mesh>(vertices, indices);
    } else {
        static_assert(always_false<T>, "Unsupported template parameter for createGround");
    }
}