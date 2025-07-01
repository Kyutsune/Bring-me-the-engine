#include "engine/Scene.h"
#include "base/Shader.h"
#include "base/Vec.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Scene::Scene(Shader * shader, Shader * lightShader, Shader * skyboxShader = nullptr, Shader * bboxShader = nullptr) : shader(shader), lightShader(lightShader), skyboxShader(skyboxShader), bboxShader(bboxShader), view(Mat4::identity()), projection(Mat4::identity()) {
    init();
}

void Scene::init() {
    this->camera = Camera(
        Vec3(-5.68114, 0.024997, -0.912596), // position à l'initialisation
        Vec3(0.025365, 0.0263991, -3.00793), // le point ciblé
        Vec3(0, 1, 0),                       // up
        45.0f,                               // FOV
        1600.0f / 800.0f,                    // aspect ratio
        0.1f, 100.0f);                       // near et far planes

    this->view = camera.getViewMatrix();
    this->projection = camera.getProjectionMatrix();
    this->initObjects();

    lightingManager.setupLightingOnScene();

    lightingManager.addLight({
        LightType::LIGHT_POINT, // type 0=ponctuelle, 1= directionnelle
        Vec3(-3, 0, -3),        // position
        Vec3(0, -1, 0),         // direction vers le bas
        Color(255, 255, 255),   // couleur blanche
        0.3f,                   // intensité
        0.5f, 0.7f, 1.8f        // Consantes d'atténuation (constant, linear, quadratic)
    });
    // lightingManager.addLight({
    //     LightType::LIGHT_DIRECTIONAL,
    //     Vec3(3, 2, -3),
    //     Vec3(0, -1, 0),
    //     Color(255, 255, 255),
    //     0.1f,
    //     0.5f, 0.7f, 1.8f
    // });

    std::shared_ptr<Mesh> lightMesh = createSphere<std::shared_ptr<Mesh>>(0.5f, 36, 18, Color::white());
    for (const Light & light : lightingManager.getLights()) {
        Mat4 lightTransform = Mat4::Scale(Vec3(0.1f, 0.1f, 0.1f)) * Mat4::Translation(light.position);
        std::shared_ptr<Entity> lightEntity = std::make_shared<Entity>(lightTransform, lightMesh);
        lightEntities.push_back(lightEntity);
    }

    if (skyboxShader) {
        std::vector<std::string> faces = {
            "../assets/cubemap/Nuit_bleue/right.jpg",
            "../assets/cubemap/Nuit_bleue/left.jpg",
            "../assets/cubemap/Nuit_bleue/bottom.jpg",
            "../assets/cubemap/Nuit_bleue/top.jpg",
            "../assets/cubemap/Nuit_bleue/front.jpg",
            "../assets/cubemap/Nuit_bleue/back.jpg"};
        skybox = std::make_unique<Skybox>(faces);
    }
}

void Scene::initObjects() {
    std::shared_ptr<Mesh> cubeMesh = createCube<std::shared_ptr<Mesh>>(Color::cyan());
    Mat4 t;
    auto cube_qui_tourne = std::make_shared<Entity>(t, cubeMesh, "../assets/materiaux/cuivre_diffus.jpg", "../assets/materiaux/cuivre_normal.jpg", "../assets/materiaux/cuivre_specular.jpg", "Cube_qui_tourne");
    cube_qui_tourne->getBoundingBox().setupBBoxBuffers();
    entities.push_back(cube_qui_tourne);

    std::shared_ptr<Mesh> cubeMesh2 = createCube<std::shared_ptr<Mesh>>(Color::rose());
    Mat4 t2 = Mat4::Translation(Vec3(1, 0, -5));
    auto Cube_tout_bleu = std::make_shared<Entity>(t2, cubeMesh2, "", "", "", "Cube_tout_bleu");
    Cube_tout_bleu->getBoundingBox().setupBBoxBuffers();
    entities.push_back(Cube_tout_bleu);

    std::shared_ptr<Mesh> cubeMesh3 = createCube<std::shared_ptr<Mesh>>();
    Mat4 t4 = Mat4::Translation(Vec3(3, 0, -3));
    auto Cube_plein_de_texture = std::make_shared<Entity>(t4, cubeMesh3, "../assets/materiaux/bois.jpg", "", "", "Cube_plein_de_texture");
    Cube_plein_de_texture->getBoundingBox().setupBBoxBuffers();
    entities.push_back(Cube_plein_de_texture);

    // std::shared_ptr<Mesh> floorMesh = createFloor<std::shared_ptr<Mesh>>(25.f, -1.f);
    // Mat4 t3;
    // auto sol_beton = std::make_shared<Entity>(t3, floorMesh, "../assets/Mud.jpg", "../assets/Mud_normal.jpg");
    // entities.push_back(sol_beton);

    std::shared_ptr<Mesh> floorMesh = createFloor<std::shared_ptr<Mesh>>(25.f, -1.f);
    Mat4 t3;
    // auto sol_beton = std::make_shared<Entity>(t3, floorMesh, "../assets/sol/sol_cobble/sol_cobble.jpg", "../assets/sol/sol_cobble/sol_cobble_normal.jpg", "../assets/sol/sol_cobble/sol_cobble_specular.jpg");
    auto sol_beton = std::make_shared<Entity>(t3, floorMesh, "../assets/sol/brique_recyclee/brique_recyclee_diffuse.jpg", "../assets/sol/brique_recyclee/brique_recyclee_normal.jpg", "", "Sol_beton");
    sol_beton->getBoundingBox().setupBBoxBuffers();
    entities.push_back(sol_beton);
}

void Scene::update() {

    view = camera.getViewMatrix();
    projection = camera.getProjectionMatrix();

    if (skybox && skyboxShader) {
        skybox->draw(*skyboxShader, view, projection);
    }

    frustum = frustum.updateFromCamera(camera);

    lightingManager.applyLightning(*shader, camera.getPosition());

    float angle = glfwGetTime();

    entities[0]->setTransform(Mat4::Translation(Vec3(0, 0, -1.f)) * Mat4::rotateY(angle) * Mat4::rotateZ(angle));

    // Dessin de chaque entité avec sa propre matrice de transformation si elle est dans le frustum
    for (const std::shared_ptr<Entity> & entity : entities) {
        if (frustum.isBoxInFrustum(entity->getTransformedBoundingBox())) {
            entity->draw_entity(*shader, view, projection);
        }
        // else if (!frustum.isBoxInFrustum(entity->getTransformedBoundingBox()) && entity->getName() == "Cube_tout_bleu") {
        //     std::cout << "L'entité " << entity->getName() << " n'est pas dans le frustum." << std::endl;
        // }
    }

    for (size_t i = 0; i < lightEntities.size(); ++i) {
        const Light & light = lightingManager.getLights()[i];

        // On ne dessine que les lumières ponctuelles
        if (light.type != LightType::LIGHT_POINT)
            continue;

        lightingManager.applyPosLights(*lightShader);
        lightEntities[i]->draw_entity(*lightShader, view, projection);
    }
}
