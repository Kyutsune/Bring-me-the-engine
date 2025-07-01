#include "engine/Camera.h"

Mat4 Camera::getViewMatrix() const {
    return Mat4::lookAt(position, target, up);
}
Mat4 Camera::getProjectionMatrix() const {
    return Mat4::perspective(radians(fov), aspectRatio, nearPlane, farPlane);
}
