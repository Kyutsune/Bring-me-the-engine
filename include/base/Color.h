#pragma once

#include <string>

class Color {
public:
    float r, g, b, a;
    Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    std::string toString() const {
        return "Color(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
    }

    Color operator+(const Color & other) const {
        return Color(r + other.r, g + other.g, b + other.b, a + other.a);
    }

    Color operator-(const Color & other) const {
        return Color(r - other.r, g - other.g, b - other.b, a - other.a);
    }

    Color red() {
        return Color(1.0f, 0.0f, 0.0f, 1.0f);
    }
    Color green() {
        return Color(0.0f, 1.0f, 0.0f, 1.0f);
    }
    Color blue() {
        return Color(0.0f, 0.0f, 1.0f, 1.0f);
    }
    Color white() {
        return Color(1.0f, 1.0f, 1.0f, 1.0f);
    }
    Color black() {
        return Color(0.0f, 0.0f, 0.0f, 1.0f);
    }
    Color yellow() {
        return Color(1.0f, 1.0f, 0.0f, 1.0f);
    }
    Color cyan() {
        return Color(0.0f, 1.0f, 1.0f, 1.0f);
    }
    Color magenta() {
        return Color(1.0f, 0.0f, 1.0f, 1.0f);
    }
};