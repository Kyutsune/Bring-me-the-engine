#pragma once
#include "math/Color.h"
#include "engine/Mesh.h"
#include "math/Tang_Bitang.h"
#include <memory>
#include <vector>

template <typename T = Mesh>
inline T createFloor(float size = 10.0f, float height = 0.0f, const Color & color = Color(16.f, 144.f, 48.f)) {
    float half = size / 2.0f;

    float texelDensity = 0.5f; 
    float repeat = size * texelDensity;

    std::vector<Vertex> vertices = {
        {{-half, height, -half}, {0, 1, 0}, {color.r / 255.f, color.g / 255.f, color.b / 255.f}, {0.0f, 0.0f}},
        {{half, height, -half}, {0, 1, 0}, {color.r / 255.f, color.g / 255.f, color.b / 255.f}, {repeat, 0.0f}},
        {{half, height, half}, {0, 1, 0}, {color.r / 255.f, color.g / 255.f, color.b / 255.f}, {repeat, repeat}},
        {{-half, height, half}, {0, 1, 0}, {color.r / 255.f, color.g / 255.f, color.b / 255.f}, {0.0f, repeat}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0};

    computeTangentsAndBitangents(vertices, indices);

    if constexpr (std::is_same_v<T, Mesh>) {
        return Mesh(vertices, indices);
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Mesh>>) {
        return std::make_shared<Mesh>(vertices, indices);
    } else {
        static_assert(always_false<T>, "Unsupported template parameter for createGround");
    }
}