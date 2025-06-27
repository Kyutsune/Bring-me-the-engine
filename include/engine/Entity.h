#pragma once

#include "base/Shader.h"
#include "base/Vec.h"
#include "engine/Mesh.h"
#include <filesystem>
#include <iostream>

inline void updateCameraUniforms(Shader & shader, const Mat4 & model, const Mat4 & view, const Mat4 & projection) {
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

class Entity {
public:
    Entity() : transform(Mat4::identity()), mesh(nullptr) {}

    Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh, const std::string & filenameTextDiffuse = "",
        const std::string & filenameNormalMap = "");

    virtual ~Entity() = default;

    const Mat4 & getTransform() const { return transform; }
    void setTransform(const Mat4 & newTransform) { transform = newTransform; }

    void draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection);

    void setTexture(std::shared_ptr<Texture> tex);

private:
    Mat4 transform;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Texture> normalMap; 
    std::shared_ptr<Texture> specularMap; // Au cas ou, ce sera pour la suite

};
