#pragma once

#include "Globals.h"

class EntityCreator {
public:
    EntityCreator();

    std::shared_ptr<Entity> createEntity(TypeEntityCreated type, const double & x, const double & y, const double & z);

    std::string getNameOfEntityCreated(TypeEntityCreated type);

private:
    static unsigned int m_nb_cube_created;
    static unsigned int m_nb_sphere_created;
    static unsigned int m_nb_plane_created;


    std::shared_ptr<Entity> createCubeAndPlace(const double & x, const double & y, const double & z);
};