#pragma once
#include "math/Trigo.h"
#include "math/Vec.h"

class Camera {
private:
    Vec3 m_position;
    Vec3 m_target;
    Vec3 m_up;
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
    Mat4 m_viewMatrix;

public:
    inline Camera()
        : m_position(0.0f, 0.0f, 3.0f), m_target(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
          m_fov(45.0f), m_aspectRatio(16.0f / 9.0f), m_nearPlane(0.1f), m_farPlane(100.0f) {
    }

    inline Camera(const Vec3 & pos, const Vec3 & tgt, const Vec3 & upDir, float fovDegrees, float aspect, float nearP, float farP)
        : m_position(pos), m_target(tgt), m_up(upDir), m_fov(fovDegrees), m_aspectRatio(aspect), m_nearPlane(nearP), m_farPlane(farP) {}

    inline ~Camera() = default;

    Mat4 getViewMatrix() const;

    Mat4 getProjectionMatrix() const;

    inline const Vec3 & getPosition() const { return m_position; }
    inline void setPosition(const Vec3 & pos) { m_position = pos; }
    inline const Vec3 & getTarget() const { return m_target; }
    inline void setTarget(const Vec3 & tgt) { m_target = tgt; }

    inline Vec3 getDirection() const { return (m_target - m_position).normalized(); }
    inline Vec3 getRight() const { return getDirection().cross(m_up).normalized(); }
    inline Vec3 getLeft() const { return -getRight(); }
    inline Vec3 getForward() const { return getDirection(); }
    inline Vec3 getBackward() const { return -getDirection(); }
    inline Vec3 getUp() const { return m_up; }
    inline float getFov() const { return m_fov; }
    inline float getAspectRatio() const { return m_aspectRatio; }
    inline float getNearPlane() const { return m_nearPlane; }
    inline float getFarPlane() const { return m_farPlane; }
};
