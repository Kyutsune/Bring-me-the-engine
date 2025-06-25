#pragma once
#include "base/Vec.h"

struct LightSettings {
    Vec3 ambientColor = Vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.2f;

    Vec3 diffuseColor = Vec3(1.0f, 1.0f, 1.0f);
    float diffuseIntensity = 1.0f;

    Vec3 specularColor = Vec3(1.0f, 1.0f, 1.0f);
    float specularStrength = 0.5f;
    float shininess = 32.0f;
};