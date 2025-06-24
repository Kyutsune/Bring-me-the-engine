#include "engine/Camera.h"

Vec3 Camera::getDirection() const {
    return (target - position).normalized();
}

Vec3 Camera::getRight() const {
    // direction croisé avec up donne la droite
    return getDirection().cross(up).normalized();
}

Vec3 Camera::getLeft() const {
    return -getRight();
}

Vec3 Camera::getForward() const {
    return getDirection();
}

Vec3 Camera::getBackward() const {
    return -getDirection();
}
