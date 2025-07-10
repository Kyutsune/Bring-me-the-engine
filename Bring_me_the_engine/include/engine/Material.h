#pragma once

#include "rendering/Texture.h"
#include <memory>

struct Material {
    // Pour les textures de chaque entité, on ajoute une texture diffuse pour la couleur de base,
    // Une normal map pour les détails de surface (souvent pour donner du relief),
    // et une specular map pour les reflets spéculaires particulier au contact de la surface.
    std::shared_ptr<Texture> m_diffuseTexture = nullptr;
    std::shared_ptr<Texture> m_normalMap = nullptr;
    std::shared_ptr<Texture> m_specularMap = nullptr;

    bool m_useDiffuse = false;
    bool m_useNormal = false;
    bool m_useSpecular = false;

    Material() = default;

    Material(const std::shared_ptr<Texture> & diffuse,
             const std::shared_ptr<Texture> & normal,
             const std::shared_ptr<Texture> & specular)
        : m_diffuseTexture(diffuse),
          m_normalMap(normal),
          m_specularMap(specular),
          m_useDiffuse(diffuse != nullptr),
          m_useNormal(normal != nullptr),
          m_useSpecular(specular != nullptr) {}
};