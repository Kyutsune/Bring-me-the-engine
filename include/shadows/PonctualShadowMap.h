#pragma once
#include "engine/Scene.h"
#include "math/Vec.h"
#include "rendering/Shader.h"

class PonctualShadowMap {
public:
    inline PonctualShadowMap() {
        width = height = 0;
        shadowFBO = depthCubemap = 0;
        lightPosition = Vec3(0.0f, 0.0f, 0.0f);
    };
    PonctualShadowMap(unsigned int width, unsigned int height);
    ~PonctualShadowMap() = default;

    void init();
    void render(const Scene & scene, Shader & shadowShader, const Light & pointLight);

    void bindTexture(GLenum textureUnit) const;
    const Vec3 & getLightPosition() const;


    // Section de déboggage
    void initDebugQuad();
    void debugRenderFace(int faceIndex);

private:
    unsigned int shadowFBO;
    unsigned int depthCubemap;
    unsigned int width, height;
    Vec3 lightPosition;

    // IDs pour quad fullscreen (debug)
    GLuint debugQuadVAO = 0;
    GLuint debugQuadVBO = 0;

    // Shader debug simple
    Shader * debugShader;
};