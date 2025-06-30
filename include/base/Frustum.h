#pragma once
#include "base/PlaneBoundingVolume.h"

class Frustum {
private:
    Plane planes[6]; // left, right, bottom, top, near, far
public:
    // Met à jour les plans à partir de la matrice projection * view
    void update(const Mat4& projectionViewMatrix);

    // Teste si une AABB intersecte le frustum
    bool isBoxInFrustum(const AABB& box) const;
};