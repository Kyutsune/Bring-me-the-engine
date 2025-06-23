#include "engine/Scene.h"
#include "base/Vec.h"
#include "base/Shader.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Scene::Scene(Shader * shader) : shader(shader), model(Mat4::identity()), view(Mat4::identity()), projection(Mat4::identity()) {
    init();
}

void Scene::init() {
    this->camera = Camera(
        Vec3(2, 1, 3),    // position à l'initialisation
        Vec3(0, 0, 0),    // le point ciblé
        Vec3(0, 1, 0),    // up
        45.0f,            // FOV
        1600.0f / 800.0f, // aspect ratio
        0.1f, 100.0f);

    this->view = camera.getViewMatrix();
    this->projection = camera.getProjectionMatrix();
    this->model = Mat4::identity();
    this->initObjects();
}

void Scene::initObjects() {
    std::shared_ptr<Mesh> cubeMesh = createCube<std::shared_ptr<Mesh>>();
    Mat4 t;

    auto entity = std::make_shared<Entity>(t, cubeMesh);
    entities.push_back(entity);



    std::shared_ptr<Mesh> cubeMesh2 = createCube<std::shared_ptr<Mesh>>();
    Mat4 t2 = Mat4::Translation(Vec3(1, 0, -5));
    auto entity2 = std::make_shared<Entity>(t2, cubeMesh2);
    entities.push_back(entity2);


}

void Scene::update() {
    shader->use();

    float angle = glfwGetTime();

    entities[0]->setTransform(Mat4::Translation(Vec3(0, 0, -1.f)) * Mat4::rotateY(angle));

    // Dessin de chaque entité avec sa propre matrice de transformation
    for (const auto & entity : entities) {
        entity->draw_entity(*shader, view, projection);
    }

}
