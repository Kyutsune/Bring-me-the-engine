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

    Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh, const std::string & filenameText = "")
        : transform(transform), mesh(std::move(mesh)) {
        if(!std::filesystem::exists(filenameText) && !filenameText.empty()){
            std::cout << "Erreur lors du chargement de la texture : " << filenameText << " La couleur seule sera utilisée" << std::endl;
            return;
        }
        if (!filenameText.empty())
            this->setTexture(std::make_shared<Texture>(filenameText));
    }

    virtual ~Entity() = default;

    const Mat4 & getTransform() const { return transform; }
    void setTransform(const Mat4 & newTransform) { transform = newTransform; }

    void draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection) {
        updateCameraUniforms(shader, transform, view, projection);

        if (texture) {
            shader.set("useTexture", 1);
            shader.set("texture_diffuse", 0);
            texture->bind();
        } else {
            shader.set("useTexture", 0);
        }

        mesh->draw();
    }

    void setTexture(std::shared_ptr<Texture> tex) {
        texture = std::move(tex);
    }

private:
    Mat4 transform;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Texture> texture;

};
