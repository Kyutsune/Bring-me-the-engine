#pragma once
#include "base/Vec.h"
#include "base/Color.h"

struct Light {
    Vec3 position;      // Pour une lumière ponctuelle
    Vec3 direction;     // Pour une lumière directionnelle
    Color color;
    float intensity;
};