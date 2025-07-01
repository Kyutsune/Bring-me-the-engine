#pragma once

#include "rendering/Shader.h"
#include "math/Vec.h"
#include "Mesh.h"
#include "Material.h"
#include "math/PlaneBoundingVolume.h"
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

Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh,
       const std::string & filenameTextDiffuse = "",
       const std::string & filenameNormalMap = "",
       const std::string & filenameSpecularMap = "",
       const std::string & name = "");

    virtual ~Entity() = default;

    const std::string & getName() const { return entity_name; }
    const Mat4 & getTransform() const { return transform; }
    void setTransform(const Mat4 & newTransform) { transform = newTransform; }

    void draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection);

    AABB getBoundingBox() { return boundingBox; }
    AABB getTransformedBoundingBox() const;

private:
    std::string entity_name;
    Mat4 transform;
    std::shared_ptr<Mesh> mesh;
    AABB boundingBox;

    Material material;
};
