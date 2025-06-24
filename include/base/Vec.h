#pragma once
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
    float length() const { return std::sqrt(x * x + y * y); }

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

    Vec3 operator+(const Vec3 & other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vec3 operator-(const Vec3 & other) const { return {x - other.x, y - other.y, z - other.z}; }
    Vec3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
    Vec3 operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }

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

    Mat4() {
        for (int i = 0; i < 16; ++i)
            data[i] = 0.0f;
        data[0] = data[5] = data[10] = data[15] = 1.0f;
    }

    static Mat4 identity() {
        return Mat4();
    }

    Mat4(std::initializer_list<float> list) {
        int i = 0;
        for (auto it = list.begin(); it != list.end() && i < 16; ++it, ++i) {
            data[i] = *it;
        }
        for (; i < 16; ++i) {
            data[i] = 0.0f;
        }
    }

    static Mat4 lookAt(const Vec3 & eye, const Vec3 & center, const Vec3 & up) {
        Vec3 f = (center - eye).normalized();
        Vec3 s = f.cross(up).normalized();
        Vec3 u = s.cross(f);

        Mat4 result;
        result.data[0] = s.x;
        result.data[1] = u.x;
        result.data[2] = -f.x;
        result.data[3] = 0.0f;

        result.data[4] = s.y;
        result.data[5] = u.y;
        result.data[6] = -f.y;
        result.data[7] = 0.0f;

        result.data[8] = s.z;
        result.data[9] = u.z;
        result.data[10] = -f.z;
        result.data[11] = 0.0f;

        result.data[12] = -s.dot(eye);
        result.data[13] = -u.dot(eye);
        result.data[14] = f.dot(eye);
        result.data[15] = 1.0f;

        return result;
    }

    static Mat4 perspective(float fovRadians, float aspect, float near, float far) {
        Mat4 result;
        float tanHalfFovy = tan(fovRadians / 2.0f);

        result.data[0] = 1.0f / (aspect * tanHalfFovy);
        result.data[5] = 1.0f / (tanHalfFovy);
        result.data[10] = -(far + near) / (far - near);
        result.data[11] = -1.0f;
        result.data[14] = -(2.0f * far * near) / (far - near);
        // les autres éléments restent à 0

        return result;
    }

    const float * ptr() const { return data; }
    float * ptr() { return data; }

    friend std::ostream & operator<<(std::ostream & os, const Mat4 & m) {
        return os << m.data[0] << ", " << m.data[1] << ", " << m.data[2] << ", " << m.data[3] << ")\n"
                  << m.data[4] << ", " << m.data[5] << ", " << m.data[6] << ", " << m.data[7] << ")\n"
                  << m.data[8] << ", " << m.data[9] << ", " << m.data[10] << ", " << m.data[11] << ")\n"
                  << m.data[12] << ", " << m.data[13] << ", " << m.data[14] << ", " << m.data[15] << ")\n";
    }

    Mat4 rotateX(float angleRadians) {
        Mat4 result;
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        result.data[0] = 1.0f;
        result.data[1] = 0.0f;
        result.data[2] = 0.0f;
        result.data[3] = 0.0f;

        result.data[4] = 0.0f;
        result.data[5] = c;
        result.data[6] = -s;
        result.data[7] = 0.0f;

        result.data[8] = 0.0f;
        result.data[9] = s;
        result.data[10] = c;
        result.data[11] = 0.0f;

        result.data[12] = 0.0f;
        result.data[13] = 0.0f;
        result.data[14] = 0.0f;
        result.data[15] = 1.0f;

        return result;
    }

    static Mat4 rotateY(float angleRadians) {
        Mat4 result;
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        result.data[0] = c;
        result.data[1] = 0.0f;
        result.data[2] = -s;
        result.data[3] = 0.0f;

        result.data[4] = 0.0f;
        result.data[5] = 1.0f;
        result.data[6] = 0.0f;
        result.data[7] = 0.0f;

        result.data[8] = s;
        result.data[9] = 0.0f;
        result.data[10] = c;
        result.data[11] = 0.0f;

        result.data[12] = 0.0f;
        result.data[13] = 0.0f;
        result.data[14] = 0.0f;
        result.data[15] = 1.0f;

        return result;
    }

    static Mat4 rotateZ(float angleRadians) {
        Mat4 result;
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        result.data[0] = c;
        result.data[1] = -s;
        result.data[2] = 0.0f;
        result.data[3] = 0.0f;

        result.data[4] = s;
        result.data[5] = c;
        result.data[6] = 0.0f;
        result.data[7] = 0.0f;

        result.data[8] = 0.0f;
        result.data[9] = 0.0f;
        result.data[10] = 1.0f;
        result.data[11] = 0.0f;

        result.data[12] = 0.0f;
        result.data[13] = 0.0f;
        result.data[14] = 0.0f;
        result.data[15] = 1.0f;

        return result;
    }

    Mat4 rotate(const Vec3 & axis, float angle) {
        Vec3 u = axis.normalized();

        float c = cos(angle);
        float s = sin(angle);
        float one_c = 1.0f - c;

        float ux = u.x;
        float uy = u.y;
        float uz = u.z;

        return Mat4({c + ux * ux * one_c, ux * uy * one_c - uz * s, ux * uz * one_c + uy * s, 0.f,
                     uy * ux * one_c + uz * s, c + uy * uy * one_c, uy * uz * one_c - ux * s, 0.f,
                     uz * ux * one_c - uy * s, uz * uy * one_c + ux * s, c + uz * uz * one_c, 0.f,
                     0.f, 0.f, 0.f, 1.f});
    }

    void setIdentity() {
        for (int i = 0; i < 16; ++i)
            data[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }

    Mat4 operator*(const Mat4 & other) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.data[i * 4 + j] = data[i * 4 + 0] * other.data[0 * 4 + j] +
                                         data[i * 4 + 1] * other.data[1 * 4 + j] +
                                         data[i * 4 + 2] * other.data[2 * 4 + j] +
                                         data[i * 4 + 3] * other.data[3 * 4 + j];
            }
        }
        return result;
    }

    Mat4 operator*(const Vec3 & v) const {
        Mat4 result;
        result.data[0] = data[0] * v.x + data[4] * v.y + data[8] * v.z + data[12];
        result.data[1] = data[1] * v.x + data[5] * v.y + data[9] * v.z + data[13];
        result.data[2] = data[2] * v.x + data[6] * v.y + data[10] * v.z + data[14];
        result.data[3] = 1.0f;
        return result;
    }

    Mat4 & translate(const Vec3 & t) {
        Mat4 translation = Mat4::Translation(t);
        *this = *this * translation;
        return *this;
    }

    static Mat4 Translation(const Vec3 & translation) {
        Mat4 result;
        result.data[12] = translation.x;
        result.data[13] = translation.y;
        result.data[14] = translation.z;
        return result;
    }
};

// Free function for Mat4 * Vec3 multiplication
inline Vec3 operator*(const Mat4 & mat, const Vec3 & vec) {
    // Treat Vec3 as a Vec4 with w = 1 for affine transformations
    float x = mat.data[0] * vec.x + mat.data[4] * vec.y + mat.data[8] * vec.z + mat.data[12];
    float y = mat.data[1] * vec.x + mat.data[5] * vec.y + mat.data[9] * vec.z + mat.data[13];
    float z = mat.data[2] * vec.x + mat.data[6] * vec.y + mat.data[10] * vec.z + mat.data[14];
    return Vec3(x, y, z);
}
