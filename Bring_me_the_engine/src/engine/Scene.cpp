#include "engine/Scene.h"
#include "engine/SceneLoader/SceneLoader.h"
#include "math/Vec.h"
#include "rendering/Shader.h"
#include "system/PathResolver.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

Scene::Scene() : m_view(Mat4::identity()), m_projection(Mat4::identity()) {
    m_camera = Camera(
        Vec3(-5.68114, 0.024997, -0.912596), // position à l'initialisation
        Vec3(0.025365, 0.0263991, -3.00793), // le point ciblé
        Vec3(0, 1, 0),                       // up
        45.0f,                               // FOV
        1600.0f / 800.0f,                    // aspect ratio
        0.1f, 100.0f);                       // near et far planes

    m_view = m_camera.getViewMatrix();
    m_projection = m_camera.getProjectionMatrix();

    SceneLoader::loadScene(1, m_entities, m_lightEntities, m_skybox, m_lightingManager);
}
Scene::Scene(const int & sceneIndex) : m_view(Mat4::identity()), m_projection(Mat4::identity()) {
    m_camera = Camera(
        Vec3(-5.68114, 0.024997, -0.912596), // position à l'initialisation
        Vec3(0.025365, 0.0263991, -3.00793), // le point ciblé
        Vec3(0, 1, 0),                       // up
        45.0f,                               // FOV
        1600.0f / 800.0f,                    // aspect ratio
        0.1f, 1000.0f);                       // near et far planes

    m_view = m_camera.getViewMatrix();
    m_projection = m_camera.getProjectionMatrix();
    SceneLoader::loadScene(sceneIndex, m_entities, m_lightEntities, m_skybox, m_lightingManager);
}

void Scene::update() {
    // Mise à jour des matrices de vue et de projection
    m_view = m_camera.getViewMatrix();
    m_projection = m_camera.getProjectionMatrix();

    // Mise à jour du frustum pour le culling
    m_frustum = m_frustum.updateFromCamera(m_camera);

    float angle = glfwGetTime();
    if (!m_entities.empty() && m_entities[0]->getName() == "Cube_qui_tourne") {
        m_entities[0]->setTransform(
            Mat4::Translation(Vec3(0, 0, -1.f)) *
            Mat4::rotateY(angle) *
            Mat4::rotateZ(angle));
    }
}