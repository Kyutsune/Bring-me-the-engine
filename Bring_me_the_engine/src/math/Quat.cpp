#include "math/Quat.h"
#include <cmath>

Quat::Quat() : x(0), y(0), z(0), w(1) {}

Quat::Quat(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

Quat Quat::identity() {
    return Quat(0, 0, 0, 1);
}

Quat Quat::fromAxisAngle(const Vec3& axis, float angleRad) {
    float halfAngle = angleRad * 0.5f;
    float sinHalf = sin(halfAngle);
    return Quat(
        axis.x * sinHalf,
        axis.y * sinHalf,
        axis.z * sinHalf,
        cos(halfAngle)
    );
}

Quat Quat::operator*(const Quat& q) const {
    return Quat(
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w,
        w * q.w - x * q.x - y * q.y - z * q.z
    );
}

Quat Quat::normalized() const {
    float len = length();
    if (len == 0.0f) return identity();
    return Quat(x / len, y / len, z / len, w / len);
}

float Quat::length() const {
    return sqrt(x * x + y * y + z * z + w * w);
}

Quat Quat::fromEuler(const Vec3& euler) {
    // Moitiés d’angles
    float cx = cos(euler.x * 0.5f);
    float sx = sin(euler.x * 0.5f);
    float cy = cos(euler.y * 0.5f);
    float sy = sin(euler.y * 0.5f);
    float cz = cos(euler.z * 0.5f);
    float sz = sin(euler.z * 0.5f);

    // Ordre XYZ
    float qw = cx * cy * cz + sx * sy * sz;
    float qx = sx * cy * cz - cx * sy * sz;
    float qy = cx * sy * cz + sx * cy * sz;
    float qz = cx * cy * sz - sx * sy * cz;

    return Quat(qx, qy, qz, qw).normalized();
}

Mat4 Quat::toMat4() const {
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    Mat4 result;

    result.data[0]  = 1.0f - 2.0f * (yy + zz);
    result.data[1]  = 2.0f * (xy - wz);
    result.data[2]  = 2.0f * (xz + wy);
    result.data[3]  = 0.0f;

    result.data[4]  = 2.0f * (xy + wz);
    result.data[5]  = 1.0f - 2.0f * (xx + zz);
    result.data[6]  = 2.0f * (yz - wx);
    result.data[7]  = 0.0f;

    result.data[8]  = 2.0f * (xz - wy);
    result.data[9]  = 2.0f * (yz + wx);
    result.data[10] = 1.0f - 2.0f * (xx + yy);
    result.data[11] = 0.0f;

    result.data[12] = 0.0f;
    result.data[13] = 0.0f;
    result.data[14] = 0.0f;
    result.data[15] = 1.0f;

    return result;
}

Vec3 Quat::toEuler() const {
    Vec3 euler;

    // Pré-calculs
    float sinr_cosp = 2.0f * (w * x + y * z);
    float cosr_cosp = 1.0f - 2.0f * (x * x + y * y);
    euler.x = std::atan2(sinr_cosp, cosr_cosp); // X (pitch)

    float sinp = 2.0f * (w * y - z * x);
    if (std::abs(sinp) >= 1.0f)
        euler.y = std::copysign(M_PI / 2.0f, sinp); // Gimbal lock
    else
        euler.y = std::asin(sinp);                 // Y (yaw)

    float siny_cosp = 2.0f * (w * z + x * y);
    float cosy_cosp = 1.0f - 2.0f * (y * y + z * z);
    euler.z = std::atan2(siny_cosp, cosy_cosp);    // Z (roll)

    return euler;
}
