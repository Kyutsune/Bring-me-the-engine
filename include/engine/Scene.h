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

    inline Camera * getCamera() { return &m_camera; }
    inline const Camera & getCamera() const { return m_camera; }
    inline Mat4 & getView() { return m_view; }
    inline LightingManager & getLightingManager() { return m_lightingManager; }
    inline const LightingManager & getLightingManager() const { return m_lightingManager; }
    inline const Skybox * getSkybox() const { return m_skybox.get(); }
    inline std::vector<std::shared_ptr<Entity>> & getEntities() { return m_entities; }
    inline const std::vector<std::shared_ptr<Entity>> & getEntities() const { return m_entities; }
    inline const std::vector<std::shared_ptr<Entity>> & getLightEntities() const { return m_lightEntities; }
    inline const Frustum & getFrustum() const { return m_frustum; }

    inline const int getFogType() const { return m_lightingManager.settings().m_fogType; }
    inline void setFogType(int type) { m_lightingManager.settings().m_fogType = type; }
    inline float * getFogStart() { return &m_lightingManager.settings().m_fogStart; }
    inline float * getFogEnd() { return &m_lightingManager.settings().m_fogEnd; }
    inline float * getFogDensity() { return &m_lightingManager.settings().m_fogDensity; }
    inline void setFogDensity(float density) { m_lightingManager.settings().m_fogDensity = density; }
    inline Color & getFogColor() { return m_lightingManager.settings().m_fogColor; }


private:
    Camera m_camera;
    Mat4 m_view;
    Mat4 m_projection;

    std::vector<std::shared_ptr<Entity>> m_entities;

    LightingManager m_lightingManager;
    std::vector<std::shared_ptr<Entity>> m_lightEntities;

    std::unique_ptr<Skybox> m_skybox;

    Frustum m_frustum;
};