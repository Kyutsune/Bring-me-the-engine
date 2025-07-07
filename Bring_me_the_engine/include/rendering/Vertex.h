#pragma once
#include "math/Vec.h"

struct Vertex {
    Vec3 m_position;
    Vec3 m_normal;
    Vec3 m_color;
    Vec2 m_texCoords;
    Vec3 m_tangent;    
    Vec3 m_bitangent; 
};
