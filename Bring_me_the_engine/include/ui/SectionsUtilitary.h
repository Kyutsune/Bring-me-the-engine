#pragma once

#include <string>
#include <functional>
#include "math/Vec.h"
#include "math/Color.h"
#include "engine/Scene.h"
#include "engine/LightingManager.h"


namespace SectionsUtilitary {
    void renderPositionEditor(const std::string & labelPrefix, Vec3 & position, const std::function<void(const Vec3 &)> & onPositionChanged);
}