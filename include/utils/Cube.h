#pragma once
#include <vector>
#include <memory>
#include "engine/Mesh.h"
#include "base/Color.h"
#include "utils/MeshUtils.h"

template<class> inline constexpr bool always_false = false;

template<typename T = Mesh>
inline T createCube(const Color & color = Color(204.f, 204.f, 204.f)) {
    std::vector<Vertex> vertices = {
        // Face avant (z = +0.5)
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 1.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 1.0f}, {0,0,0}, {0,0,0}},

        // Face arrière (z = -0.5)
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f,  0.5f, -0.5f}, {0, 0, -1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 1.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 1.0f}, {0,0,0}, {0,0,0}},

        // Face gauche (x = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 1.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 1.0f}, {0,0,0}, {0,0,0}},

        // Face droite (x = +0.5)
        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 1.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 1.0f}, {0,0,0}, {0,0,0}},

        // Face haut (y = +0.5)
        {{-0.5f,  0.5f,  0.5f}, {0, 1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 1.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 1.0f}, {0,0,0}, {0,0,0}},

        // Face bas (y = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f, -0.5f, -0.5f}, {0, -1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 0.0f}, {0,0,0}, {0,0,0}},
        {{ 0.5f, -0.5f,  0.5f}, {0, -1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {1.0f, 1.0f}, {0,0,0}, {0,0,0}},
        {{-0.5f, -0.5f,  0.5f}, {0, -1, 0}, {color.r/255.f, color.g/255.f, color.b/255.f}, {0.0f, 1.0f}, {0,0,0}, {0,0,0}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,       // Avant
        4, 5, 6, 6, 7, 4,       // Arrière
        8, 9,10,10,11, 8,       // Gauche
       12,13,14,14,15,12,       // Droite
       16,17,18,18,19,16,       // Haut
       20,21,22,22,23,20        // Bas
    };

    computeTangentsAndBitangents(vertices, indices);

    if constexpr (std::is_same_v<T, Mesh>) {
        return Mesh(vertices, indices);
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Mesh>>) {
        return std::make_shared<Mesh>(vertices, indices);
    } else {
        static_assert(always_false<T>, "Unsupported template parameter for createCube");
    }
}
