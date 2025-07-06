#pragma once

#include "rendering/Texture.h"
#include <memory>

struct Material {
    // Pour les textures de chaque entité, on ajoute une texture diffuse pour la couleur de base,
    // Une normal map pour les détails de surface (souvent pour donner du relief),
    // et une specular map pour les reflets spéculaires particulier au contact de la surface.
    std::shared_ptr<Texture> m_diffuseTexture;
    std::shared_ptr<Texture> m_normalMap;
    std::shared_ptr<Texture> m_specularMap;

    bool m_useDiffuse;
    bool m_useNormal;
    bool m_useSpecular;
};