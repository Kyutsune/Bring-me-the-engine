#pragma once
#include "camera/Camera.h"
#include "math/PlaneBoundingVolume.h"

/**
 * @class Frustum
 * @brief Représente un frustum de vue, défini par 6 plans (left, right, bottom, top, near, far).
 *
 * Cette classe permet de construire et mettre à jour le frustum à partir d'une matrice projection * view
 * ou directement à partir d'une caméra. Elle propose également des fonctions de test d'intersection avec une AABB
 * ainsi que le calcul d'une AABB englobante du frustum.
 */
class Frustum {
public:
    Plane m_planes[6]; ///< Tableau des 6 plans du frustum : gauche, droite, bas, haut, proche, loin.

public:
    /**
     * @brief Met à jour les plans du frustum à partir de la matrice projection * view.
     * @param projectionViewMatrix Matrice combinée projection * view.
     * @deprecated Cette méthode est dépréciée. Utilisez plutôt updateFromCamera().
     * @note Cette méthode est dépréciée mais je la garde à une fin éducative.
     */
    void update(const Mat4 & projectionViewMatrix);

    /**
     * @brief Met à jour le frustum directement à partir des paramètres de la caméra.
     * @param camera La caméra utilisée pour extraire les plans.
     * @return Frustum mis à jour.
     */
    Frustum updateFromCamera(const Camera & camera);

    /**
     * @brief Teste si une AABB (boîte englobante axis-aligned) intersecte le frustum.
     * @param box La boîte axis-aligned à tester.
     * @return true si la boîte est partiellement ou totalement dans le frustum, false sinon.
     */
    bool isBoxInFrustum(const AABB & box) const;

    /**
     * @brief Calcule une AABB englobant tout le volume du frustum.
     * @return AABB englobante du frustum.
     */
    AABB computeBoundingBox() const;
};
