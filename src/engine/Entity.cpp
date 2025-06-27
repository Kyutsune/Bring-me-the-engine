#include "engine/Entity.h"

Entity::Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh, const std::string & filenameTextDiffuse,
               const std::string & filenameNormalMap)
    : transform(transform), mesh(std::move(mesh)) {
    if (!filenameTextDiffuse.empty() && !std::filesystem::exists(filenameTextDiffuse)) {
        std::cout << "Erreur lors du chargement de la texture : " << filenameTextDiffuse << " La couleur seule sera utilisée" << std::endl;
    } else if (!filenameTextDiffuse.empty()) {
        this->setTexture(std::make_shared<Texture>(filenameTextDiffuse));
    }

    if (!filenameNormalMap.empty() && !std::filesystem::exists(filenameNormalMap)) {
        std::cout << "Erreur lors du chargement de la normal map : " << filenameNormalMap << " La normal map ne sera pas utilisée" << std::endl;
    } else if (!filenameNormalMap.empty()) {
        normalMap = std::make_shared<Texture>(filenameNormalMap);
    }
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

    if (normalMap) {
        shader.set("useNormalMap", 1);
        shader.set("texture_normal", 1);
        normalMap->bind(1);
    } else {
        shader.set("useNormalMap", 0);
    }

    mesh->draw();
}

void Entity::setTexture(std::shared_ptr<Texture> tex) {
    texture = std::move(tex);
}