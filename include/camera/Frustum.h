#pragma once
#include "camera/Camera.h"
#include "math/PlaneBoundingVolume.h"

class Frustum {
public:
    Plane planes[6]; // left, right, bottom, top, near, far
public:
    // Met à jour les plans à partir de la matrice projection * view
    void update(const Mat4 & projectionViewMatrix);

    // Même fonction que update sauf que la mise à jour des plans se fait à partir des infos de la caméra
    Frustum updateFromCamera(const Camera & camera);

    // Teste si une AABB intersecte le frustum
    bool isBoxInFrustum(const AABB & box) const;

    // Calcule l'AABB qui englobe le frustum dans l'espace local du frustum (ou dans un espace donné)
    AABB computeBoundingBox() const;
};