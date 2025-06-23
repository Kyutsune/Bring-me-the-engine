#include "engine/Scene.h"
#include "base/Vec.h"
#include "engine/Shader.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

void updateCameraUniforms(Shader & shader, const Mat4 & model, const Mat4 & view, const Mat4 & projection) {
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

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
    this->meshes.push_back(createCube<std::shared_ptr<Mesh>>());
}

void Scene::update() {
    // Utilisation du shader pour dessiner les objets
    shader->use();
    // // Pour l'instant on fait juste tourner l'objet
    float angle = glfwGetTime();
    this->model = Mat4::Translation(Vec3(0, 0, -1.f))*Mat4::rotateY(angle) ;

    std::cout<< "Model Matrix: " << this->model << "\n";

    updateCameraUniforms(*this->shader, this->model, this->view, this->projection);

    this->meshes[0]->draw();
}
