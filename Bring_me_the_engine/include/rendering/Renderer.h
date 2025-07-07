#pragma once

#include "camera/Camera.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "engine/Scene.h"
#include "rendering/Shader.h"
#include "rendering/Skybox.h"
#include "rendering/ShadowManager.h"
#include "system/PathResolver.h"

class Renderer {
public:
    Renderer(Shader * entityShader, Shader * lightShader, Shader * skyboxShader, Shader * boundingBoxShader, Shader * shadowDirShader, Shader * shadowPoncShader);

    void renderScene(const Scene & scene);

    void renderSkybox(const Skybox * skybox, const Mat4 & view, const Mat4 & projection);
    void renderEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);
    void renderLightEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);

    inline void initShadowMap() { m_shadowManager.init_directionnal_shadows(); }
    void debugSaveShadowMap(const std::string & filename);
    void renderShadowMapOnQuad();
    void renderFrame(const Scene & scene);

private:
    Shader * m_entityShader;
    Shader * m_lightShader;
    Shader * m_skyboxShader;
    Shader * m_boundingBoxShader;
    Shader * m_shadowShaderDirectionnal;
    Shader * m_shadowShaderPonctual;

    ShadowManager m_shadowManager;

    //AVENIR: à garder?? utile pour le debug mais bon en soit..
    Shader m_quadDebugShader = Shader(PathResolver::getResourcePath("shaders/debug/quad.vert"), PathResolver::getResourcePath("shaders/debug/quad.frag"));
};