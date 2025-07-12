#pragma once

#include "math/Vec.h"

class Quat {
public:
    float x, y, z, w;

    Quat();
    Quat(float x, float y, float z, float w);

    static Quat identity();

    // Création depuis un angle et un axe unitaire
    static Quat fromAxisAngle(const Vec3 & axis, float angleRad);

    static Quat fromEuler(const Vec3 & eulerRad);

    Mat4 toMat4() const;

    Vec3 toEuler() const;

    Quat operator*(const Quat & q) const;
    Quat normalized() const;

    float length() const;

    // Sert à rien, mais j'ai besoin de comprendre la dinguerie que sont les quaternions
    friend std::ostream & operator<<(std::ostream & os, const Quat & q) {
        os << "Quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
        return os;
    }
};
