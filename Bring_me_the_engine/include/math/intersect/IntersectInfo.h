#pragma once

#include <limits>
#include <memory>
#include "math/Vec.h"
#include "engine/Entity.h"

struct IntersectionInfo {
    bool hit = false;
    float t = std::numeric_limits<float>::max();
    Vec3 position;
    Vec3 normal;
    std::shared_ptr<Entity> entity = nullptr;
};