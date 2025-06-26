#include "engine/Entity.h"

Entity::Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh, const std::string & filenameText)
    : transform(transform), mesh(std::move(mesh)) {
    if (!std::filesystem::exists(filenameText) && !filenameText.empty()) {
        std::cout << "Erreur lors du chargement de la texture : " << filenameText << " La couleur seule sera utilisée" << std::endl;
        return;
    }
    if (!filenameText.empty())
        this->setTexture(std::make_shared<Texture>(filenameText));
}

void Entity::draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection) {
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

void Entity::setTexture(std::shared_ptr<Texture> tex) {
    texture = std::move(tex);
}