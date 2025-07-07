#pragma once

#include "math/Vec.h"
#include "engine/Scene.h"
#include "rendering/Shader.h"

class DirectionalShadowMap {
public:
    DirectionalShadowMap(unsigned int width = 2048, unsigned int height = 2048);
    ~DirectionalShadowMap();

    void init();
    void render(const Scene& scene, Shader& shadowShader);
    void bindTexture(GLenum textureUnit) const;
    const Mat4& getLightSpaceMatrix() const { return m_lightSpaceMatrix; }

private:
    unsigned int m_shadowFBO;
    unsigned int m_shadowMap;
    unsigned int m_width, m_height;

    Mat4 m_lightSpaceMatrix;
};
