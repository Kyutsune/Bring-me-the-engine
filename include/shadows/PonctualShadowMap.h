#pragma once
#include "engine/Scene.h"
#include "math/Vec.h"
#include "rendering/Shader.h"

class PonctualShadowMap {
public:
    inline PonctualShadowMap() {
        m_width = m_height = 0;
        m_shadowFBO = m_depthCubemap = 0;
        m_lightPosition = Vec3(0.0f, 0.0f, 0.0f);
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
    unsigned int m_shadowFBO;
    unsigned int m_depthCubemap;
    unsigned int m_width, m_height;
    Vec3 m_lightPosition;

    // IDs pour quad fullscreen (debug)
    GLuint m_debugQuadVAO = 0;
    GLuint m_debugQuadVBO = 0;

    // Shader debug simple
    Shader * m_debugShader = nullptr;
};