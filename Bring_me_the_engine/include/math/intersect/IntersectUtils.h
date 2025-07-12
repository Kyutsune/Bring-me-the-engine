#pragma once

#include "math/intersect/Ray.h"
#include "math/intersect/IntersectInfo.h"
#include "engine/Entity.h"


namespace IntersectUtils {
    bool intersect(const Vec3 & o, const Vec3 & d, const float tmax, const Vec3 & a, const Vec3 & b, const Vec3 & c,
               Vec3 & intersection, Vec3 & normale_intersection, float & t);

    bool intersectEntity(const Ray& ray, const Entity& entity, IntersectionInfo& outInfo, float tmax = 1000.0f);

}