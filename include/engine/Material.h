#pragma once

#include "base/Texture.h"
#include <memory>

struct Material {
    // Pour les textures de chaque entité, on ajoute une texture diffuse pour la couleur de base,
    // Une normal map pour les détails de surface (souvent pour donner du relief),
    // et une specular map pour les reflets spéculaires particulier au contact de la surface.
    std::shared_ptr<Texture> diffuse_text;
    std::shared_ptr<Texture> normal_map;
    std::shared_ptr<Texture> specular_map;

    bool useDiffuse = true;
    bool useNormal = true;
    bool useSpecular = true;
};