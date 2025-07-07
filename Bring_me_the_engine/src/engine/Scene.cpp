#include "engine/Scene.h"
#include "math/Vec.h"
#include "rendering/Shader.h"
#include "system/PathResolver.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
    initObjects();

    m_lightingManager.setupLightingOnScene();

    m_lightingManager.addLight({true,
                                    LightType::LIGHT_POINT,
                                    Vec3(3, 1, -1),
                                    Vec3(0, -1, 0),
                                    Color(255, 255, 255),
                                    1.f,
                                    1.0f, 0.7f, 1.8f});

    m_lightingManager.addLight({false,
                                    LightType::LIGHT_DIRECTIONAL,
                                    Vec3(0, 10, 0),
                                    Vec3(1, -1, 0),
                                    Color(255, 255, 255),
                                    0.06f,
                                    0.5f, 0.7f, 1.8f});

    m_lightingManager.addLight({true,
                                    LightType::LIGHT_POINT,
                                    Vec3(-1, 1, -3),
                                    Vec3(0, -1, 0),
                                    Color(255, 255, 255),
                                    0.7f,
                                    1.0f, 0.7f, 1.8f});

    std::shared_ptr<Mesh> lightMesh = createSphere<std::shared_ptr<Mesh>>(0.5f, 36, 18, Color::white());
    for (const Light & light : m_lightingManager.getLights()) {
        Mat4 lightTransform = Mat4::Scale(Vec3(0.1f, 0.1f, 0.1f)) * Mat4::Translation(light.getPosition());
        std::shared_ptr<Entity> lightEntity = std::make_shared<Entity>(lightTransform, lightMesh);
        m_lightEntities.push_back(lightEntity);
    }

    std::vector<std::string> faces = {
        PathResolver::getResourcePath("assets/cubemap/Nuit_bleue/right.jpg"),
        PathResolver::getResourcePath("assets/cubemap/Nuit_bleue/left.jpg"),
        PathResolver::getResourcePath("assets/cubemap/Nuit_bleue/bottom.jpg"),
        PathResolver::getResourcePath("assets/cubemap/Nuit_bleue/top.jpg"),
        PathResolver::getResourcePath("assets/cubemap/Nuit_bleue/front.jpg"),
        PathResolver::getResourcePath("assets/cubemap/Nuit_bleue/back.jpg")};
    m_skybox = std::make_unique<Skybox>(faces);
}

void Scene::initObjects() {
    std::shared_ptr<Mesh> cubeMesh = createCube<std::shared_ptr<Mesh>>(Color::cyan());
    std::shared_ptr<Entity> cube_qui_tourne = std::make_shared<Entity>(Mat4::identity(), cubeMesh,
                                                                       PathResolver::getResourcePath("assets/materiaux/cuivre_diffus.jpg"),
                                                                       PathResolver::getResourcePath("assets/materiaux/cuivre_normal.jpg"),
                                                                       PathResolver::getResourcePath("assets/materiaux/cuivre_specular.jpg"),
                                                                       "Cube_qui_tourne");
    cube_qui_tourne->getBoundingBox().setupBBoxBuffers();
    m_entities.push_back(cube_qui_tourne);

    std::shared_ptr<Mesh> cubeMesh2 = createCube<std::shared_ptr<Mesh>>(Color::rose());
    Mat4 t2 = Mat4::Translation(Vec3(1, 0, -5));
    std::shared_ptr<Entity> Cube_tout_bleu = std::make_shared<Entity>(t2, cubeMesh2,
                                                                      "",
                                                                      "",
                                                                      "",
                                                                      "Cube_tout_bleu");
    Cube_tout_bleu->getBoundingBox().setupBBoxBuffers();
    m_entities.push_back(Cube_tout_bleu);

    std::shared_ptr<Mesh> cubeMesh3 = createCube<std::shared_ptr<Mesh>>();
    Mat4 t4 = Mat4::Translation(Vec3(3, 0, -3));
    std::shared_ptr<Entity> Cube_plein_de_texture = std::make_shared<Entity>(t4, cubeMesh3,
                                                                             PathResolver::getResourcePath("assets/materiaux/bois.jpg"),
                                                                             "",
                                                                             "",
                                                                             "Cube_plein_de_texture");
    Cube_plein_de_texture->getBoundingBox().setupBBoxBuffers();
    m_entities.push_back(Cube_plein_de_texture);

    // std::shared_ptr<Mesh> floorMesh = createFloor<std::shared_ptr<Mesh>>(25.f, -1.f);
    // Mat4 t3;
    // auto sol_beton = std::make_shared<Entity>(t3, floorMesh, "../assets/Mud.jpg", "../assets/Mud_normal.jpg");
    // entities.push_back(sol_beton);

    std::shared_ptr<Mesh> floorMesh = createFloor<std::shared_ptr<Mesh>>(25.f, -1.f);
    // auto sol_beton = std::make_shared<Entity>(t3, floorMesh, "../assets/sol/sol_cobble/sol_cobble.jpg", "../assets/sol/sol_cobble/sol_cobble_normal.jpg", "../assets/sol/sol_cobble/sol_cobble_specular.jpg");
    std::shared_ptr<Entity> sol_beton = std::make_shared<Entity>(Mat4::identity(), floorMesh,
                                                                 PathResolver::getResourcePath("assets/sol/brique_recyclee/brique_recyclee_diffuse.jpg"),
                                                                 PathResolver::getResourcePath("assets/sol/brique_recyclee/brique_recyclee_normal.jpg"),
                                                                 "",
                                                                 "Sol_beton");
    sol_beton->getBoundingBox().setupBBoxBuffers();
    m_entities.push_back(sol_beton);

    std::shared_ptr<Mesh> sphereMesh = createSphere<std::shared_ptr<Mesh>>(0.5f, 36, 18, Color::red());
    Mat4 t5 = Mat4::Translation(Vec3(-2, 0, -5));
    std::shared_ptr<Entity> sphere = std::make_shared<Entity>(t5, sphereMesh,
                                                              PathResolver::getResourcePath("assets/materiaux/petit_caillou/petit_caillou_diffus.jpg"),
                                                              PathResolver::getResourcePath("assets/materiaux/petit_caillou/petit_caillou_normal.jpg"),
                                                              PathResolver::getResourcePath("assets/sol/sol_cobble/sol_cobble_specular.jpg"),
                                                              "Sphere_toute_texturee");
    sphere->getBoundingBox().setupBBoxBuffers();
    m_entities.push_back(sphere);
}

void Scene::update() {
    // Mise à jour des matrices de vue et de projection
    m_view = m_camera.getViewMatrix();
    m_projection = m_camera.getProjectionMatrix();

    // Mise à jour du frustum pour le culling
    m_frustum = m_frustum.updateFromCamera(m_camera);

    float angle = glfwGetTime();
    if (!m_entities.empty()) {
        m_entities[0]->setTransform(
            Mat4::Translation(Vec3(0, 0, -1.f)) *
            Mat4::rotateY(angle) *
            Mat4::rotateZ(angle));
    }
}