#pragma once

#include "engine/Entity.h"
#include "math/intersect/IntersectInfo.h"
#include "math/intersect/Ray.h"

namespace IntersectUtils {

    /**
     * @brief Teste l'intersection entre un rayon et un triangle.
     * 
     * @param o Origine du rayon.
     * @param d Direction normalisée du rayon.
     * @param tmax Distance maximale à tester le long du rayon.
     * @param a Premier sommet du triangle.
     * @param b Deuxième sommet du triangle.
     * @param c Troisième sommet du triangle.
     * @param[out] intersection Point d'intersection calculé si intersection vraie.
     * @param[out] normale_intersection Normale au point d'intersection.
     * @param[out] t Distance le long du rayon vers l'intersection.
     * @return true si intersection trouvée avant tmax, false sinon.
     */
    bool intersect(const Vec3 & o, const Vec3 & d, const float tmax, const Vec3 & a, const Vec3 & b, const Vec3 & c,
                   Vec3 & intersection, Vec3 & normale_intersection, float & t);

    /**
     * @brief Teste l'intersection d'un rayon avec une entité.
     * 
     * @param ray Rayon à tester.
     * @param entity Entité à tester.
     * @param[out] outInfo Informations détaillées sur l'intersection (si elle a lieu).
     * @param tmax Distance maximale à tester (par défaut 1000.0f).
     * @return true si intersection détectée, false sinon.
     */
    bool intersectEntity(const Ray & ray, const Entity & entity, IntersectionInfo & outInfo, float tmax = 1000.0f);

    /**
     * @brief Teste l'intersection d'un rayon avec le plan horizontal Y=0.
     * 
     * @param ray Rayon à tester.
     * @param[out] outHitPoint Point d'intersection sur le plan Y=0 si intersection.
     * @return true si intersection avec le plan Y=0, false sinon.
     */
    bool intersectRayWithPlaneY0(const Ray & ray, Vec3 & outHitPoint);

}
