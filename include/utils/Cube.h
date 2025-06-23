#pragma once
#include <vector>
#include <memory>
#include "engine/Mesh.h"

template<class> inline constexpr bool always_false = false;

template<typename T = Mesh>
inline T createCube() {
    std::vector<Vertex> vertices = {
        // positions           normales    couleurs    texCoords
        {{-0.5f, -0.5f, 0.5f}, {0, 0, 1}, {1, 0, 0}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f},  {0, 0, 1}, {0, 1, 0}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f},   {0, 0, 1}, {0, 0, 1}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f},  {0, 0, 1}, {1, 0, 1}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 0, 1}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0, 0, -1}, {0, 1, 1}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f},   {0, 0, -1}, {1, 1, 1}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f},  {0, 0, -1}, {0, 0, 1}, {1.0f, 1.0f}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,    // Face avant
        1, 5, 6, 6, 2, 1,    // Face droite
        5, 4, 7, 7, 6, 5,    // Face arrière
        4, 0, 3, 3, 7, 4,    // Face gauche
        3, 2, 6, 6, 7, 3,    // Face supérieure
        4, 5, 1, 1, 0, 4     // Face inférieure
    };

    if constexpr (std::is_same_v<T, Mesh>) {
        return Mesh(vertices, indices);
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Mesh>>) {
        return std::make_shared<Mesh>(vertices, indices);
    } else {
        static_assert(always_false<T>, "Unsupported template parameter for createCube");
    }
}
