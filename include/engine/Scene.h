#pragma once

#include "rendering/Shader.h"
#include "rendering/Skybox.h"
#include "camera/Camera.h"
#include "camera/Frustum.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "engine/Mesh.h"
#include "geometry/Cube.h"
#include "geometry/Floor.h"
#include "geometry/Sphere.h"

#include <iostream>
#include <memory>
#include <vector>

class Scene {
public:
    Scene();
    void update();

    void initObjects();

    inline Camera * getCamera() { return &camera; }
    inline const Camera & getCamera() const { return camera; }
    inline Mat4 & getView() { return view; }
    inline LightingManager & getLightingManager() { return lightingManager; }
    inline const LightingManager & getLightingManager() const { return lightingManager; }
    const Skybox * getSkybox() const { return skybox.get(); }


    inline const int getFogType() const { return lightingManager.settings().fogType; }
    inline void setFogType(int type) { lightingManager.settings().fogType = type; }
    inline float * getFogStart() { return &lightingManager.settings().fogStart; }
    inline float * getFogEnd() { return &lightingManager.settings().fogEnd; }
    inline float * getFogDensity() { return &lightingManager.settings().fogDensity; }
    inline void setFogDensity(float density) { lightingManager.settings().fogDensity = density; }
    inline Color & getFogColor() { return lightingManager.settings().fogColor; }
    inline const Frustum & getFrustum() const { return frustum; }
    inline std::vector<std::shared_ptr<Entity>> & getEntities() { return entities; }
    inline const std::vector<std::shared_ptr<Entity>> & getEntities() const { return entities; }
    inline const std::vector<std::shared_ptr<Entity>> & getLightEntities() const { return lightEntities; }


private:
    Camera camera;
    // Ici chaque objet de la scène aura sa propre matrice de transformation donc pas de model global
    Mat4 view;
    Mat4 projection;

    std::vector<std::shared_ptr<Entity>> entities;

    LightingManager lightingManager;

    std::vector<std::shared_ptr<Entity>> lightEntities;

    std::unique_ptr<Skybox> skybox;

    Frustum frustum;
};