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

    this->lights.push_back(Light{
        Vec3(0, 2, -3), // position de la lumière
        Vec3(0, 0, 0),  // direction de la lumière (non utilisée pour une lumière ponctuelle)
        Vec3(1, 1, 1),  // couleur de la lumière
        0.01f          // intensité de la lumière
    });
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

    std::shared_ptr<Mesh> floorMesh = createFloor<std::shared_ptr<Mesh>>(25.f, -1.f, 16.f, 144.f, 48.f);
    Mat4 t3;
    auto entity3 = std::make_shared<Entity>(t3, floorMesh);
    entities.push_back(entity3);
}

void Scene::update() {
    view = camera.getViewMatrix();
    projection = camera.getProjectionMatrix();

    shader->use();

    shader->set("lightPos", lights[0].position);
    shader->set("lightColor", lights[0].color);
    std::cout<< "Light Position: " << lights[0].position << std::endl;
    std::cout<< "Light Color: " << lights[0].color << std::endl;
    std::cout<< "Light Intensity: " << lights[0].intensity << std::endl;
    shader->set("lightIntensity", lights[0].intensity);
    shader->set("viewPos", camera.getPosition()); // nouvelle uniform
    shader->set("ambientStrength", 0.1f);
    shader->set("specularStrength", 0.2f);
    shader->set("shininess", 32); // Plus grand = reflet plus petit et plus net

    float angle = glfwGetTime();

    entities[0]->setTransform(Mat4::Translation(Vec3(0, 0, -1.f)) * Mat4::rotateY(angle));

    // Dessin de chaque entité avec sa propre matrice de transformation
    for (const auto & entity : entities) {
        entity->draw_entity(*shader, view, projection);
    }
}
