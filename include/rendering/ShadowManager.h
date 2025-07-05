#pragma once

#include "shadows/DirectionalShadowMap.h"
#include "shadows/PonctualShadowMap.h"
#include "rendering/Shader.h"
#include "engine/Scene.h"

class ShadowManager {
public:
    ShadowManager(Shader* dirShadowShader, Shader* pointShadowShader);

    void init_directionnal_shadows(); // Initialise la shadow map directionnelle
    void renderShadows(const Scene& scene); // Rendu de toutes les ombres

    void bindShadows(Shader& shader, const Scene& scene); // Envoie les infos aux shaders principaux

    void debugSaveDirectionalShadow(const std::string& filename);
    void renderDebugQuad();

private:
    DirectionalShadowMap directionalShadow;
    std::vector<PonctualShadowMap> punctualShadows;

    Shader* dirShadowShader;
    Shader* pointShadowShader;
};