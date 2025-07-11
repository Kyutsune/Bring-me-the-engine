#pragma once

#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

struct Color {
    float r, g, b, a;
    Color()
        : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    Color(const int & r, const int & g, const int & b, const int & a = 255)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {
    }

    Color(const uint8_t & r, const uint8_t & g, const uint8_t & b, const uint8_t & a = 255)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

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

    static Color from255(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    static Color red() {
        return Color(1.0f, 0.0f, 0.0f, 1.0f);
    }
    static Color green() {
        return Color(0.0f, 1.0f, 0.0f, 1.0f);
    }
    static Color blue() {
        return Color(0.0f, 0.0f, 1.0f, 1.0f);
    }
    static Color white() {
        return Color(1.0f, 1.0f, 1.0f, 1.0f);
    }
    static Color black() {
        return Color(0.0f, 0.0f, 0.0f, 1.0f);
    }
    static Color yellow() {
        return Color(1.0f, 1.0f, 0.0f, 1.0f);
    }
    static Color cyan() {
        return Color(0.0f, 1.0f, 1.0f, 1.0f);
    }
    static Color magenta() {
        return Color(1.0f, 0.0f, 1.0f, 1.0f);
    }
    static Color rose() {
        return Color(1.0f, 0.75f, 0.8f, 1.0f);
    }
};