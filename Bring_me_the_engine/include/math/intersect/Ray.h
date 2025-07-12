#pragma once
#include "math/Vec.h"

struct Ray {
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d.normalized()) {}
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
        os << "Ray(origin: " << ray.origin << ", direction: " << ray.direction << ")";
        return os;
    }
    static Ray generateRayFromScreen(double mouseX, double mouseY);

};