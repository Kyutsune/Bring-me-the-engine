#pragma once

#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

/**
 * @brief Représente une couleur en RGBA avec des composants en float [0.0 - 1.0].
 * 
 * Les composantes rouge, verte, bleue et alpha sont stockées en float entre 0.0 et 1.0.
 * Plusieurs constructeurs permettent l'initialisation à partir de floats ou d'entiers sur 255.
 */
struct Color {
    float r; ///< Composante rouge
    float g; ///< Composante verte
    float b; ///< Composante bleue
    float a; ///< Composante alpha (opacité)

    /**
     * @brief Constructeur par défaut (couleur noire opaque).
     */
    Color()
        : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    /**
     * @brief Constructeur avec composantes en float.
     * @param r Rouge [0.0 - 1.0]
     * @param g Vert [0.0 - 1.0]
     * @param b Bleu [0.0 - 1.0]
     * @param a Alpha [0.0 - 1.0], par défaut 1.0 (opaque)
     */
    Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    /**
     * @brief Constructeur avec composantes entières [0-255].
     * @param r Rouge [0-255]
     * @param g Vert [0-255]
     * @param b Bleu [0-255]
     * @param a Alpha [0-255], par défaut 255 (opaque)
     */
    Color(const int & r, const int & g, const int & b, const int & a = 255)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

    /**
     * @brief Constructeur avec composantes uint8_t [0-255].
     * @param r Rouge [0-255]
     * @param g Vert [0-255]
     * @param b Bleu [0-255]
     * @param a Alpha [0-255], par défaut 255 (opaque)
     */
    Color(const uint8_t & r, const uint8_t & g, const uint8_t & b, const uint8_t & a = 255)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

    /**
     * @brief Additionne deux couleurs composante par composante.
     * @param other Autre couleur à additionner.
     * @return Nouvelle couleur résultante.
     */
    Color operator+(const Color & other) const {
        return Color(r + other.r, g + other.g, b + other.b, a + other.a);
    }

    /**
     * @brief Soustrait deux couleurs composante par composante.
     * @param other Autre couleur à soustraire.
     * @return Nouvelle couleur résultante.
     */
    Color operator-(const Color & other) const {
        return Color(r - other.r, g - other.g, b - other.b, a - other.a);
    }

    /**
     * @brief Affiche la couleur au format Color(r, g, b, a).
     */
    friend std::ostream & operator<<(std::ostream & os, const Color & color) {
        os << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
        return os;
    }

    /**
     * @brief Crée une couleur à partir de valeurs entières 0-255.
     * @param r Rouge [0-255]
     * @param g Vert [0-255]
     * @param b Bleu [0-255]
     * @param a Alpha [0-255], par défaut 255 (opaque)
     * @return Couleur convertie en float.
     */
    static Color from255(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    // Couleurs standards
    static Color red()     { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
    static Color green()   { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
    static Color blue()    { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
    static Color white()   { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
    static Color black()   { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
    static Color yellow()  { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
    static Color cyan()    { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
    static Color magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
    static Color rose()    { return Color(1.0f, 0.75f, 0.8f, 1.0f); }
};
