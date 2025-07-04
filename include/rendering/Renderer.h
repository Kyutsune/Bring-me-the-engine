#pragma once

#include "camera/Camera.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "engine/Scene.h"
#include "rendering/Shader.h"
#include "rendering/Skybox.h"
#include "shadows/DirectionalShadowMap.h"
#include "shadows/PonctualShadowMap.h"

class Renderer {
public:
    Renderer(Shader * entityShader, Shader * lightShader, Shader * skyboxShader, Shader * boundingBoxShader, Shader * shadowDirShader, Shader * shadowPoncShader);

    void renderScene(const Scene & scene);

    void renderSkybox(const Skybox * skybox, const Mat4 & view, const Mat4 & projection);
    void renderEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);
    void renderLightEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);

    inline void initShadowMap() { shadowMapperDirectionnal.init(); }
    void debugSaveShadowMap(const std::string & filename);
    void renderShadowMapOnQuad();
    void renderFrame(const Scene & scene);

    void renderPonctualShadowMaps(const Scene & scene);

    Shader quadDebugShader = Shader("../shaders/debug/quad.vert", "../shaders/debug/quad.frag");

private:
    Shader * entityShader;
    Shader * lightShader;
    Shader * skyboxShader;
    Shader * boundingBoxShader;

    DirectionalShadowMap shadowMapperDirectionnal;
    Shader * shadowShaderDirectionnal;

    std::vector<PonctualShadowMap> shadowMapperPonctuals;
    Shader * shadowShaderPonctual;
};