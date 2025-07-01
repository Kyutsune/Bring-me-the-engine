#pragma once

#include "engine/Scene.h"
#include "engine/Camera.h"
#include "engine/LightingManager.h"
#include "base/Shader.h"
#include "engine/Entity.h"
#include "base/Skybox.h"

class Renderer {
public:
    Renderer(Shader* entityShader, Shader* lightShader, Shader* skyboxShader);

    void renderScene(const Scene& scene);

private:
    Shader* entityShader;
    Shader* lightShader;
    Shader* skyboxShader;

    void renderSkybox(const Skybox* skybox, const Mat4& view, const Mat4& projection);
    void renderEntities(const Scene& scene, const Mat4& view, const Mat4& projection);
    void renderLightEntities(const Scene& scene, const Mat4& view, const Mat4& projection);
};