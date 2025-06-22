#include "base/Vec.h"
#include "tools/Trigo.h"


class Camera {
private:
    Vec3 position;
    Vec3 target;
    Vec3 up;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

public:
    Camera(const Vec3& pos, const Vec3& tgt, const Vec3& upDir, float fovDegrees, float aspect, float nearP, float farP)
    : position(pos), target(tgt), up(upDir), fov(fovDegrees), aspectRatio(aspect), nearPlane(nearP), farPlane(farP) {}

    Mat4 getViewMatrix() const {
        return Mat4::lookAt(position, target, up);
    }

    Mat4 getProjectionMatrix() const {
        return Mat4::perspective(radians(fov), aspectRatio, nearPlane, farPlane);
    }

    void setPosition(const Vec3& pos) { position = pos; }
    void setTarget(const Vec3& tgt) { target = tgt; }
};
