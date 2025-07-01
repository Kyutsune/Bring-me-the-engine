#pragma once

#include "rendering/Shader.h"
#include "rendering/Skybox.h"
#include "camera/Camera.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "engine/Scene.h"

class Renderer {
public:
    Renderer(Shader * entityShader, Shader * lightShader, Shader * skyboxShader, Shader * boundingBoxShader);

    void renderScene(const Scene & scene);

private:
    Shader * entityShader;
    Shader * lightShader;
    Shader * skyboxShader;
    Shader * boundingBoxShader;

    void renderSkybox(const Skybox * skybox, const Mat4 & view, const Mat4 & projection);
    void renderEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);
    void renderLightEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection);
};