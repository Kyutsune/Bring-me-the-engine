#pragma once
#include "math/Color.h"
#include "math/Vec.h"

enum LightType {
    LIGHT_ERROR = -1,
    LIGHT_POINT = 0,
    LIGHT_DIRECTIONAL = 1,
    //AVENIR: Autre type de lumière possible à implémenter à l'avenir: Spotlight, Area light, etc...
};

class Light {
public:
    Light();
    Light(bool active, int type, const Vec3 & position, const Vec3 & direction,
          const Color & color, float intensity, float constant, float linear, float quadratic);

    float computeEffectiveRange(float epsilon) const;

    LightType getType() const;
    void setType(LightType newType);
    const Vec3 & getPosition() const;
    void setPosition(const Vec3 & newPosition);
    const Vec3 & getDirection() const;
    const Color & getColor() const;
    float getIntensity() const;
    void setIntensity(float newIntensity);
    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;
    bool isActive() const;
    void setActive(bool isActive);

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