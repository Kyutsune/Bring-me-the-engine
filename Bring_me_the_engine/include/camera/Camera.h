#pragma once
#include "math/Trigo.h"
#include "math/Vec.h"

/**
 * @class Camera
 * @brief Représente une caméra 3D avec position, orientation et paramètres de projection.
 *
 * La classe Camera gère la position, la direction (via une cible), l'orientation (up vector),
 * ainsi que les paramètres de la caméra pour la projection perspective.
 * Elle fournit des méthodes pour récupérer les matrices de vue et de projection,
 * ainsi que des vecteurs directions usuels (forward, right, up, etc.).
 */
class Camera {
private:
    Vec3 m_position;    ///< Position dans l’espace 3D.
    Vec3 m_target;      ///< Point visé par la caméra.
    Vec3 m_up;          ///< Vecteur "up" de la caméra.
    float m_fov;        ///< Champ de vision vertical en degrés.
    float m_aspectRatio;///< Ratio largeur / hauteur de la vue.
    float m_nearPlane;  ///< Plan proche de la vue.(valeur minimale pour le rendu)
    float m_farPlane;   ///< Plan lointain de la vue.(valeur maximale pour le rendu)
    Mat4 m_viewMatrix;  ///< Matrice de vue calculée.

public:
    /**
     * @brief Constructeur par défaut avec paramètres standards.
     * Position initiale à (0, 0, 3), regard vers l’origine, up vers Y+, FOV 45°, ratio 16:9.
     */
    inline Camera()
        : m_position(0.0f, 0.0f, 3.0f), m_target(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
          m_fov(45.0f), m_aspectRatio(16.0f / 9.0f), m_nearPlane(0.1f), m_farPlane(100.0f) {
    }

    /**
     * @brief Constructeur complet.
     * @param pos Position initiale.
     * @param tgt Cible regardée.
     * @param upDir Vecteur "up".
     * @param fovDegrees Champ de vision en degrés.
     * @param aspect Ratio largeur/hauteur.
     * @param nearP Plan proche.
     * @param farP Plan lointain.
     */
    inline Camera(const Vec3 & pos, const Vec3 & tgt, const Vec3 & upDir, float fovDegrees, float aspect, float nearP, float farP)
        : m_position(pos), m_target(tgt), m_up(upDir), m_fov(fovDegrees), m_aspectRatio(aspect), m_nearPlane(nearP), m_farPlane(farP) {}

    inline ~Camera() = default;

    /**
     * @brief Obtient la matrice de vue calculée à partir de la position, cible et vecteur up.
     * @return Mat4 Matrice de vue.
     */
    Mat4 getViewMatrix() const;

    /**
     * @brief Obtient la matrice de projection perspective basée sur fov, aspect, near et far.
     * @return Mat4 Matrice de projection.
     */
    Mat4 getProjectionMatrix() const;

    /// Accesseurs et mutateurs simples.
    inline const Vec3 & getPosition() const { return m_position; }
    inline void setPosition(const Vec3 & pos) { m_position = pos; }
    inline const Vec3 & getTarget() const { return m_target; }
    inline void setTarget(const Vec3 & tgt) { m_target = tgt; }

    /**
     * @brief Vecteur direction normalisé (du point position vers target).
     * @return Vec3 Direction normalisée.
     */
    inline Vec3 getDirection() const { return (m_target - m_position).normalized(); }

    /**
     * @brief Vecteur droit (right) de la caméra, perpendiculaire à la direction et up.
     * @return Vec3 Vecteur droit normalisé.
     */
    inline Vec3 getRight() const { return getDirection().cross(m_up).normalized(); }

    inline Vec3 getLeft() const { return -getRight(); }
    inline Vec3 getForward() const { return getDirection(); }
    inline Vec3 getBackward() const { return -getDirection(); }

    inline Vec3 getUp() const { return m_up; }
    inline Vec3 & getUp() { return m_up; }

    inline float getFov() const { return m_fov; }
    inline float getAspectRatio() const { return m_aspectRatio; }
    inline float getNearPlane() const { return m_nearPlane; }
    inline float getFarPlane() const { return m_farPlane; }
};