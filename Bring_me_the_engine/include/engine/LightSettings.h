#pragma once
#include "math/Vec.h"
#include "math/Color.h"

struct LightSettings {
    Vec3 m_ambientColor = Vec3(1.0f, 1.0f, 1.0f);
    float m_ambientStrength = 0.2f;

    Vec3 m_diffuseColor = Vec3(1.0f, 1.0f, 1.0f);
    float m_diffuseIntensity = 0.5f;

    Vec3 m_specularColor = Vec3(1.0f, 1.0f, 1.0f);
    float m_specularStrength = 0.5f;
    float m_shininess = 32.0f;


    // Paramètres pour le fog
    Color m_fogColor = Color(8, 159, 255, 255); 
    float m_fogStart = 5.0f;
    float m_fogEnd = 20.0f;
    float m_fogDensity = 0.045f;
    int m_fogType = 0; // 0: aucun, 1: linéaire, 2: exp, 3: exp²
};