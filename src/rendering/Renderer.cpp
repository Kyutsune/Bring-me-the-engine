#include "rendering/Renderer.h"
#include "Globals.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/stb/stb_image_write.h"

Renderer::Renderer(Shader * entityShader, Shader * lightShader, Shader * skyboxShader, Shader * boundingBoxShader, Shader * shadowShaderDirectionnal, Shader * shadowShaderPonctual)
    : entityShader(entityShader), lightShader(lightShader), skyboxShader(skyboxShader), boundingBoxShader(boundingBoxShader), shadowShaderDirectionnal(shadowShaderDirectionnal), shadowShaderPonctual(shadowShaderPonctual) {
}

void Renderer::renderScene(const Scene & scene) {
    Mat4 view = scene.getCamera().getViewMatrix();
    Mat4 projection = scene.getCamera().getProjectionMatrix();
    const Light & dirLight = scene.getLightingManager().getFirstDirectional();

    if (scene.getSkybox() && skyboxShader) {
        renderSkybox(scene.getSkybox(), view, projection);
    }

    entityShader->use();

    // Si pas de lumière directionnelle, on ne rend pas les ombres liées à ce type de lumière
    if (dirLight.type == LightType::LIGHT_ERROR || dirLight.active) {
        entityShader->set("lightSpaceMatrix", shadowMapperDirectionnal.getLightSpaceMatrix(), false);
        entityShader->set("dirLightDirection", dirLight.direction);

        shadowMapperDirectionnal.bindTexture(GL_TEXTURE3);
        entityShader->set("shadowMap", 3);
        entityShader->set("useDirectionalShadow", true);
    } else {
        entityShader->set("useDirectionalShadow", false);
    }

    if (!shadowMapperPonctuals.empty()) {
        shadowMapperPonctuals[0].bindTexture(GL_TEXTURE4);
        entityShader->set("pointShadowMap", 4);
        entityShader->set("lightPos", scene.getLightingManager().getPonctualLight()[0].position);
        entityShader->set("farPlane", scene.getLightingManager().getPonctualLight()[0].computeEffectiveRange(0.01f));
        entityShader->set("pointLightIntensity", scene.getLightingManager().getPonctualLight()[0].intensity);
        entityShader->set("usePointShadow", true);
    } else {
        entityShader->set("usePointShadow", false);
    }

    scene.getLightingManager().applyLightning(*entityShader, scene.getCamera().getPosition());
    renderEntities(scene, view, projection);

    renderLightEntities(scene, view, projection);
}

void Renderer::renderSkybox(const Skybox * skybox, const Mat4 & view, const Mat4 & projection) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->textureID);
    skybox->draw(*skyboxShader, view, projection);
}

void Renderer::renderEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection) {
    const auto & frustum = scene.getFrustum();
    const auto & entities = scene.getEntities();

    for (const auto & entity : entities) {
        if (frustum.isBoxInFrustum(entity->getTransformedBoundingBox())) {
            entity->draw_entity(*entityShader, view, projection);
        }
        // else if(!frustum.isBoxInFrustum(entity->getTransformedBoundingBox()) && entity->getName()=="Cube_tout_bleu"){
        //     std::cout<< "Entité " << entity->getName() << " Pas dans le frustum." << std::endl;
        // }
    }
}

void Renderer::renderLightEntities(const Scene & scene, const Mat4 & view, const Mat4 & projection) {
    const auto & lights = scene.getLightingManager().getLights();
    const auto & lightEntities = scene.getLightEntities();

    for (size_t i = 0; i < lightEntities.size(); ++i) {
        if (lights[i].type != LightType::LIGHT_POINT)
            continue;

        scene.getLightingManager().applyPosLights(*lightShader);
        lightEntities[i]->draw_entity(*lightShader, view, projection);
    }
}

void Renderer::renderPonctualShadowMaps(const Scene & scene) {
    const auto & pointLights = scene.getLightingManager().getPonctualLight();

    // Redimensionner si nécessaire
    if (shadowMapperPonctuals.size() < pointLights.size()) {
        size_t oldSize = shadowMapperPonctuals.size();
        shadowMapperPonctuals.resize(pointLights.size());

        // Initialiser les nouvelles shadow maps
        for (size_t i = oldSize; i < pointLights.size(); ++i) {
            shadowMapperPonctuals[i] = PonctualShadowMap(1024, 1024);
        }
    }

    // Rendu de chaque shadow map
    for (size_t i = 0; i < pointLights.size(); ++i) {
        if (!pointLights[i].active)
            continue;
        shadowMapperPonctuals[i].render(scene, *shadowShaderPonctual, pointLights[i]);
    }
}

void Renderer::renderFrame(const Scene & scene) {
    shadowMapperDirectionnal.render(scene, *shadowShaderDirectionnal);
    renderPonctualShadowMaps(scene);
    renderScene(scene);
}
