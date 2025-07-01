#pragma once

#include "base/Shader.h"
#include "base/Skybox.h"
#include "engine/Camera.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "engine/Mesh.h"
#include "utils/Cube.h"
#include "utils/Floor.h"
#include "utils/Sphere.h"
#include "base/Frustum.h"
#include <iostream>
#include <memory>
#include <vector>

class Scene {
public:
    Scene(Shader * shader, Shader * lightShader, Shader * skyboxShader, Shader * BboxShader);
    void init();
    void update();

    void initObjects();

    inline Camera * getCamera() { return &camera; }
    inline Mat4 & getView() { return view; }
    LightingManager & getLightingManager() { return lightingManager; }


    inline const int getFogType() const { return lightingManager.settings().fogType; }
    inline void setFogType(int type) { lightingManager.settings().fogType = type; }
    inline float * getFogStart() { return &lightingManager.settings().fogStart; }
    inline float * getFogEnd() { return &lightingManager.settings().fogEnd; }
    inline float * getFogDensity() { return &lightingManager.settings().fogDensity; }
    inline void setFogDensity(float density) { lightingManager.settings().fogDensity = density; }
    inline Color & getFogColor() { return lightingManager.settings().fogColor; }
private:
    Camera camera;
    // Ici chaque objet de la scène aura sa propre matrice de transformation donc pas de model global
    Mat4 view;
    Mat4 projection;

    std::vector<std::shared_ptr<Entity>> entities;

    LightingManager lightingManager;

    std::vector<std::shared_ptr<Entity>> lightEntities;

    Shader * shader;
    // Ce shader va me permettre de dessiner les lumières, on le fait à part pour éviter de mélanger les deux
    // ainsi que permettre de ne pas faire de lumière sur les lumières elles-mêmes
    Shader * lightShader;

    std::unique_ptr<Skybox> skybox;
    Shader * skyboxShader;

    Shader * bboxShader;
    Frustum frustum;
};