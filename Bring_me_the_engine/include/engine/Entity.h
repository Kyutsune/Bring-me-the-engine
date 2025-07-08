#pragma once

#include "Material.h"
#include "Mesh.h"
#include "math/PlaneBoundingVolume.h"
#include "math/Vec.h"
#include "rendering/Shader.h"
#include <filesystem>
#include <iostream>

inline void updateCameraUniforms(Shader & shader, const Mat4 & model, const Mat4 & view, const Mat4 & projection) {
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

class Entity {
public:
    Entity() : m_transform(Mat4::identity()), m_mesh(nullptr) {}

    Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh,
           const std::string & filenameTextDiffuse = "",
           const std::string & filenameNormalMap = "",
           const std::string & filenameSpecularMap = "",
           const std::string & name = "");

    virtual ~Entity() = default;

    const std::string & getName() const { return m_entity_name; }
    const Mat4 & getTransform() const { return m_transform; }
    Mat4& getTransform() { return m_transform; }
    void setTransform(const Mat4 & newTransform) { m_transform = newTransform; }
    inline void setPosition(const Vec3 & newPosition) { m_transform.translate(newPosition); }

    void draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection);

    AABB getBoundingBox() { return m_boundingBox; }
    AABB getTransformedBoundingBox() const;

    Material & getMaterial() { return m_material; }
    const Material & getMaterial() const { return m_material; }

    inline const std::shared_ptr<Mesh> & getMesh() const { return m_mesh; }

private:
    std::string m_entity_name;
    Mat4 m_transform;
    std::shared_ptr<Mesh> m_mesh;
    AABB m_boundingBox;

    Material m_material;
};
