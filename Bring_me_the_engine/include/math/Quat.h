#pragma once

#include "math/Vec.h"

/**
 * @brief Représente un quaternion pour les rotations 3D.
 *
 * Utilisé pour manipuler et interpoler des rotations sans singularités.
 */
class Quat {
public:
    float x; ///< Composante x du quaternion (vecteur imaginaire)
    float y; ///< Composante y du quaternion (vecteur imaginaire)
    float z; ///< Composante z du quaternion (vecteur imaginaire)
    float w; ///< Composante w du quaternion (partie réelle)

    /**
     * @brief Constructeur par défaut : quaternion identité (0,0,0,1).
     */
    Quat();

    /**
     * @brief Constructeur avec composantes explicites.
     * @param x Composante x.
     * @param y Composante y.
     * @param z Composante z.
     * @param w Composante w.
     */
    Quat(float x, float y, float z, float w);

    /**
     * @brief Quaternion identité (rotation nulle).
     * @return Quaternion unité (0, 0, 0, 1).
     */
    static Quat identity();

    /**
     * @brief Crée un quaternion à partir d'un axe unitaire et d'un angle en radians.
     * @param axis Axe de rotation (doit être normalisé).
     * @param angleRad Angle de rotation en radians.
     * @return Quaternion représentant cette rotation.
     */
    static Quat fromAxisAngle(const Vec3 & axis, float angleRad);

    /**
     * @brief Crée un quaternion à partir d'angles d'Euler (en radians).
     * @param eulerRad Vecteur des angles (pitch, yaw, roll).
     * @return Quaternion équivalent.
     */
    static Quat fromEuler(const Vec3 & eulerRad);

    /**
     * @brief Convertit le quaternion en matrice 4x4 de transformation.
     * @return Matrice de rotation 4x4.
     */
    Mat4 toMat4() const;

    /**
     * @brief Convertit le quaternion en angles d'Euler (radians).
     * @return Vecteur des angles (pitch, yaw, roll).
     */
    Vec3 toEuler() const;

    /**
     * @brief Opérateur de multiplication quaternionique.
     * @param q Quaternion à multiplier.
     * @return Produit quaternionique (composition des rotations).
     */
    Quat operator*(const Quat & q) const;

    /**
     * @brief Retourne une copie normalisée du quaternion.
     * @return Quaternion normalisé (longueur 1).
     */
    Quat normalized() const;

    /**
     * @brief Calcule la norme (longueur) du quaternion.
     * @return Norme positive.
     */
    float length() const;

    /**
     * @brief Affiche le quaternion au format Quat(x, y, z, w).
     */
    // Sert à rien, mais j'ai besoin de comprendre la dinguerie que sont les quaternions
    friend std::ostream & operator<<(std::ostream & os, const Quat & q) {
        os << "Quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
        return os;
    }
};
