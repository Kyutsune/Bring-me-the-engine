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

    // Si pas de lumière directionnelle, on ne rend pas les ombres liées à ce type de lumière
    const Light & dirLight = scene.getLightingManager().getFirstDirectional();
    if (dirLight.type != LightType::LIGHT_ERROR) {
        entityShader->set("lightSpaceMatrix", lightSpaceMatrix, false);
        entityShader->set("dirLightDirection", dirLight.direction);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, shadowMap);
        entityShader->set("shadowMap", 3);
        entityShader->set("useDirectionalShadow", true);
    } else {
        entityShader->set("useDirectionalShadow", false);
    }

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

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Erreur: Shadow framebuffer non complete !" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderShadowMap(const Scene & scene, Shader & shadowShader) {
    const Light & dirLight = scene.getLightingManager().getFirstDirectional();

    if (dirLight.type == LightType::LIGHT_ERROR) {
        return;
    }

    Vec3 lightTarget = dirLight.position + dirLight.direction;
    Vec3 up = std::abs(dirLight.direction.z) > 0.9f ? Vec3(0, 1, 0) : Vec3(0, 0, 1);
    Mat4 lightView = Mat4::lookAt(dirLight.position, lightTarget, up);
    Mat4 lightProjection = Mat4::orthographic(-20, 20, -20, 20, 1.0f, 100.0f);
    this->lightSpaceMatrix = lightView * lightProjection;

    shadowShader.use();
    shadowShader.set("lightSpaceMatrix", lightSpaceMatrix, false);

    glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    const auto & entities = scene.getEntities();
    for (const auto & entity : entities) {
        if (entity->getName() == "Sol_beton")
            continue;
        shadowShader.set("model", entity->getTransform(), false);
        entity->getMesh()->draw();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
}

void Renderer::renderFrame(const Scene & scene) {
    renderShadowMap(scene, *shadowShader);

    // Au besoin on peut afficher la shadow map pour debug dans l'écran,
    // ceci nécessite de ne pas dessiner la scène ensuite évidemment sinon ce qu'on à
    //  dessiner en premier est écrasé
    // renderShadowMapOnQuad();

    renderScene(scene);
}

void Renderer::debugSaveShadowMap(const std::string & filename) {
    std::vector<float> pixels(SHADOW_WIDTH * SHADOW_HEIGHT);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, pixels.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    std::vector<unsigned char> image(SHADOW_WIDTH * SHADOW_HEIGHT);
    for (int i = 0; i < SHADOW_WIDTH * SHADOW_HEIGHT; ++i) {
        image[i] = static_cast<unsigned char>(pixels[i] * 255.0f);
    }

    stbi_write_png(filename.c_str(), SHADOW_WIDTH, SHADOW_HEIGHT, 1, image.data(), SHADOW_WIDTH);
}

void Renderer::renderShadowMapOnQuad() {
    // Afficher la shadow map dans un quad pour debug
    quadDebugShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowMap);

    static GLuint quadVAO = 0;
    static GLuint quadVBO;
    if (quadVAO == 0) {
        float quadVertices[] = {
            // positions   // texCoords
            -1.0f,
            1.0f,
            0.0f,
            1.0f,
            -1.0f,
            -1.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            -1.0f,
            1.0f,
            0.0f,
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}