#include "engine/Light.h"

Light::Light() : m_active(true), m_type(LIGHT_POINT), m_position(0, 0, 0),
                 m_direction(0, -1, 0), m_color(1, 1, 1), m_intensity(1),
                 m_constant(1), m_linear(0), m_quadratic(0) {}

Light::Light(bool active,
             int type,
             const Vec3 & position,
             const Vec3 & direction,
             const Color & color,
             float intensity,
             float constant,
             float linear,
             float quadratic)
    : m_active(active),
      m_type(static_cast<LightType>(type)),
      m_position(position),
      m_direction(direction),
      m_color(color),
      m_intensity(intensity),
      m_constant(constant),
      m_linear(linear),
      m_quadratic(quadratic) {}

float Light::computeEffectiveRange(float epsilon) const {
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

LightType Light::getType() const { return m_type; }
void Light::setType(LightType newType) { m_type = newType; }
const Vec3 & Light::getPosition() const { return m_position; }
const Vec3 & Light::getDirection() const { return m_direction; }
const Color & Light::getColor() const { return m_color; }
Color & Light::getColor() { return m_color; }
float Light::getIntensity() const { return m_intensity; }
void Light::setIntensity(float newIntensity) { m_intensity = newIntensity; }
float Light::getConstant() const { return m_constant; }
float Light::getLinear() const { return m_linear; }
float Light::getQuadratic() const { return m_quadratic; }
bool Light::isActive() const { return m_active; }
void Light::setActive(bool isActive) { m_active = isActive; }
void Light::setPosition(const Vec3 & newPosition) { m_position = newPosition; }
