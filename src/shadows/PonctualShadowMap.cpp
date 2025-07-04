#include "shadows/PonctualShadowMap.h"
#include "Globals.h"

PonctualShadowMap::PonctualShadowMap(unsigned int width, unsigned int height)
    : width(width), height(height), lightPosition(0.0f, 0.0f, 0.0f) {
    init();
}

void PonctualShadowMap::init() {
    glGenFramebuffers(1, &shadowFBO);

    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32F,
                     width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Test si le framebuffer est complet
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PonctualShadowMap::render(const Scene & scene, Shader & shadowShader, const Light & pointLight) {
    lightPosition = pointLight.position;

    float nearPlane = 1.0f;
    float farPlane = pointLight.computeEffectiveRange(0.01f);

    Mat4 shadowProj = Mat4::perspective(90.0f, 1.0f, nearPlane, farPlane);

    std::vector<Mat4> shadowTransforms;
    Vec3 pos = pointLight.position;
    shadowTransforms.push_back(Mat4::lookAt(pos, pos + Vec3(1, 0, 0), Vec3(0, -1, 0))* shadowProj);
    shadowTransforms.push_back(Mat4::lookAt(pos, pos + Vec3(-1, 0, 0), Vec3(0, -1, 0))* shadowProj);
    shadowTransforms.push_back(Mat4::lookAt(pos, pos + Vec3(0, 1, 0), Vec3(0, 0, 1))* shadowProj);
    shadowTransforms.push_back(Mat4::lookAt(pos, pos + Vec3(0, -1, 0), Vec3(0, 0, -1))* shadowProj);
    shadowTransforms.push_back(Mat4::lookAt(pos, pos + Vec3(0, 0, 1), Vec3(0, -1, 0))* shadowProj);
    shadowTransforms.push_back(Mat4::lookAt(pos, pos + Vec3(0, 0, -1), Vec3(0, -1, 0))* shadowProj);

    glViewport(0, 0, width, height);
    shadowShader.use();

    shadowShader.set("lightPos", lightPosition);
    shadowShader.set("farPlane", farPlane);

    // Attacher toute la cubemap d'un coup
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);

    glClear(GL_DEPTH_BUFFER_BIT);

    // Passer toutes les matrices d'un coup
    for (int i = 0; i < 6; ++i) {
        shadowShader.set("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
    }

    // Rendu de toute la scène UNE SEULE FOIS (le geometry shader s'occupe des 6 faces)
    for (const auto & entity : scene.getEntities()) {
        std::cout<<entity->getTransform()<<std::endl;
        shadowShader.set("model", entity->getTransform(), false);
        entity->getMesh()->draw();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
}

void PonctualShadowMap::bindTexture(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
}