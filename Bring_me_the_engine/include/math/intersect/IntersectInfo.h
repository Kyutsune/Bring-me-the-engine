#pragma once

#include <limits>
#include <memory>
#include "math/Vec.h"
#include "engine/Entity.h"

/**
 * @brief Contient les informations d'intersection lors d'un test rayon/objet.
 * 
 * Stocke si une intersection a eu lieu, la distance, la position, la normale au point d'intersection,
 * ainsi qu'un pointeur vers l'entité intersectée.
 */
struct IntersectionInfo {
    bool hit = false; ///< Vrai si une intersection a été détectée.
    float t = std::numeric_limits<float>::max(); ///< Distance la plus proche sur le rayon.
    Vec3 position; ///< Position 3D du point d'intersection.
    Vec3 normal; ///< Vecteur normal à la surface au point d'intersection.
    std::shared_ptr<Entity> entity = nullptr; ///< Entité intersectée, nullptr si aucune.
};
