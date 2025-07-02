#include "rendering/Renderer.h"
#include "Globals.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/stb/stb_image_write.h"

Renderer::Renderer(Shader * entityShader, Shader * lightShader, Shader * skyboxShader, Shader * boundingBoxShader, Shader * shadowShader)
    : entityShader(entityShader), lightShader(lightShader), skyboxShader(skyboxShader), boundingBoxShader(boundingBoxShader), shadowShader(shadowShader) {}

void Renderer::renderScene(const Scene & scene) {
    Mat4 view = scene.getCamera().getViewMatrix();
    Mat4 projection = scene.getCamera().getProjectionMatrix();

    if (scene.getSkybox() && skyboxShader) {
        renderSkybox(scene.getSkybox(), view, projection);
    }

    entityShader->use();
    // Transmettre la matrice lightSpace (récupérée depuis renderShadowMap)
    entityShader->set("lightSpaceMatrix", lightSpaceMatrix);

    // Activer et binder la shadow map à la bonne unité de texture
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    entityShader->set("shadowMap", 3);

    scene.getLightingManager().applyLightning(*entityShader, scene.getCamera().getPosition());
    renderEntities(scene, view, projection);

    renderLightEntities(scene, view, projection);
}

void Renderer::renderSkybox(const Skybox * skybox, const Mat4 & view, const Mat4 & projection) {
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

void Renderer::initShadowMap() {
    glGenFramebuffers(1, &shadowFBO);

    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, shadowMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderShadowMap(const Scene & scene, Shader & shadowShader) {
    const Light & dirLight = scene.getLightingManager().getFirstDirectional();
    Mat4 lightView = Mat4::lookAt(dirLight.position, dirLight.position + dirLight.direction, Vec3(0, 1, 0));
    Mat4 lightProjection = Mat4::orthographic(-20, 20, -20, 20, 0.1f, 100.0f);
    this->lightSpaceMatrix = lightProjection * lightView;

    shadowShader.use();
    shadowShader.set("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    const auto & entities = scene.getEntities();
    for (const auto & entity : entities) {
        std::cout << entity->getName() << " - " << entity->getTransform() << std::endl;
        shadowShader.set("model", entity->getTransform());
        entity->getMesh()->draw();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight); // Reset viewport to default size
}

void Renderer::renderFrame(const Scene & scene) {
    renderShadowMap(scene, *shadowShader);
    renderScene(scene);
}

void Renderer::debugSaveShadowMap(const std::string & filename) {
    glBindTexture(GL_TEXTURE_2D, shadowMap);

    std::vector<float> pixels(SHADOW_WIDTH * SHADOW_HEIGHT);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, pixels.data());

    // Convertir en image 8-bit pour visualisation
    std::vector<unsigned char> image(SHADOW_WIDTH * SHADOW_HEIGHT);
    for (int i = 0; i < SHADOW_WIDTH * SHADOW_HEIGHT; ++i) {
        image[i] = static_cast<unsigned char>(pixels[i] * 255.0f);
    }

    // Sauvegarde l'image avec stb_image_write
    stbi_write_png(filename.c_str(), SHADOW_WIDTH, SHADOW_HEIGHT, 1, image.data(), SHADOW_WIDTH);

    glBindTexture(GL_TEXTURE_2D, 0);
}