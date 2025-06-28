#pragma once
#include "base/Color.h"
#include "base/Vec.h"

enum LightType {
    LIGHT_POINT = 0,
    LIGHT_DIRECTIONAL = 1,
    // Autre type de lumière possible : Spotlight, Area light, etc.
};

struct Light {
    LightType type; // 0 = point, 1 = directionnelle
    Vec3 position;  // Pour une lumière ponctuelle (position dans l'espace)
    Vec3 direction; // Pour une lumière directionnelle
    Color color;
    float intensity;

    // Optionnel : paramètres d'atténuation pour lumière ponctuelle
    float constant;
    float linear;
    float quadratic;

    Light() : type(LIGHT_POINT), position(0, 0, 0), direction(0, -1, 0), color(1, 1, 1), intensity(1),
              constant(1), linear(0), quadratic(0) {}

    Light(int type,
          const Vec3 & position,
          const Vec3 & direction,
          const Color & color,
          float intensity,
          float constant,
          float linear,
          float quadratic)
        : type(static_cast<LightType>(type)),
          position(position),
          direction(direction),
          color(color),
          intensity(intensity),
          constant(constant),
          linear(linear),
          quadratic(quadratic) {}
};