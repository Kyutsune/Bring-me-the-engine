#pragma once
#include "rendering/Shader.h"
#include "math/Vec.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct Plane {
    Vec3 normal;
    float distance; // d dans l’équation ax + by + cz + d = 0

    inline Plane() : normal(Vec3(0.0f, 1.0f, 0.0f)), distance(0.0f) {}
    inline Plane(const Vec3 & normal, float distance) : normal(normal), distance(distance) {}

    inline Plane(const Vec3 & point, const Vec3 & normal) {
        this->normal = normal.normalized();
        this->distance = -this->normal.dot(point);
    }

    inline Plane(const Vec3 & a, const Vec3 & b, const Vec3 & c) {
        normal = (b - a).cross(c - a).normalized();
        distance = -normal.dot(a);
    }

    // Calcule la distance signée d’un point au plan
    inline float distanceToPoint(const Vec3 & point) const {
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
