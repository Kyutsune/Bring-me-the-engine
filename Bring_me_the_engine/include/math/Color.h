#pragma once

#include <ostream>
#include <string>

struct Color {
    float r, g, b, a;
    Color()
        : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    Color operator+(const Color & other) const {
        return Color(r + other.r, g + other.g, b + other.b, a + other.a);
    }

    Color operator-(const Color & other) const {
        return Color(r - other.r, g - other.g, b - other.b, a - other.a);
    }

    friend std::ostream & operator<<(std::ostream & os, const Color & color) {
        os << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
        return os;
    }

    static Color red() {
        return Color(255.0f, 0.0f, 0.0f, 255.0f);
    }
    static Color green() {
        return Color(0.0f, 255.0f, 0.0f, 255.0f);
    }
    static Color blue() {
        return Color(0.0f, 0.0f, 255.0f, 255.0f);
    }
    static Color white() {
        return Color(255.0f, 255.0f, 255.0f, 255.0f);
    }
    static Color black() {
        return Color(0.0f, 0.0f, 0.0f, 255.0f);
    }
    static Color yellow() {
        return Color(255.0f, 255.0f, 0.0f, 255.0f);
    }
    static Color cyan() {
        return Color(0.0f, 255.0f, 255.0f, 255.0f);
    }
    static Color magenta() {
        return Color(255.0f, 0.0f, 255.0f, 255.0f);
    }
    static Color rose() {
        return Color(255.0f, 192.0f, 203.0f, 255.0f);
    }
};