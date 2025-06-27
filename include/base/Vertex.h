#pragma once
#include "base/Vec.h"

struct Vertex {
    Vec3 position;
    Vec3 normal;
    Vec3 color;
    Vec2 texCoords;
    Vec3 tangent;    
    Vec3 bitangent; 
};
