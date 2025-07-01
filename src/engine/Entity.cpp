#include "engine/Entity.h"

Entity::Entity(const Mat4 & transform, std::shared_ptr<Mesh> mesh,
               const std::string & filenameTextDiffuse,
               const std::string & filenameNormalMap,
               const std::string & filenameSpecularMap,
               const std::string & name)
    : transform(transform), mesh(std::move(mesh)) {

    if (!filenameTextDiffuse.empty() && !std::filesystem::exists(filenameTextDiffuse)) {
        std::cout << "Erreur lors du chargement de la texture : " << filenameTextDiffuse << " La couleur seule sera utilisée" << std::endl;
    } else if (!filenameTextDiffuse.empty()) {
        material.diffuse_text = std::make_shared<Texture>(filenameTextDiffuse);
    }

    if (!filenameNormalMap.empty() && !std::filesystem::exists(filenameNormalMap)) {
        std::cout << "Erreur lors du chargement de la normal map : " << filenameNormalMap << " La normal map ne sera pas utilisée" << std::endl;
    } else if (!filenameNormalMap.empty()) {
        material.normal_map = std::make_shared<Texture>(filenameNormalMap);
    }

    if (!filenameSpecularMap.empty() && !std::filesystem::exists(filenameSpecularMap)) {
        std::cout << "Erreur lors du chargement de la specular map : " << filenameSpecularMap << " La specular map ne sera pas utilisée" << std::endl;
    } else if (!filenameSpecularMap.empty()) {
        material.specular_map = std::make_shared<Texture>(filenameSpecularMap);
    }

    if (this->mesh) {
        boundingBox = this->mesh->getBoundingBox();
    }
    entity_name = name.empty() ? "Unnamed Entity" : name;
}

void Entity::draw_entity(Shader & shader, const Mat4 & view, const Mat4 & projection) {
    updateCameraUniforms(shader, transform, view, projection);

    if (material.diffuse_text && material.useDiffuse) {
        shader.set("useTexture", 1);
        shader.set("texture_diffuse", 0);
        material.diffuse_text->bind();
    } else {
        shader.set("useTexture", 0);
    }

    if (material.normal_map && material.useNormal) {
        shader.set("useNormalMap", 1);
        shader.set("texture_normal", 1);
        material.normal_map->bind(1);
    } else {
        shader.set("useNormalMap", 0);
    }

    if (material.specular_map && material.useSpecular) {
        shader.set("useSpecularMap", 1);
        shader.set("texture_specular", 2);
        material.specular_map->bind(2);
    } else {
        shader.set("useSpecularMap", 0);
    }

    mesh->draw();
}

AABB Entity::getTransformedBoundingBox() const {
    return boundingBox.transform(transform);
}