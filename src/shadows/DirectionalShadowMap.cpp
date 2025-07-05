#include "shadows/DirectionalShadowMap.h"
#include "Globals.h"
#include <glad/glad.h>
#include <iostream>

DirectionalShadowMap::DirectionalShadowMap(unsigned int width, unsigned int height)
    : width(width), height(height), shadowFBO(0), shadowMap(0) {}

DirectionalShadowMap::~DirectionalShadowMap() {
    if (shadowMap) glDeleteTextures(1, &shadowMap);
    if (shadowFBO) glDeleteFramebuffers(1, &shadowFBO);
}

void DirectionalShadowMap::init() {
    glGenFramebuffers(1, &shadowFBO);

    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
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
        std::cerr << "Erreur: Shadow framebuffer non complet !" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DirectionalShadowMap::render(const Scene& scene, Shader& shadowShader) {
    const Light& dirLight = scene.getLightingManager().getFirstDirectional();
    if (dirLight.getType() == LightType::LIGHT_ERROR || !dirLight.isActive())
        return;

    Vec3 lightTarget = dirLight.getPosition() + dirLight.getDirection();
    Vec3 up = std::abs(dirLight.getDirection().z) > 0.9f ? Vec3(0, 1, 0) : Vec3(0, 0, 1);
    Mat4 lightView = Mat4::lookAt(dirLight.getPosition(), lightTarget, up);

    Camera lightCam(dirLight.getPosition(), lightTarget, up, 90.0f, 1.0f, 1.0f, 10.0f);
    Frustum lightFrustum = Frustum().updateFromCamera(lightCam);
    AABB boundingBox = lightFrustum.computeBoundingBox();

    Mat4 lightProjection = Mat4::orthographic(
        boundingBox.min.x, boundingBox.max.x,
        boundingBox.min.y, boundingBox.max.y,
        boundingBox.min.z, boundingBox.max.z);

    lightSpaceMatrix = lightView * lightProjection;

    shadowShader.use();
    shadowShader.set("lightSpaceMatrix", lightSpaceMatrix, false);

    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (const auto& entity : scene.getEntities()) {
        if (entity->getName() == "Sol_beton") continue;

        shadowShader.set("model", entity->getTransform(), false);
        entity->getMesh()->draw();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
}
    
void DirectionalShadowMap::bindTexture(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}
