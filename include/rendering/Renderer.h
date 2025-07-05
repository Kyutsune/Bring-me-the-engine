#pragma once

#include "camera/Camera.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "engine/Scene.h"
#include "rendering/Shader.h"
#include "rendering/Skybox.h"
#include "rendering/ShadowManager.h"

class Renderer {
public:
    Renderer(Shader * entityShader, Shader * lightShader, Shader * skyboxShader, Shader * boundingBoxShader, Shader * shadowDirShader, Shader * shadowPoncShader);

    void renderScene(const Scene & scene);

    void renderSkybox(const Skybox * skybox, const Mat4 & view, const Mat4 & projection);
    void renderEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);
    void renderLightEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);

    inline void initShadowMap() { shadowManager.init_directionnal_shadows(); }
    void debugSaveShadowMap(const std::string & filename);
    void renderShadowMapOnQuad();
    void renderFrame(const Scene & scene);


    Shader quadDebugShader = Shader("../shaders/debug/quad.vert", "../shaders/debug/quad.frag");

private:
    Shader * entityShader;
    Shader * lightShader;
    Shader * skyboxShader;
    Shader * boundingBoxShader;
    Shader * shadowShaderDirectionnal;
    Shader * shadowShaderPonctual;

    ShadowManager shadowManager;
};