#include "rendering/Renderer.h"

Renderer::Renderer(Shader* entityShader, Shader* lightShader, Shader* skyboxShader, Shader* boundingBoxShader)
    : entityShader(entityShader), lightShader(lightShader), skyboxShader(skyboxShader), boundingBoxShader(boundingBoxShader) {}

void Renderer::renderScene(const Scene& scene) {
    Mat4 view = scene.getCamera().getViewMatrix();
    Mat4 projection = scene.getCamera().getProjectionMatrix();

    if (scene.getSkybox() && skyboxShader) {
        renderSkybox(scene.getSkybox(), view, projection);
    }

    scene.getLightingManager().applyLightning(*entityShader, scene.getCamera().getPosition());
    renderEntities(scene, view, projection);

    renderLightEntities(scene, view, projection);
}

void Renderer::renderSkybox(const Skybox* skybox, const Mat4& view, const Mat4& projection) {
    skybox->draw(*skyboxShader, view, projection);
}

void Renderer::renderEntities(const Scene& scene, const Mat4& view, const Mat4& projection) {
    const auto& frustum = scene.getFrustum();
    const auto& entities = scene.getEntities();

    for (const auto& entity : entities) {
        if (frustum.isBoxInFrustum(entity->getTransformedBoundingBox())) {
            entity->draw_entity(*entityShader, view, projection);
        }
        // else if(!frustum.isBoxInFrustum(entity->getTransformedBoundingBox()) && entity->getName()=="Cube_tout_bleu"){
        //     std::cout<< "Entité " << entity->getName() << " Pas dans le frustum." << std::endl;
        // }
    }
}

void Renderer::renderLightEntities(const Scene& scene, const Mat4& view, const Mat4& projection) {
    const auto& lights = scene.getLightingManager().getLights();
    const auto& lightEntities = scene.getLightEntities();

    for (size_t i = 0; i < lightEntities.size(); ++i) {
        if (lights[i].type != LightType::LIGHT_POINT)
            continue;

        scene.getLightingManager().applyPosLights(*lightShader);
        lightEntities[i]->draw_entity(*lightShader, view, projection);
    }
}
