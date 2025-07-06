#pragma once
#include "math/Vec.h"
#include "rendering/Shader.h"
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct Plane {
    Vec3 m_normal;
    float m_distance; // d dans l’équation ax + by + cz + d = 0

    inline Plane() : m_normal(Vec3(0.0f, 1.0f, 0.0f)), m_distance(0.0f) {}
    inline Plane(const Vec3 & normal, float distance) : m_normal(normal), m_distance(distance) {}

    inline Plane(const Vec3 & point, const Vec3 & normal) {
        this->m_normal = normal.normalized();
        this->m_distance = -this->m_normal.dot(point);
    }

    inline Plane(const Vec3 & a, const Vec3 & b, const Vec3 & c) {
        m_normal = (b - a).cross(c - a).normalized();
        m_distance = -m_normal.dot(a);
    }

    // Calcule la distance signée d’un point au plan
    inline float distanceToPoint(const Vec3 & point) const {
        return m_normal.dot(point) + m_distance;
    }
};

struct AABB {
    Vec3 m_min;
    Vec3 m_max;
    unsigned int bboxVAO = 0, bboxVBO = 0, bboxEBO = 0;

    AABB() : m_min(Vec3(0.0f)), m_max(Vec3(0.0f)) {}
    AABB(const Vec3 & min, const Vec3 & max) : m_min(min), m_max(max) {}

    // Transforme la box par une matrice (transforme les 8 coins et recalcule min/max)
    AABB transform(const Mat4 & matrix) const;

    void setupBBoxBuffers();
    void drawAABB(const Mat4 & model, const Mat4 & view, const Mat4 & projection, Shader & shader);

    friend std::ostream & operator<<(std::ostream & os, const AABB & box) {
        os << "AABB(min: " << box.m_min << ", max: " << box.m_max << ")";
        return os;
    }

    // Calcule le point d'intersection de trois plans
    static Vec3 intersectPlanes(const Plane & p1, const Plane & p2, const Plane & p3);

    inline std::array<Vec3, 8> getCorners() const {
        return {
            Vec3(m_min.x, m_min.y, m_min.z),
            Vec3(m_max.x, m_min.y, m_min.z),
            Vec3(m_max.x, m_max.y, m_min.z),
            Vec3(m_min.x, m_max.y, m_min.z),
            Vec3(m_min.x, m_min.y, m_max.z),
            Vec3(m_max.x, m_min.y, m_max.z),
            Vec3(m_max.x, m_max.y, m_max.z),
            Vec3(m_min.x, m_max.y, m_max.z)
        };
    }
};
