#pragma once
#include "base/Vec.h"

struct Light {
    Vec3 position;      // Pour une lumière ponctuelle
    Vec3 direction;     // Pour une lumière directionnelle
    Vec3 color;
    float intensity;
};