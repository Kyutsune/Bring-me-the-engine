#include "engine/Scene.h"
#include "base/Shader.h"
#include "base/Vec.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Scene::Scene(Shader * shader) : shader(shader), view(Mat4::identity()), projection(Mat4::identity()) {
    init();
}

void Scene::init() {
    this->camera = Camera(
        Vec3(0, 0, 3),    // position à l'initialisation
        Vec3(0, 0, 0),    // le point ciblé
        Vec3(0, 1, 0),    // up
        45.0f,            // FOV
        1600.0f / 800.0f, // aspect ratio
        0.1f, 100.0f);

    this->view = camera.getViewMatrix();
    this->projection = camera.getProjectionMatrix();
    this->initObjects();

    lightingManager.settings().ambientColor = Vec3(1.f, 1.f, 1.f);
    lightingManager.settings().ambientStrength = 0.2f;

    lightingManager.settings().specularStrength = 0.6f;
    lightingManager.settings().shininess = 64.f;

    lightingManager.addLight({Vec3(0, 2, -3), Vec3(0, -1, 0), Vec3(1, 1, 1), 1.f});
    // lightingManager.addLight({Vec3(0, 2, 3), Vec3(0, -1, 0), Vec3(1,1,1), 0.5f});

    std::shared_ptr<Mesh> lightMesh = createCube<std::shared_ptr<Mesh>>();
    for (const auto & light : lightingManager.getLights()) {
        Mat4 lightTransform = Mat4::Translation(light.position);
        auto lightEntity = std::make_shared<Entity>(lightTransform, lightMesh);
        lightEntities.push_back(lightEntity);
    }
}

void Scene::initObjects() {
    std::shared_ptr<Mesh> cubeMesh = createCube<std::shared_ptr<Mesh>>(Color::yellow());
    Mat4 t;

    auto entity = std::make_shared<Entity>(t, cubeMesh);
    entities.push_back(entity);

    std::shared_ptr<Mesh> cubeMesh2 = createCube<std::shared_ptr<Mesh>>(Color::cyan());
    Mat4 t2 = Mat4::Translation(Vec3(1, 0, -5));
    auto entity2 = std::make_shared<Entity>(t2, cubeMesh2);
    entities.push_back(entity2);

    std::shared_ptr<Mesh> floorMesh = createFloor<std::shared_ptr<Mesh>>(25.f, -1.f);
    Mat4 t3;
    auto entity3 = std::make_shared<Entity>(t3, floorMesh);
    entities.push_back(entity3);
}

void Scene::update() {
    view = camera.getViewMatrix();
    projection = camera.getProjectionMatrix();

    lightingManager.apply(*shader, camera.getPosition());

    float angle = glfwGetTime();

    entities[0]->setTransform(Mat4::Translation(Vec3(0, 0, -1.f)) * Mat4::rotateY(angle));

    // Dessin de chaque entité avec sa propre matrice de transformation
    for (const auto & entity : entities) {
        entity->draw_entity(*shader, view, projection);
    }

    for (const auto & entity : lightEntities) {
        entity->draw_entity(*shader, view, projection);
    }
}
