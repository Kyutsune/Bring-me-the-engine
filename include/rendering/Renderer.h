#pragma once

#include "camera/Camera.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "engine/Scene.h"
#include "rendering/Shader.h"
#include "rendering/Skybox.h"

class Renderer {
public:
    Renderer(Shader * entityShader, Shader * lightShader, Shader * skyboxShader, Shader * boundingBoxShader, Shader * shadowShader);

    void renderScene(const Scene & scene);

    void renderSkybox(const Skybox * skybox, const Mat4 & view, const Mat4 & projection);
    void renderEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);
    void renderLightEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);

    void initShadowMap();
    void renderShadowMap(const Scene & scene, Shader & shadowShader);
    void debugSaveShadowMap(const std::string & filename);
    void renderFrame(const Scene & scene);

    Shader quadDebugShader = Shader("../shaders/debug/quad.vert", "../shaders/debug/quad.frag");

private:
    Shader * entityShader;
    Shader * lightShader;
    Shader * skyboxShader;
    Shader * boundingBoxShader;
    Shader * shadowShader;

    GLuint shadowFBO;
    GLuint shadowMap;
    Mat4 lightSpaceMatrix;

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
};