#pragma once

#include "math/Color.h"
#include <cmath>
#include <ostream>

// TODO: Mettre de l'ordre dans ce bordel.. pas forcément séparer en deux fichiers car... pourquoi? ça à du sens ensemble mais au moins bien foutre
//  Les déclarations dans le cpp
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

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    Vec3(const Color & color);

    Vec3 operator+(const Vec3 & other) const;
    Vec3 operator-(const Vec3 & other) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator*(const Vec3 & other) const;
    Vec3 operator/(float scalar) const;

    Vec3 operator+=(const Vec3 & other);
    Vec3 operator-=(const Vec3 & other);

    Vec3 operator-() const;

    const float * ptr() const;
    float * ptr();

    float length() const;
    Vec3 normalized() const;

    float dot(const Vec3 & other) const;
    Vec3 cross(const Vec3 & other) const;

    friend Vec3 operator*(float scalar, const Vec3 & v);
    friend std::ostream & operator<<(std::ostream & os, const Vec3 & v);
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

    Vec4(const Vec3 & v, float w = 1.0f) {
        x = v.x;
        y = v.y;
        z = v.z;
        this->w = w;
    }

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
    // Mes matrices sont stockées en ligne majeure, donc les colonnes sont stockées consécutivement
    // mes translations sont dans data[12], data[13], data[14]
    // ce qui implique que mes * sont dans le sens inverse de la convention glsl qui elle est en colonne majeure
    // Concrètement m_transform = S * R * T;  fait S puis R et finalement T, pas l'inverse comme en glsl
    float data[16];

    Mat4();
    Mat4(std::initializer_list<float> list);

    static Mat4 identity();
    static Mat4 lookAt(const Vec3 & eye, const Vec3 & center, const Vec3 & up);
    static Mat4 perspective(float fovRadians, float aspect, float near, float far);
    static Mat4 rotateX(float angleRadians);
    static Mat4 rotateY(float angleRadians);
    static Mat4 rotateZ(float angleRadians);
    static Mat4 rotateXYZ(const Vec3 & anglesRadians);
    static Mat4 Translation(const Vec3 & translation);
    static Mat4 Scale(const Vec3 & scale);
    static Mat4 Scale(float scaleX, float scaleY, float scaleZ);
    static Mat4 Scale(float scaleFactor);

    
    Mat4 rotate(const Vec3 & axis, float angle);
    void setIdentity();

    Mat4 operator*(const Mat4 & other) const;
    Mat4 & translate(const Vec3 & t);
    void setTranslation(const Vec3 & t);
    Mat4 removeTranslation() const;

    const float * ptr() const;
    float * ptr();

    static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);

    Vec3 getTranslation() const;
    Vec3 getScale() const;
    Vec3 getEulerAngles() const;
    Mat4 fromEulerAngles(const Vec3 & euler);


    Mat4 transpose() const;
    Mat4 inverse() const;

    friend std::ostream & operator<<(std::ostream & os, const Mat4 & m);
    float operator[](size_t index) const;
    float & operator[](size_t index);
    Mat4 & operator=(const Mat4 & other);
};

inline Vec3 operator*(const Mat4 & mat, const Vec3 & vec) {
    float x = mat.data[0] * vec.x + mat.data[4] * vec.y + mat.data[8] * vec.z + mat.data[12];
    float y = mat.data[1] * vec.x + mat.data[5] * vec.y + mat.data[9] * vec.z + mat.data[13];
    float z = mat.data[2] * vec.x + mat.data[6] * vec.y + mat.data[10] * vec.z + mat.data[14];
    float w = mat.data[3] * vec.x + mat.data[7] * vec.y + mat.data[11] * vec.z + mat.data[15];

    if (w != 0.0f) {
        x /= w;
        y /= w;
        z /= w;
    }

    return Vec3(x, y, z);
}

inline Vec3 transformPoint(const Mat4 & mat, const Vec3 & vec) {
    float x = mat.data[0] * vec.x + mat.data[4] * vec.y + mat.data[8] * vec.z + mat.data[12];
    float y = mat.data[1] * vec.x + mat.data[5] * vec.y + mat.data[9] * vec.z + mat.data[13];
    float z = mat.data[2] * vec.x + mat.data[6] * vec.y + mat.data[10] * vec.z + mat.data[14];
    // PAS de division par w !
    return Vec3(x, y, z);
}

inline Vec4 operator*(const Mat4 & mat, const Vec4 & vec) {
    Vec4 result;
    result.x = mat.data[0] * vec.x + mat.data[4] * vec.y + mat.data[8] * vec.z + mat.data[12] * vec.w;
    result.y = mat.data[1] * vec.x + mat.data[5] * vec.y + mat.data[9] * vec.z + mat.data[13] * vec.w;
    result.z = mat.data[2] * vec.x + mat.data[6] * vec.y + mat.data[10] * vec.z + mat.data[14] * vec.w;
    result.w = mat.data[3] * vec.x + mat.data[7] * vec.y + mat.data[11] * vec.z + mat.data[15] * vec.w;
    return result;
}