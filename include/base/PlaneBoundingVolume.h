#pragma once
#include "base/Vec.h"
#include "base/Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct Plane {
    Vec3 normal;
    float distance; // d dans l’équation ax + by + cz + d = 0

    // Calcule la distance signée d’un point au plan
    float distanceToPoint(const Vec3 & point) const {
        return normal.dot(point) + distance;
    }
};

struct AABB {
    Vec3 min;
    Vec3 max;
    unsigned int bboxVAO = 0, bboxVBO = 0, bboxEBO = 0;

    AABB() : min(Vec3(0.0f)), max(Vec3(0.0f)) {}
    AABB(const Vec3 & min, const Vec3 & max) : min(min), max(max) {}

    // Transforme la box par une matrice (transforme les 8 coins et recalcule min/max)
    AABB transform(const Mat4 & matrix) const;

    void setupBBoxBuffers();
    void drawAABB(const Mat4 & model, const Mat4 & view, const Mat4 & projection, Shader & shader);

    friend std::ostream & operator<<(std::ostream & os, const AABB & box) {
        os << "AABB(min: " << box.min << ", max: " << box.max << ")";
        return os;
    }
};
