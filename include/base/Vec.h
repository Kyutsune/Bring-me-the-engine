#pragma once
#include "base/Color.h"
#include <cmath>
#include <ostream>

struct Vec2 {
    float x, y;

    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Vec2 operator+(const Vec2 & other) const { return {x + other.x, y + other.y}; }
    Vec2 operator-(const Vec2 & other) const { return {x - other.x, y - other.y}; }
    Vec2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
    Vec2 operator/(float scalar) const { return {x / scalar, y / scalar}; }

    const float * ptr() const { return &x; }
    float * ptr() { return &x; }

    // Simplement une distance euclidienne, qui sera la même pour Vec2 et Vec3
    float length() const { return sqrt(x * x + y * y); }

    // Normalisation basique, on veut un vecteur de longueur 1
    Vec2 normalized() const {
        float len = length();
        return len == 0 ? *this : *this / len;
    }

    Vec2 operator-() const {
        return Vec2(-x, -y);
    }

    friend std::ostream & operator<<(std::ostream & os, const Vec2 & v) {
        return os << "Vec2(" << v.x << ", " << v.y << ")";
    }
};

struct Vec3 {
    float x, y, z;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    Vec3(const Color & color) : x(color.r / 255.0f), y(color.g / 255.0f), z(color.b / 255.0f) {}

    Vec3 operator+(const Vec3 & other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vec3 operator-(const Vec3 & other) const { return {x - other.x, y - other.y, z - other.z}; }
    Vec3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
    Vec3 operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }
    Vec3 operator+=(const Vec3 & other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    const float * ptr() const { return &x; }
    float * ptr() { return &x; }

    float length() const { return std::sqrt(x * x + y * y + z * z); }
    Vec3 normalized() const {
        float len = length();
        return len == 0 ? *this : *this / len;
    }

    float dot(const Vec3 & other) const { return x * other.x + y * other.y + z * other.z; }

    Vec3 cross(const Vec3 & other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
    }

    Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }

    friend std::ostream & operator<<(std::ostream & os, const Vec3 & v) {
        return os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
};

inline Vec3 normalize(Vec3 v) {
    float len = v.length();
    if (len != 0.0f) {
        v = v / len;
    }
    return v;
}

struct Vec4 {
    float x, y, z, w;

    Vec4(float x = 0, float y = 0, float z = 0, float w = 0)
        : x(x), y(y), z(z), w(w) {}

    Vec4 operator+(const Vec4 & o) const { return {x + o.x, y + o.y, z + o.z, w + o.w}; }
    Vec4 operator-(const Vec4 & o) const { return {x - o.x, y - o.y, z - o.z, w - o.w}; }
    Vec4 operator*(float s) const { return {x * s, y * s, z * s, w * s}; }
    Vec4 operator/(float s) const { return {x / s, y / s, z / s, w / s}; }

    const float * ptr() const { return &x; }
    float * ptr() { return &x; }

    Vec4 operator-() const {
        return Vec4(-x, -y, -z, -w);
    }
    friend std::ostream & operator<<(std::ostream & os, const Vec4 & v) {
        return os << "Vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    }
};

struct Mat4 {
    float data[16];

    Mat4();
    Mat4(std::initializer_list<float> list);

    static Mat4 identity();
    static Mat4 lookAt(const Vec3 & eye, const Vec3 & center, const Vec3 & up);
    static Mat4 perspective(float fovRadians, float aspect, float near, float far);
    static Mat4 rotateY(float angleRadians);
    static Mat4 rotateZ(float angleRadians);
    static Mat4 Translation(const Vec3 & translation);
    static Mat4 Scale(const Vec3 & scale);
    static Mat4 Scale(float scaleX, float scaleY, float scaleZ);
    static Mat4 Scale(float scaleFactor);

    Mat4 rotateX(float angleRadians);
    Mat4 rotate(const Vec3 & axis, float angle);
    void setIdentity();

    Mat4 operator*(const Mat4 & other) const;
    Mat4 & translate(const Vec3 & t);

    const float * ptr() const;
    float * ptr();
    Mat4 removeTranslation() const;

    friend std::ostream & operator<<(std::ostream & os, const Mat4 & m);
};

inline Vec3 operator*(const Mat4 & mat, const Vec3 & vec) {
    float x = mat.data[0] * vec.x + mat.data[4] * vec.y + mat.data[8] * vec.z + mat.data[12];
    float y = mat.data[1] * vec.x + mat.data[5] * vec.y + mat.data[9] * vec.z + mat.data[13];
    float z = mat.data[2] * vec.x + mat.data[6] * vec.y + mat.data[10] * vec.z + mat.data[14];
    return Vec3(x, y, z);
}
