#pragma once
#include "math/Vec.h"

/**
 * @brief Représente un rayon dans l'espace 3D.
 * 
 * Un rayon est défini par une origine et une direction normalisée.
 */
struct Ray {
    Vec3 origin;    ///< Origine du rayon
    Vec3 direction; ///< Direction normalisée du rayon

    /**
     * @brief Constructeur.
     * 
     * Normalise automatiquement la direction fournie.
     * @param o Origine du rayon.
     * @param d Direction du rayon (normalisée automatiquement).
     */
    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d.normalized()) {}

    /**
     * @brief Génère un rayon à partir des coordonnées souris à l'écran.
     * 
     * @param mouseX Coordonnée X de la souris.
     * @param mouseY Coordonnée Y de la souris.
     * @return Rayon calculé dans l'espace 3D.
     */
    static Ray generateRayFromScreen(double mouseX, double mouseY);

    /**
     * @brief Pour afficher le rayon sur la sortie standard.
     */
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
        os << "Ray(origin: " << ray.origin << ", direction: " << ray.direction << ")";
        return os;
    }
};
