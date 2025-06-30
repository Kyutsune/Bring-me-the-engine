#pragma once
#include "base/Vec.h"
#include "base/Color.h"

struct LightSettings {
    Vec3 ambientColor = Vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.2f;

    Vec3 diffuseColor = Vec3(1.0f, 1.0f, 1.0f);
    float diffuseIntensity = 0.5f;

    Vec3 specularColor = Vec3(1.0f, 1.0f, 1.0f);
    float specularStrength = 0.5f;
    float shininess = 32.0f;


    // Paramètres pour le fog
    Color fogColor = Color(126.f, 126.f, 126.f, 1.f); // Gris clair
    float fogStart = 5.0f;   
    float fogEnd = 20.0f;
    float fogDensity = 0.045f;
    int fogType = 0; // 0: aucun, 1: linéaire, 2: exp, 3: exp²
};