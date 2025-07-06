#include "camera/Camera.h"

Mat4 Camera::getViewMatrix() const {
    return Mat4::lookAt(m_position, m_target, m_up);
}
Mat4 Camera::getProjectionMatrix() const {
    return Mat4::perspective(radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}
