#pragma once
#include "math/Color.h"
#include "math/Vec.h"

enum LightType {
    LIGHT_ERROR = -1,
    LIGHT_POINT = 0,
    LIGHT_DIRECTIONAL = 1,
    // Autre type de lumière possible : Spotlight, Area light, etc...
};

class Light {
public:
    Light() : m_active(true), m_type(LIGHT_POINT), m_position(0, 0, 0), m_direction(0, -1, 0), m_color(1, 1, 1), m_intensity(1),
              m_constant(1), m_linear(0), m_quadratic(0) {}

    Light(bool active,
          int type,
          const Vec3 & position,
          const Vec3 & direction,
          const Color & color,
          float intensity,
          float constant,
          float linear,
          float quadratic)
        : m_type(static_cast<LightType>(type)),
          m_position(position),
          m_direction(direction),
          m_color(color),
          m_intensity(intensity),
          m_constant(constant),
          m_linear(linear),
          m_quadratic(quadratic),
          m_active(active) {}

    //TODO: Corriger pour remplacer ça dans le cpp
    inline float computeEffectiveRange(float epsilon) const {
        float threshold = m_intensity / epsilon;

        float A = m_quadratic;
        float B = m_linear;
        float C = m_constant - threshold;

        if (A == 0.0f) {
            if (B == 0.0f)
                return (C < 0.0f) ? 100.0f : 0.0f;
            return -C / B;
        }

        float discriminant = B * B - 4 * A * C;
        if (discriminant < 0.0f)
            return 0.0f;

        return (-B + std::sqrt(discriminant)) / (2 * A);
    }

    inline LightType getType() const { return m_type; }
    inline void setType(LightType newType) { m_type = newType; }
    inline const Vec3 & getPosition() const { return m_position; }
    inline const Vec3 & getDirection() const { return m_direction; }
    inline const Color & getColor() const { return m_color; }
    inline float getIntensity() const { return m_intensity; }
    inline void setIntensity(float newIntensity) { m_intensity = newIntensity; }
    inline float getConstant() const { return m_constant; }
    inline float getLinear() const { return m_linear; }
    inline float getQuadratic() const { return m_quadratic; }
    inline bool isActive() const { return m_active; }
    inline void setActive(bool isActive) { m_active = isActive; }

private:
    bool m_active;
    LightType m_type; // 0 = point, 1 = directionnelle
    Vec3 m_position;  // Pour une lumière ponctuelle (position dans l'espace)
    Vec3 m_direction; // Pour une lumière directionnelle
    Color m_color;
    float m_intensity;

    // Optionnel : paramètres d'atténuation pour lumière ponctuelle
    float m_constant;
    float m_linear;
    float m_quadratic;
};