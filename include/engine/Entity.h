#pragma once

#include "base/Vec.h"
#include "engine/Mesh.h"
#include "base/Shader.h"
#include <memory>
#include <vector>

inline void updateCameraUniforms(Shader & shader, const Mat4 & model, const Mat4 & view, const Mat4 & projection) {
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

class Entity {
public:
    Entity() : transform(Mat4::identity()), mesh(nullptr) {}

    Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh)
        : transform(transform), mesh(std::move(mesh)) {}

    virtual ~Entity() = default;

    const Mat4 & getTransform() const { return transform; }
    void setTransform(const Mat4 & newTransform) { transform = newTransform; }

    void draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection) {
        updateCameraUniforms(shader, transform, view, projection);
        mesh->draw();
    }

private:
    Mat4 transform;
    std::shared_ptr<Mesh> mesh;
};


