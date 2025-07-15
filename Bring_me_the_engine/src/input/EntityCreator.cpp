#include "input/EntityCreator.h"

#include "engine/Mesh.h"
#include "geometry/Cube.h"

unsigned int EntityCreator::m_nb_cube_created = 0;
unsigned int EntityCreator::m_nb_sphere_created = 0;
unsigned int EntityCreator::m_nb_plane_created = 0;

EntityCreator::EntityCreator() {
}

std::shared_ptr<Entity> EntityCreator::createEntity(TypeEntityCreated type, const double & x, const double & y, const double & z) {
    if (type == TypeEntityCreated::None) {
        return nullptr;
    }
    if (type == TypeEntityCreated::Cube) {
        return createCubeAndPlace(x, y, z);
    }
    return nullptr;
}

std::shared_ptr<Entity> EntityCreator::createCubeAndPlace(const double & x, const double & y, const double & z) {
    std::shared_ptr<Mesh> t_cubeMesh = createCube<std::shared_ptr<Mesh>>(Color::rose());
    Mat4 t_translation = Mat4::Translation(Vec3(x, y, z));
    std::shared_ptr<Material> t_boisMaterial = std::make_shared<Material>(nullptr, nullptr, nullptr);
    std::string t_name = getNameOfEntityCreated(TypeEntityCreated::Cube);
    std::shared_ptr<Entity> cubeFinal = std::make_shared<Entity>(
        t_translation, t_cubeMesh, t_boisMaterial, t_name);

    cubeFinal->getBoundingBox().setupBBoxBuffers();
    getScene().getEntities().emplace_back(cubeFinal);
    return cubeFinal;
}

std::string EntityCreator::getNameOfEntityCreated(TypeEntityCreated type) {
    switch (type) {
    case TypeEntityCreated::None:
        return "Aucune entité créée";
    case TypeEntityCreated::Cube:
        return "Cube_" + std::to_string(++m_nb_cube_created);
    case TypeEntityCreated::Sphere:
        return "Sphère_" + std::to_string(++m_nb_sphere_created);
    case TypeEntityCreated::Plane:
        return "Plan_" + std::to_string(++m_nb_plane_created);
    default:
        return "Type d'entité inconnu";
    }
}
