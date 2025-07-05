#pragma once

#include "engine/Scene.h"
#include "rendering/Renderer.h"
#include "engine/Light.h"

class ShadowMapBase {
public:
    virtual void render(const Scene & scene, Shader & shader, const Light * light) = 0;
    virtual void bindTexture(GLenum textureUnit) const = 0;
    virtual void applyToShader(Shader & shader, int textureSlot) const = 0;
    virtual ~ShadowMapBase() = default;
};