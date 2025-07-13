#pragma once

#include "Material.h"
#include "Mesh.h"
#include "math/PlaneBoundingVolume.h"
#include "math/Quat.h"
#include "math/Vec.h"
#include "rendering/Shader.h"
#include <filesystem>
#include <iostream>

// TODO: foutre de l'ordre dans ce joyeux bordel

inline void updateCameraUniforms(Shader & shader, const Mat4 & model, const Mat4 & view, const Mat4 & projection) {
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity() : m_transform(Mat4::identity()), m_mesh(nullptr) {}

    Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh,
           const std::string & filenameTextDiffuse = "",
           const std::string & filenameNormalMap = "",
           const std::string & filenameSpecularMap = "",
           const std::string & name = "");

    Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh,
           std::shared_ptr<Material> material,
           const std::string & name = "");

    virtual ~Entity() = default;

    const std::string & getName() const { return m_entity_name; }
    const Mat4 & getTransform() const { return m_transform; }
    Mat4 & getTransform() { return m_transform; }
    void setTransform(const Mat4 & newTransform);

    void draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection);

    AABB getBoundingBox() { return m_boundingBox; }
    AABB getTransformedBoundingBox() const;

    Material & getMaterial() { return m_material; }
    const Material & getMaterial() const { return m_material; }

    inline const std::shared_ptr<Mesh> & getMesh() const { return m_mesh; }

    inline bool isVisible() const { return visible; }
    inline void setVisible(bool v) { visible = v; }

    inline void setPosition(const Vec3 & pos) {
        m_transform.setTranslation(pos);
        m_position = pos;
        updateTransform();
    }

    inline void setScale(const Vec3 & scale) {
        m_scale = scale;
        updateTransform();
    }

    inline Vec3 getScale() const { return m_scale; }

    inline void setRotation(const Quat & rot) {
        m_rotation = rot.normalized();
        updateTransform();
    }

    inline Vec3 getPosition() const { return m_position; }
    inline Quat getRotation() const { return m_rotation; }

    void updateTransform();

private:
    std::string m_entity_name;
    std::shared_ptr<Mesh> m_mesh;
    AABB m_boundingBox;

    Vec3 m_position = Vec3(0.0f);
    Quat m_rotation = Quat::identity();
    Vec3 m_scale = Vec3(1.0f, 1.0f, 1.0f);
    Mat4 m_transform;

    Material m_material;
    bool visible = false;
};
