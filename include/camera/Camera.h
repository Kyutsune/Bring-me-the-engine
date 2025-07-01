#pragma once
#include "math/Vec.h"
#include "math/Trigo.h"

class Camera {
private:
    Vec3 position;
    Vec3 target;
    Vec3 up;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    Mat4 * viewMatrix;

public:
    inline Camera()
        : position(0.0f, 0.0f, 3.0f), target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f),
          fov(45.0f), aspectRatio(16.0f / 9.0f), nearPlane(0.1f), farPlane(100.0f) {
        viewMatrix = new Mat4();
    }

    inline Camera(const Vec3 & pos, const Vec3 & tgt, const Vec3 & upDir, float fovDegrees, float aspect, float nearP, float farP)
        : position(pos), target(tgt), up(upDir), fov(fovDegrees), aspectRatio(aspect), nearPlane(nearP), farPlane(farP) {
        viewMatrix = new Mat4();
    }

    Mat4 getViewMatrix() const;

    Mat4 getProjectionMatrix() const;

    inline const Vec3 & getPosition() const { return position; }
    inline void setPosition(const Vec3 & pos) { position = pos; }
    inline const Vec3 & getTarget() const { return target; }
    inline void setTarget(const Vec3 & tgt) { target = tgt; }

    inline Vec3 getDirection() const { return (target - position).normalized(); }
    inline Vec3 getRight() const { return getDirection().cross(up).normalized(); }
    inline Vec3 getLeft() const { return -getRight(); }
    inline Vec3 getForward() const { return getDirection(); }
    inline Vec3 getBackward() const { return -getDirection(); }
    inline Vec3 getUp() const { return up; }
    inline float getFov() const { return fov; }
    inline float getAspectRatio() const { return aspectRatio; }
    inline float getNearPlane() const { return nearPlane; }
    inline float getFarPlane() const { return farPlane; }
};
