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

    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    // Pas besoin de lier ici la texture complète, on fera face par face dans render()
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

    Mat4 shadowProj = Mat4::perspective(M_PI / 2.0f, 1.0f, nearPlane, farPlane);

    Vec3 pos = pointLight.position;
    Mat4 shadowViews[6] = {
        Mat4::lookAt(pos, pos + Vec3(1, 0, 0), Vec3(0, -1, 0)),
        Mat4::lookAt(pos, pos + Vec3(-1, 0, 0), Vec3(0, -1, 0)),
        Mat4::lookAt(pos, pos + Vec3(0, 1, 0), Vec3(0, 0, 1)),
        Mat4::lookAt(pos, pos + Vec3(0, -1, 0), Vec3(0, 0, -1)),
        Mat4::lookAt(pos, pos + Vec3(0, 0, 1), Vec3(0, -1, 0)),
        Mat4::lookAt(pos, pos + Vec3(0, 0, -1), Vec3(0, -1, 0))};

    glViewport(0, 0, width, height);
    shadowShader.use();

    shadowShader.set("lightPos", lightPosition);
    shadowShader.set("farPlane", farPlane);

    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    for (int face = 0; face < 6; ++face) {
        // Attacher la bonne face de la cubemap
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
                               depthCubemap, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Framebuffer incomplete for face " << face << std::endl;
            continue;
        }

        glClear(GL_DEPTH_BUFFER_BIT);

        Mat4 shadowMatrix = shadowViews[face] * shadowProj;

        Vec4 testPoint = shadowMatrix * Vec4(lightPosition, 1.0f);
        Vec3 ndc = Vec3(testPoint.x / testPoint.w, testPoint.y / testPoint.w, testPoint.z / testPoint.w);

        shadowShader.set("shadowMatrix", shadowMatrix);

        for (const auto & entity : scene.getEntities()) {
            shadowShader.set("model", entity->getTransform(), false);
            entity->getMesh()->draw();
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
}

void PonctualShadowMap::bindTexture(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
}